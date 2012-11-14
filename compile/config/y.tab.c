/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 3 "config.y"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

extern char *yytext;
extern int   yyleng;

#define NIL (struct dev_ent *)0x00

#define CONFIGC   "../system/conf.c"  /* name of .c output     */
#define CONFIGH   "../include/conf.h" /* name of .h output     */
#define CONFHREF  "<conf.h>"          /* how conf.h referenced */
#define CONFIGIN  "xinu.config"       /* name of input file    */
#define CONFMAXNM 20                  /* max length of strings */

FILE *confc;
FILE *confh;

char *dbstr;
int   ndevs = 0;
int   currname = -1;
int   currtname = -1;
int   currdname = -1;
int   brkcount = 0;

struct sym_ent { /* symbol table */
	char *name;
	int   occurs;
} symtab[250];

int nsym = 0;
int linectr = 1;

char *doing = "device type declaration";
char *s;

struct dev_ent
{
	char *name;               /* device name (not used in types) */
	char *tname;              /* type name                       */
	int   tnum;               /* symbol table index of type      */
	char *device;             /* device name                     */
	int   csr;                /* Control Status Register addr    */
	int   irq;                /* interrupt request               */
	char  intr[CONFMAXNM];    /* interrupt routine               */
	char  init[CONFMAXNM];    /* init routine name               */
	char  open[CONFMAXNM];    /* open routine name               */
	char  close[CONFMAXNM];   /* close routine name              */
	char  read[CONFMAXNM];    /* read routine name               */
	char  write[CONFMAXNM];   /* write routine name              */
	char  control[CONFMAXNM]; /* control routine name            */
	char  seek[CONFMAXNM];    /* seek routine name               */
	char  getc[CONFMAXNM];    /* getc routine name               */
	char  putc[CONFMAXNM];    /* putc routine name               */
	int   minor;              /* device number 0,1,...           */
	struct dev_ent *next;     /* next node on the list           */
};

struct dev_ent *ftypes = NIL; /* linked list of device types  */
struct dev_ent *devs = NIL;   /* linked list of device decls. */
struct dev_ent *lastdv = NIL;
struct dev_ent *currtype = NIL;

char *devstab[] =
{
	"/* Device table entry */",
	"typedef struct dentry",
	"{",
	"\tint     num;",
	"\tint     minor;",
	"\tchar    *name;",
	"\tdevcall (*init)(struct dentry *);",
	"\tdevcall (*open)(struct dentry *, ...);",
	"\tdevcall (*close)(struct dentry *);",
	"\tdevcall (*read)(struct dentry *, void *, uint);",
	"\tdevcall (*write)(struct dentry *, void *, uint);",
	"\tdevcall (*seek)(struct dentry *, long);",
	"\tdevcall (*getc)(struct dentry *);",
	"\tdevcall (*putc)(struct dentry *, char);",
	"\tdevcall (*control)(struct dentry *, int, long, long);",
	"\tvoid    *csr;",
	"\tvoid    (*intr)(void);",
	"\tuchar   irq;",
	"} device;\n",
	"extern const device devtab[]; /* one entry per device */",
	NULL
};

/* Prototypes */
void yyerror(char *s);
int  lookup(char *str, int len);
int  config_atoi(char *p, int len);
void newattr(int tok, int val);
int  cktname(int symid);
void mktype(int deviceid);
void initattr(struct dev_ent *fstr, int tnum, int deviceid);
void mkdev(int nameid, int typid, int deviceid);
int  ckdname(int devid);



/* Line 268 of yacc.c  */
#line 175 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEFBRK = 258,
     COLON = 259,
     OCTAL = 260,
     INTEGER = 261,
     IDENT = 262,
     CSR = 263,
     IRQ = 264,
     INTR = 265,
     INIT = 266,
     OPEN = 267,
     CLOSE = 268,
     READ = 269,
     WRITE = 270,
     SEEK = 271,
     CONTROL = 272,
     IS = 273,
     ON = 274,
     GETC = 275,
     PUTC = 276
   };
