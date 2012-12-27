#
# Make the Xinu configuration program
#

CC     = gcc
LEX    = flex
YACC   = bison -y    # Flag enables yacc-compatible filenames
CFLAGS = 
LFLAGS = -lfl

CONFIG = config

all: ${CONFIG}

${CONFIG}: lex.yy.c y.tab.c
	$(CC) ${CFLAGS} -o $@ $^ ${LFLAGS}

lex.yy.c: config.l y.tab.h
	$(LEX) --header-file=lex.yy.h config.l

lex.yy.h: config.l
	$(LEX) --header-file=lex.yy.h config.l

y.tab.c: config.y lex.yy.h
	$(YACC) config.y

y.tab.h: config.y
	$(YACC) --defines=$@ $^

clean:
	rm -f ${CONFIG} lex.yy.c y.tab.c lex.yy.h y.tab.h
