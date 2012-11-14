/**
 * @file create.c
 * @provides create, newtid.
 * @brief Creates a thread to start running a procedure
 */

#include <debug.h>
#include <memory.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <thread.h>

/**
 * Context record offsets
 */
/** context record size in words */
#define CONTEXT_WORDS (14)
/** context record size in bytes       */
#define CONTEXT (CONTEXT_WORDS * sizeof(intptr_t))

static int thrnew(void);

/**
 * Create a thread to start running a procedure.
 * @param procaddr procedure address
 * @param ssize stack size in bytes
 * @param priority thread priority
 * @param name name of the thread
 * @param nargs number of args that follow
 * @return new thread ID
 */
tid_typ create(void *procaddr, uint ssize, int priority,
               char *name, int nargs, ...)
{
    register struct thrent *thrptr;     /* thread control block  */
    intptr_t *saddr;               /* stack address                      */
    intptr_t *savargs;             /* pointer to arg saving region       */
    tid_typ tid;                /* stores new thread id               */
    va_list ap;                 /* points to list of var args         */
    int pads;                   /* padding entries in record.         */
    intptr_t i;
    void INITRET(void);
    irqmask im;

    im = disable();
    if (ssize < MINSTK)
    {
        ssize = MINSTK;
    }
    saddr = stkget(ssize);      /* allocate new stack   */
    tid = thrnew();             /* allocate new thread ID */

    if (((SYSERR) == (int)saddr) || (SYSERR == tid))
    {
        restore(im);
        return SYSERR;
    }

    thrcount++;
    thrptr = &thrtab[tid];

    /* setup thread control block for new thread    */
    thrptr->state = THRSUSP;
    thrptr->prio = priority;
    thrptr->stkbase = saddr;
    thrptr->stklen = ssize;
    thrptr->stkptr = saddr;
    strncpy(thrptr->name, name, TNMLEN);
    thrptr->parent = gettid();
    thrptr->hasmsg = FALSE;
    thrptr->memlist.next = NULL;
    thrptr->memlist.length = 0;

    /* set up default file descriptors */
    /** \todo When the CONSOLE stuff works on fluke-arm, we need to reenable stdio for threads. */
#if 0
    thrptr->fdesc[0] = CONSOLE; /* stdin  is console */
    thrptr->fdesc[1] = CONSOLE; /* stdout is console */
    thrptr->fdesc[2] = CONSOLE; /* stderr is console */
#endif /* 0 */

    /* Initialize stack with accounting block. */
    *saddr = STACKMAGIC;
    *--saddr = tid;
    *--saddr = thrptr->stklen;
    *--saddr = (intptr_t)thrptr->stkbase - thrptr->stklen + sizeof(intptr_t); /* max stack addr */


    if (0 == nargs)
    {
        pads = 4;
    }
    else if (0 == (nargs % 4))  /* pad size to multiple of 4 */
    {
        pads = 0;
    }
    else
    {
        pads = 4 - (nargs % 4);
    }

    for (i = 0; i < pads; i++)
    {
        *--saddr = 0;
    }
    /* reserve space for all args.  */
    for (i = nargs; i > 4; i--)
    {
        *--saddr = 0;
    }
    savargs = saddr;

    /* build the context record as expected by ctxsw               */
    for (i = CONTEXT_WORDS; i > 0; i--)
    {
        *--saddr = 0;
    }
    thrptr->stkptr = saddr;

    /* address of thread entry point  */
    saddr[CONTEXT_WORDS - 1] = (intptr_t)procaddr;
    /*
     * Store the process's (where to jump to if the procaddr function returns)
     * return address value
     */
    saddr[CONTEXT_WORDS - 2] = (intptr_t)INITRET;

    /* place arguments into activation record */
    va_start(ap, nargs);
    for (i = 0; i < 4 && i < nargs; i++)
    {
        saddr[CONTEXT_WORDS - 6 + i] = va_arg(ap, intptr_t);
    }
    for (; i < nargs; i++)
    {
        savargs[i - 4] = va_arg(ap, intptr_t);
    }
    va_end(ap);

    restore(im);
    return tid;
}

/**
 * Obtain a new (free) thread id.
 * @return a free thread id, SYSERR if all ids are used
 */
static int thrnew(void)
{
    int tid;                    /* thread id to return     */
    static int nexttid = 0;

    /* check all NTHREAD slots    */
    for (tid = 0; tid < NTHREAD; tid++)
    {
        nexttid = (nexttid + 1) % NTHREAD;
        if (THRFREE == thrtab[nexttid].state)
        {
            return nexttid;
        }
    }
    return SYSERR;
}