#endif
/* Tokens.  */
#define DEFBRK 258
#define COLON 259
#define OCTAL 260
#define INTEGER 261
#define IDENT 262
#define CSR 263
#define IRQ 264
#define INTR 265
#define INIT 266
#define OPEN 267
#define CLOSE 268
#define READ 269
#define WRITE 270
#define SEEK 271
#define CONTROL 272
#define IS 273
#define ON 274
#define GETC 275
#define PUTC 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 259 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   47

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  22
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  33
/* YYNRULES -- Number of states.  */
#define YYNSTATES  55

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    13,    16,    19,    23,
      26,    29,    31,    32,    35,    38,    41,    44,    47,    50,
      53,    56,    59,    62,    65,    68,    71,    73,    74,    77,
      80,    85,    87,    88
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      23,     0,    -1,    24,    34,    -1,    25,     3,    -1,    -1,
      25,    26,    -1,    29,    27,    -1,    28,    31,    -1,    27,
      28,    31,    -1,    19,    30,    -1,    30,     4,    -1,     7,
      -1,    -1,    31,    32,    -1,     8,    33,    -1,     9,    33,
      -1,    10,    30,    -1,    12,    30,    -1,    13,    30,    -1,
      11,    30,    -1,    20,    30,    -1,    21,    30,    -1,    14,
      30,    -1,    15,    30,    -1,    16,    30,    -1,    17,    30,
      -1,     6,    -1,    -1,    34,    35,    -1,    36,    31,    -1,
      37,    18,    30,    38,    -1,    30,    -1,    -1,    19,    30,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   106,   106,   109,   112,   113,   116,   119,   120,   123,
     126,   129,   132,   133,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   150,   153,   154,   157,
     160,   163,   166,   167
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEFBRK", "COLON", "OCTAL", "INTEGER",
  "IDENT", "CSR", "IRQ", "INTR", "INIT", "OPEN", "CLOSE", "READ", "WRITE",
  "SEEK", "CONTROL", "IS", "ON", "GETC", "PUTC", "$accept",
  "configuration", "devtypes", "ftypes", "ftype", "dev_list", "devheader",
  "tname", "id", "attr_list", "attr", "number", "devdescriptors",
  "descriptor", "fspec", "dname", "optional_on", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    22,    23,    24,    25,    25,    26,    27,    27,    28,
      29,    30,    31,    31,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    33,    34,    34,    35,
      36,    37,    38,    38
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     2,     2,     3,     2,
       2,     1,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     0,     2,     2,
       4,     1,     0,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    27,     0,     1,     2,     3,    11,     5,     0,
       0,    31,    28,    12,     0,     0,     6,    12,    10,    29,
       0,     9,    12,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,    32,     8,    26,
      14,    15,    16,    19,    17,    18,    22,    23,    24,    25,
      20,    21,     0,    30,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     3,     8,    16,    17,     9,    10,    19,
      36,    40,     5,    12,    13,    14,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -17
