/**
 * Functions to handle ARM interrups. These are called
 *  by the jump table in loader/start-arm.S.
 */

void SWI_Routine( void )
{

}

void UNDEF_Routine( void )
{

}

void FIQ_Routine( void )
{

}

void PAbt_Routine( void )
{
    kprintf("PAbt!\n");
}
void DAbt_Routine( void )
{
//http://www.embedded.com/design/embedded/4006695/How-to-use-ARM-s-data-abort-exception
    kprintf("DAbt\n");
}
