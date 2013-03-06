/*
 * @file     xsh_echo.c
 * @provides xsh_echo
 */
/* Embedded Xinu, Copyright (C) 2008.  All rights reserved. */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <date.h>

/**
 * Shell command (echo).
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_echo(int nargs, char *args[])
{
    int i;
    for( i=1; i<nargs; ++i)
        printf("%s ", args[i]);
    printf("\n");
    return OK;
}
