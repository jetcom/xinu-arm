%{
#include "y.tab.h"
extern int linectr;
extern int brkcount;
int skipping;
char *verbatim_out = NULL;
int verbatim_out_strlen = 0;
size_t verbatim_out_bufsize = BUFSIZ;
%}
OCT 0[0-7]*
DEC [1-9][0-9]*
HEX 0x[0-9a-fA-F]+
ID [a-z_A-Z][a-z_A-Z0-9]*
%%
"/*"      { skipping = 1;                     }
"*/"      { skipping = 0;                     }
"%%"      { if (! skipping)
                /*
                 * If we have seen the second set of '%%' tokens, prepare to
                 * copy the rest of the config file into config.h verbatim.
                 *
                 * Dump the verbatim section of the config file into
                 * 'verbatim_out'.
                 */
                if (++brkcount == 2)
                {
                    verbatim_out = malloc(verbatim_out_bufsize);
                    char c;
                    while( (c = input()) != EOF )
                    {
                        if( (verbatim_out_strlen + 1) >= verbatim_out_bufsize)
                        {
                            verbatim_out_bufsize += BUFSIZ;
                            verbatim_out =
                                realloc( verbatim_out, verbatim_out_bufsize );
                        }
                        verbatim_out[verbatim_out_strlen++] = c;
                    }
                    verbatim_out[verbatim_out_strlen] = '\0';

                    return EOF;
                }
                else
                { return DEFBRK; }            }
":"       { if (! skipping) return COLON;     }
{OCT}     { if (! skipping) return INTEGER;   }
{DEC}     { if (! skipping) return INTEGER;   }
{HEX}     { if (! skipping) return INTEGER;   }
is        { if (! skipping) return IS;        }
on        { if (! skipping) return ON;        }
"="       ;
-?intr    { if (! skipping) return INTR;      }
-?csr     { if (! skipping) return CSR;       }
-?irq     { if (! skipping) return IRQ;       }
-?i       { if (! skipping) return INIT;      }
-?o       { if (! skipping) return OPEN;      }
-?c       { if (! skipping) return CLOSE;     }
-?r       { if (! skipping) return READ;      }
-?g       { if (! skipping) return GETC;      }
-?p       { if (! skipping) return PUTC;      }
-?w       { if (! skipping) return WRITE;     }
-?s       { if (! skipping) return SEEK;      }
-?n       { if (! skipping) return CONTROL;   }
[ \t]+    ;
"\n"      { linectr++;                        }
{ID}      { if (! skipping) return IDENT;     }
.         { if (! skipping) return yytext[0]; }
