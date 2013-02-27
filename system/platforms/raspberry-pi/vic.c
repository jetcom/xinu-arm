#include "interrupt.h"
#include "vic.h"

/*
    NOTE: this is not a real VIC like one might expect! Each vector number
    is tied to a specific device which is represented as a bit in a status
    register. Because of this, we have to check each bit of the status register
    for a pending IRQ. Because of that, de-registering an interrupt doesn't
    guarantee that the interrupt won't fire while the deregister function is
    executing before it fully disables the interrupt.

    Additionally, this interrupt controller also has a number of quirks. The
    Linux source code for this device sheds some light on what these are:

    Quirk 1: Shortcut interrupts don't set the bank 1/2 register pending bits

             (The Basic Pending Register is supposed the be the first place we
             look for an interrupt. It's a summary of the most common interrupt
             bits. Because of this, it partially duplicates the bits in the
             Interrupt Pending 1 & 2 Registers. It also has a few bits that say
             if any bits are set in the Interrupt Pending 1 & 2 registers.
             Therefore, it may seem a bit odd that this device won't set these
             "look at Interrupt Pending 1 & 2" bits when devices that appear
             in both the Basic Pending Register and an Interrupt Pending
             Register assert an interrupt. This code doesn't use the Basic
             Pending Register, so we avoid this altogether.)



    Quirk 2: You can't mask the register 1/2 pending interrupts

             (Not completely sure what this means. In the worst-case
             scenario, we won't be able to disable certain IRQ sources
             by writing to the Interrupt Disable Registers. That being
             said, the deregister routine has successfully used the
             Disable Registers because otherwise, we'd go into an
             infinite IRQ loop (see comments in that routine for more
             info).)



    Quirk 3: Quirk 3: The shortcut interrupts can't be (un)masked in bank 0

             (This code does not use the Basic Pending Register, so we
             don't need to worry about this.)
*/

#define NULL_VECT (irq_handler)0
#define NUM_VECT 64

static irq_handler vectors[NUM_VECT];

//interrupts should be disabled on the CPU level before calling this routine
void vic_init(void)
{
    int i;

    //disable all IRQ sources first, just to be "safe"
    INTERRUPT_DISABLEIRQ1 = 0xFFFFFFFF;
    INTERRUPT_DISABLEIRQ2 = 0xFFFFFFFF;

    //fill the vector table with "don't jump to me" values
    for(i=0; i<NUM_VECT; i++){
        vectors[i] = NULL_VECT;
    }
}

irqmask vic_get_irqmask(void)
{
    irqmask ret;

    ret.lower = INTERRUPT_ENABLEIRQ1;
    ret.upper = INTERRUPT_ENABLEIRQ2;
    ret.irqen = vic_interrupts_disabled();

    return ret;
}

void vic_set_irqmask( irqmask im )
{
    //enable enabled IRQs
    INTERRUPT_ENABLEIRQ1 = im.lower;
    INTERRUPT_ENABLEIRQ2 = im.upper;

    //disable disabled IRQs
    INTERRUPT_DISABLEIRQ1 = ~(im.lower);
    INTERRUPT_DISABLEIRQ2 = ~(im.upper);

    //restore interrupt state
    if(im.irqen == 0) //if interrupts were enabled
    {
        vic_enable_interrupts();
    }
    else //if interrupts were disabled
    {
        vic_disable_interrupts();
    }
}

void vic_enable_irq(int vect_num)
{
        //enable the respective interrupt
        if(vect_num < 32)
        {
            //only 1 bits are recognized when writing to the (en/dis)able regs.
            //  using |= here could be problematic since it would likely be
            //  implemented as multiple instructions: at least a read, an or,
            //  and a write. if we interrupted _after_ the read instruction or
            //  the or instruction, and disabled certain bits in the IRQ
            //  routine, the |= would write back the old state of the enable
            //  bits. This would effectively be re-enabling interrupts that we
            //  wanted disabled.
            INTERRUPT_ENABLEIRQ1 = (1<<vect_num); //zeroes are ignored, don't use |=
        }
        else
        {
            INTERRUPT_ENABLEIRQ2 = (1<<(vect_num-32)); //zeroes are ignored, don't use |=
        }
}

void vic_disable_irq(int vect_num)
{
        //disable IRQs for this device before NULL-ing the vector. otherwise,
        //  we might interrupt with a NULL_VECT in the handler's address.
        //  because the interrupt wasn't ACKed because we never went to the
        //  handler routine, the device will continue to assert its IRQ line,
        //  which will put us in a never-ending IRQ loop.
        if(vect_num < 32)
        {
            INTERRUPT_DISABLEIRQ1 = (1<<vect_num); //zeroes are ignored, don't use |=
        }
        else
        {
            INTERRUPT_DISABLEIRQ2 = (1<<(vect_num-32)); //zeroes are ignored, don't use |=
        }
}

//void vic_register_irq(int vect_num, vect_t handler)
void vic_register_irq(int vect_num, irq_handler handler)
{
    //if the index is valid
    if((vect_num >= 0) &&
       (vect_num < NUM_VECT))
    {
        //write the new handler into the vector table first so that if we
        //  enable an IRQ that's currently asserted and thus have an interrupt,
        //  we'll already have a good address to jump to.
        vectors[vect_num] = handler;
    }
}

void vic_deregister_irq(int vect_num)
{
    //if the index is valid
    if((vect_num >= 0) &&
       (vect_num < NUM_VECT))
    {
        //disable IRQs for this device before NULL-ing the vector. otherwise,
        //  we might interrupt with a NULL_VECT in the handler's address.
        //  because the interrupt wasn't ACKed because we never went to the
        //  handler routine, the device will continue to assert its IRQ line,
        //  which will put us in a never-ending IRQ loop.

        //write the new handler
        vectors[vect_num] = NULL_VECT;
    }
}

void vic_irq_handler(void)
{
    //If IRQs trigger while this handler is executing, we will probably miss
    //  them. That's not the end of the world, because IRQs on the ARM are
    //  level triggered. That means that the ARM will interrupt again after
    //  we leave the IRQ handler, which will re-run this code allowing us to
    //  service the new interrupt(s).
    unsigned int i, irqs;

    //handle all vectors in the first set of IRQs
    irqs = INTERRUPT_IRQPEND1;
    for(i=0; i<32; i++)
    {
        //if the current bit is set and there's a handler
        if((irqs & 1) && //if this IRQ has a pending interrupt
           (vectors[i] != NULL_VECT)) //just in case we interrupted a registration or deregistration
        {
            //call the handler
            vectors[i]();
        }

        //on to the next one
        irqs = (irqs>>1);
    }

    //handle all vectors in the first set of IRQs
    irqs = INTERRUPT_IRQPEND2;
    for(i=32; i<64; i++)
    {
        //if the current bit is set and there's a handler
        if((irqs & 1) && //if this IRQ has a pending interrupt
           (vectors[i] != NULL_VECT)) //just in case we interrupted a registration or deregistration
        {
            //call the handler
            vectors[i]();
        }

        //on to the next one
        irqs = (irqs>>1);
    }
}