static const yytype_int8 yypact[] =
{
     -17,     2,   -17,     0,   -17,    -3,   -17,   -17,   -17,   -14,
       4,   -17,   -17,   -17,    -9,    -3,   -14,   -17,   -17,    23,
      -3,   -17,   -17,    23,     5,     5,    -3,    -3,    -3,    -3,
      -3,    -3,    -3,    -3,    -3,    -3,   -17,    -7,    23,   -17,
     -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,   -17,
     -17,   -17,    -3,   -17,   -17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -17,   -17,   -17,   -17,   -17,   -17,    -2,   -17,    -5,   -16,
     -17,   -12,   -17,   -17,   -17,   -17,   -17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      11,    23,     4,     6,     7,    15,    38,     7,    18,    20,
      21,    39,    52,    41,    22,    37,     0,     0,     0,     0,
       0,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     0,     0,    34,    35,     0,     0,    54
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-17))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       5,    17,     0,     3,     7,    19,    22,     7,     4,    18,
      15,     6,    19,    25,    16,    20,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    20,    21,    -1,    -1,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    23,    24,    25,     0,    34,     3,     7,    26,    29,
      30,    30,    35,    36,    37,    19,    27,    28,     4,    31,
      18,    30,    28,    31,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    20,    21,    32,    30,    31,     6,
      33,    33,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    19,    38,    30
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1806 of yacc.c  */
#line 109 "config.y"
    { doing = "device definitions"; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 123 "config.y"
    { mktype((yyvsp[(2) - (2)])); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 126 "config.y"
    {(yyval) = currtname = cktname((yyvsp[(1) - (2)]));}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 129 "config.y"
    { (yyval) = currname = lookup(yytext, yyleng); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 136 "config.y"
    { newattr(CSR, (yyvsp[(2) - (2)]));     }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 137 "config.y"
    { newattr(IRQ, (yyvsp[(2) - (2)]));     }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 138 "config.y"
    { newattr(INTR, (yyvsp[(2) - (2)]));    }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 139 "config.y"
    { newattr(OPEN, (yyvsp[(2) - (2)]));    }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 140 "config.y"
    { newattr(CLOSE, (yyvsp[(2) - (2)]));   }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 141 "config.y"
    { newattr(INIT, (yyvsp[(2) - (2)]));    }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 142 "config.y"
    { newattr(GETC, (yyvsp[(2) - (2)]));    }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 143 "config.y"
    { newattr(PUTC, (yyvsp[(2) - (2)]));    }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 144 "config.y"
    { newattr(READ, (yyvsp[(2) - (2)]));    }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 145 "config.y"
    { newattr(WRITE, (yyvsp[(2) - (2)]));   }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 146 "config.y"
    { newattr(SEEK, (yyvsp[(2) - (2)]));    }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 147 "config.y"
    { newattr(CONTROL, (yyvsp[(2) - (2)])); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 150 "config.y"
    { (yyval) = config_atoi(yytext, yyleng); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 160 "config.y"
    { mkdev((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)])); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 163 "config.y"
    { (yyval) = currdname = ckdname((yyvsp[(1) - (1)])); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 166 "config.y"
    { (yyval) = 0;  }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 167 "config.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;



/* Line 1806 of yacc.c  */
#line 1669 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 169 "config.y"

#include "lex.yy.c"

int main(int argc, char **argv)
{
	int n, i, j, l, fcount;
	struct dev_ent *s;
	int   verbose = 0;
	char *p;
	int  c;

	if ( argc > 1 && (strncmp("-v", argv[1], 2) == 0) )
	{
		argc--;
		argv++;
		verbose++;
	}

	if ( argc > 2 )
	{
		fprintf(stderr, "use: config [-v] [file]\n");
		exit(1);
	}

	if (verbose) { printf("Opening input file...\n"); }

	if (argc == 2)
	{
		if (freopen(argv[1], "r", stdin) == NULL)
		{
			fprintf(stderr, "Can't open %s\n", argv[1]);
			exit(1);
		}
	}
	else /* try to open Configuration file */
	{
		if (freopen(CONFIGIN, "r", stdin) == NULL)
		{
			fprintf(stderr, "Can't open %s\n", CONFIGIN);
			exit(1);
		}
	}

	/* Parse the Configuration file */
	if (verbose) { printf("Parsing configuration specs...\n"); }

	if ( (n = yyparse()) != 0 ) { exit(n); }

	/* write config.h and config.c */
	if (verbose) { printf("Opening output files...\n"); }

	if ( (confc = fopen(CONFIGC,"w") ) == NULL)
	{
		fprintf(stderr, "Can't write on %s\n", CONFIGC);
		exit(1);
	}

	if ( (confh = fopen(CONFIGH,"w") ) == NULL)
	{
		fprintf(stderr, "Can't write on %s\n", CONFIGH);
		exit(1);
	}


	/** produce conf.h **/

	fprintf(confh, "/* conf.h (GENERATED FILE; DO NOT EDIT) */\n\n");
	fprintf(confh, "#ifndef _CONF_H_\n");
	fprintf(confh, "#define _CONF_H_\n\n");

	fprintf(confh, "#include <stddef.h>\n\n");

	if (verbose) { printf("Writing output...\n"); }

	fprintf(confh, "/* Device table declarations */\n\n");

	for (i = 0; (p = devstab[i]) != NULL; i++)
	{
		fprintf(confh, "%s\n", p);
	}

	fprintf(confh, "\n");

	/* write device declarations and definitions; count type refs. */
	fprintf(confh, "/* Device name definitions */\n\n");
	for (i = 0, s = devs; s != NIL; i++, s = s->next)
	{
		fprintf(confh, "#define %-12s%d       /* type %-8s */\n",
		        s->name, i, s->tname);
		s->minor = symtab[s->tnum].occurs++;
	}

	fprintf(confh, "\n");

	/* write count of device types */
	fprintf(confh, "/* Control block sizes */\n\n");
	for (i = 0; i < nsym; i++)
	{
		if (symtab[i].occurs > 0)
		{
			int j;
			char name[CONFMAXNM];
			strncpy(name, symtab[i].name, CONFMAXNM);

			for (j = 0; j < CONFMAXNM && name[j] != '\0'; j++)
			{ name[j] = toupper( name[j] ); }
			name[19] = '\0';

			fprintf(confh, "#define N%s %d\n",
			        name, symtab[i].occurs);
		}
	}

	fprintf(confh, "\n");

	fprintf(confh, "#define DEVMAXNAME %d\n", CONFMAXNM);

	if (ndevs > 0) { fprintf(confh, "#define NDEVS %d\n", ndevs); }

	/* Copy definitions to output */
	if (brkcount == 2 && verbose)
	{ printf("Copying definitions to %s...\n", CONFIGH); }

	if (brkcount == 2 )
	{
		while ( (c = input()) > 0)    /* lex input routine */
		{ putc(c, confh); }
	}

	fprintf(confh, "\n#endif /* _CONF_H_ */\n");

	fclose(confh);


	/** produce conf.c **/

	fprintf(confc, "/* conf.c (GENERATED FILE; DO NOT EDIT) */\n\n");
	fprintf(confc, "#include %s\n", CONFHREF);
	fprintf(confc, "#include <device.h>\n\n");

	for (i = 0; i < nsym; i++)
	{
		if (symtab[i].occurs > 0)
		{ fprintf(confc, "#include <%s.h>\n", symtab[i].name); }
	}
	fprintf(confc, "\n");

	fprintf(confc, "extern devcall ioerr(void);\n");
	fprintf(confc, "extern devcall ionull(void);\n\n");

	/* produce devtab (giant I/O switch table) */
	fprintf(confc, "/* device independent I/O switch */\n\n");
	if (ndevs > 0)
	{
		fprintf(confc, "const device devtab[NDEVS] =\n{\n");
		fprintf(confc, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
			"/**",
			" * Format of entries is:",
			" * dev-number, minor-number, dev-name,",
			" * init, open, close,",
			" * read, write, seek,",
			" * getc, putc, control,",
			" * dev-csr-address, intr-handler, irq",
			" */");
	}

	for (fcount = 0, s = devs; s != NIL; fcount++, s = s->next)
	{
		fprintf(confc, "/* %s is %s */\n", s->name, s->tname);
		fprintf(confc, "\t{ %d, %d, \"%s\",\n", fcount, s->minor, s->name);
		fprintf(confc, "\t  (void *)%s, (void *)%s, (void *)%s,\n",
		        s->init, s->open, s->close);
		fprintf(confc, "\t  (void *)%s, (void *)%s, (void *)%s,\n",
		        s->read, s->write, s->seek);
		fprintf(confc, "\t  (void *)%s, (void *)%s, (void *)%s,\n",
		        s->getc, s->putc, s->control);
		fprintf(confc, "\t  (void *)0x%x, (void *)%s, %d }",
		        s->csr, s->intr, s->irq);

		if ( s->next != NIL ) { fprintf(confc, ",\n\n"); }
		else                  { fprintf(confc, "\n};");  }
	}

	/* guarantee conf.c written later than conf.c for make */
	fprintf(confc, "\n");
	fclose(confc);

	/* finish up and write report for user if requested */
	if (verbose)
	{
		printf("Configuration complete. Number of devs=%d:\n", ndevs);
		for (s = devs; s != NIL ; s = s->next)
		{
			printf("Device %s (on %s)\n", s->name, s->device);
			printf("    csr=0x%04x, irq=0x%04x, minor=%d\n",
			       s->csr, s->irq, s->minor);
		}
	}
}

void yyerror(char *s)
{
	fprintf(stderr, "Syntax error in %s on line %d\n", doing, linectr);
}

/* lookup  --  lookup a name in the symbol table; return position */
int lookup(char *str, int len)
{
	int   i;
	char *s;

	if (len >= CONFMAXNM)
	{
		len = CONFMAXNM-1;
		fprintf(stderr, "warning: name %s truncated\n", str);
	}

	s = (char *)malloc(len + 1);
	strncpy(s, str, len);
	s[len] = '\0';

	for (i = 0; i < nsym; i++)
	{
		if ( strncmp(s, symtab[i].name, CONFMAXNM) == 0 )
		{ return(i); }
	}

	symtab[nsym].name = s;
	symtab[nsym].occurs = 0;

	return nsym++;
}

int config_atoi(char *p, int len)
{
	int base, rv;

	if (*p == '0')
	{
		++p;
		--len;
		if (*p == 'x' || *p == 'X')
		{
			++p; --len; /* skip 'x' */
			base = 16;
		}
		else
		{
			base = 8;
		}
	}
	else
	{
		base = 10;
	}

	rv = 0;
	for (; len > 0; ++p, --len)
	{
		rv *= base;
		if      (isdigit(*p)) { rv += *p - '0'; }
		else if (isupper(*p)) { rv += *p - 'A' + 10; }
		else                  { rv += *p - 'a' + 10; }
	}

	return rv;
}

/* newattr -- add a new attribute spec to current type/device description */
/* tok: token type (attribute type) */
/* val: symbol number of value      */
void newattr(int tok, int val)
{
	struct dev_ent *s;
	char *c;

	/* doing types */
	if (devs == NIL) { s = currtype; }
	else             { s = lastdv; }

	if (val>=0 && val<nsym)
	{
		c = symtab[val].name;
		if (strnlen(c, CONFMAXNM) == CONFMAXNM )
		{
			fprintf(stderr, "Internal overflow\n");
			exit(1);
		}
	}
	else
	{ c = NULL; }

	switch (tok)
	{
	case CSR:     s->csr = val;                      break;
	case IRQ:     s->irq = val;                      break;
	case INTR:    strncpy(s->intr,    c, CONFMAXNM); break;
	case READ:    strncpy(s->read,    c, CONFMAXNM); break;
	case WRITE:   strncpy(s->write,   c, CONFMAXNM); break;
	case GETC:    strncpy(s->getc,    c, CONFMAXNM); break;
	case PUTC:    strncpy(s->putc,    c, CONFMAXNM); break;
	case OPEN:    strncpy(s->open,    c, CONFMAXNM); break;
	case CLOSE:   strncpy(s->close,   c, CONFMAXNM); break;
	case INIT:    strncpy(s->init,    c, CONFMAXNM); break;
	case SEEK:    strncpy(s->seek,    c, CONFMAXNM); break;
	case CONTROL: strncpy(s->control, c, CONFMAXNM); break;
	default:      fprintf(stderr, "Internal error 1\n");
	}
}

/* cktname  --  check type name for duplicates */
int cktname(int symid)
{
	struct dev_ent *s;
	char *name;

	name = symtab[symid].name;
	for (s = ftypes; s != NIL; s = s->next)
	{
		if (s->tname == name)
		{
			fprintf(stderr, "Duplicate type name %s on line %d\n",
			        name, linectr);
			exit(1);
		}
	}

	return symid;
}

/* mktype  --  make a node in the type list and initialize to defaults */
void mktype(int deviceid)
{
	struct dev_ent *s, *p;
	char *tn, *dn;

	p = NIL;
	tn = symtab[currtname].name;
	dn = symtab[deviceid].name;
	for (s = ftypes; s != NIL ; s = s->next)
	{
		if (s->tname == tn && s->device==dn)
		{
			fprintf(stderr, "Duplicate device %s for type %s on line %d\n",
			        dn, tn, linectr);
			exit(1);
		}
		p = s;
	}

	currtype = s = (struct dev_ent *)malloc(sizeof(struct dev_ent));
	if (ftypes != NIL) { p->next = s; }
	else               { ftypes = s; }

	initattr(s, currtname, deviceid);
}

/* initialize attributes in a type declaration node to typename... */
void initattr(struct dev_ent *fstr, int tnum, int deviceid)
{
	fstr->name = NULL;
	fstr->tname = symtab[tnum].name;
	fstr->tnum = tnum;
	fstr->device = symtab[deviceid].name;
	fstr->csr = 0;
	fstr->irq = 0;
	strncpy(fstr->intr,    "ioerr", 5);
	strncpy(fstr->init,    "ioerr", 5);
	strncpy(fstr->open,    "ioerr", 5);
	strncpy(fstr->close,   "ioerr", 5);
	strncpy(fstr->read,    "ioerr", 5);
	strncpy(fstr->write,   "ioerr", 5);
	strncpy(fstr->control, "ioerr", 5);
	strncpy(fstr->seek,    "ioerr", 5);
	strncpy(fstr->getc,    "ioerr", 5);
	strncpy(fstr->putc,    "ioerr", 5);
	fstr->minor = 0;
}

/* mkdev  --  make a node on the device list */
void mkdev(int nameid, int typid, int deviceid)
{
	struct dev_ent *s;
	char *devn, *tn, *dn;
	int   found;

	s = (struct dev_ent *)malloc(sizeof(struct dev_ent));
	s->next = NIL;
	if (devs == NIL)
	{
		devs = s;
		lastdv = s;
	}
	else
	{
		lastdv->next = s;
		lastdv = s;
	}

	ndevs++;
	tn = symtab[typid].name;
	devn = symtab[nameid].name;

	if (deviceid >= 0) { dn = symtab[deviceid].name; }
	else               { dn = NULL; }

	found = 0;
	for (s = ftypes; s != NULL ; s = s->next)
	{
		if (s->tname == tn && (dn == NULL || s->device == dn))
		{
			memcpy(lastdv, s, sizeof(struct dev_ent));
			found = 1;
			break;
		}
	}

	if (found==0)
	{
		fprintf(stderr,
		        "Bad type or device name in declaration of %s on line %d\n",
		        devn, linectr);
		exit(1);
	}

	lastdv->next = NIL;
	lastdv->name = devn;
}


/* chdname  -- check for duplicate device name */
int ckdname(int devid)
{
	struct dev_ent *s;
	char *name;

	name = symtab[devid].name;

	for (s = devs; s != NIL; s = s->next)
	{
		if (s->name == name)
		{
			fprintf(stderr, "Duplicate device name %s on line %d\n",
			        name, linectr);
			exit(1);
		}
	}

	return devid;
}


