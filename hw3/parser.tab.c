/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     CONST = 259,
     VOID = 260,
     INT = 261,
     FLOAT = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     FOR = 266,
     TYPEDEF = 267,
     OP_ASSIGN = 268,
     OP_OR = 269,
     OP_AND = 270,
     OP_NOT = 271,
     OP_EQ = 272,
     OP_NE = 273,
     OP_GT = 274,
     OP_LT = 275,
     OP_GE = 276,
     OP_LE = 277,
     OP_PLUS = 278,
     OP_PP = 279,
     OP_MINUS = 280,
     OP_MM = 281,
     OP_TIMES = 282,
     OP_DIVIDE = 283,
     MK_LB = 284,
     MK_RB = 285,
     MK_LPAREN = 286,
     MK_RPAREN = 287,
     MK_LBRACE = 288,
     MK_RBRACE = 289,
     MK_COMMA = 290,
     MK_SEMICOLON = 291,
     MK_DOT = 292,
     ERROR = 293,
     RETURN = 294
   };
#endif
/* Tokens.  */
#define ID 258
#define CONST 259
#define VOID 260
#define INT 261
#define FLOAT 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define FOR 266
#define TYPEDEF 267
#define OP_ASSIGN 268
#define OP_OR 269
#define OP_AND 270
#define OP_NOT 271
#define OP_EQ 272
#define OP_NE 273
#define OP_GT 274
#define OP_LT 275
#define OP_GE 276
#define OP_LE 277
#define OP_PLUS 278
#define OP_PP 279
#define OP_MINUS 280
#define OP_MM 281
#define OP_TIMES 282
#define OP_DIVIDE 283
#define MK_LB 284
#define MK_RB 285
#define MK_LPAREN 286
#define MK_RPAREN 287
#define MK_LBRACE 288
#define MK_RBRACE 289
#define MK_COMMA 290
#define MK_SEMICOLON 291
#define MK_DOT 292
#define ERROR 293
#define RETURN 294




/* Copy the first part of user declarations.  */
#line 4 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"
int linenumber = 1;
AST_NODE *prog;

extern int g_anyErrorOccur;

static inline AST_NODE* makeSibling(AST_NODE *a, AST_NODE *b)
{ 
    while (a->rightSibling) {
        a = a->rightSibling;
    }
    if (b == NULL) {
        return a;
    }
    b = b->leftmostSibling;
    a->rightSibling = b;
    
    b->leftmostSibling = a->leftmostSibling;
    b->parent = a->parent;
    while (b->rightSibling) {
        b = b->rightSibling;
        b->leftmostSibling = a->leftmostSibling;
        b->parent = a->parent;
    }
    return b;
}

static inline AST_NODE* makeChild(AST_NODE *parent, AST_NODE *child)
{
    if (child == NULL) {
        return parent;
    }
    if (parent->child) {
        makeSibling(parent->child, child);
    } else {
        child = child->leftmostSibling;
        parent->child = child;
        while (child) {
            child->parent = parent;
            child = child->rightSibling;
        }
    }
    return parent;
}

static AST_NODE* makeFamily(AST_NODE *parent, int childrenCount, ...)
{
    va_list childrenList;
    va_start(childrenList, childrenCount);
    AST_NODE* child = va_arg(childrenList, AST_NODE*);
    makeChild(parent, child);
    AST_NODE* tmp = child;
    int index = 1;
    for (index = 1; index < childrenCount; ++index) {
        child = va_arg(childrenList, AST_NODE*);
        tmp = makeSibling(tmp, child);
    }
    va_end(childrenList);
    return parent;
}

static inline AST_NODE* makeIDNode(char *lexeme, IDENTIFIER_KIND idKind)
{
    AST_NODE* identifier = Allocate(IDENTIFIER_NODE);
    identifier->semantic_value.identifierSemanticValue.identifierName = lexeme;
    identifier->semantic_value.identifierSemanticValue.kind = idKind;
    identifier->semantic_value.identifierSemanticValue.symbolTableEntry = NULL;
    return identifier;                        
}

static inline AST_NODE* makeStmtNode(STMT_KIND stmtKind)
{
    AST_NODE* stmtNode = Allocate(STMT_NODE);
    stmtNode->semantic_value.stmtSemanticValue.kind = stmtKind;
    return stmtNode;                        
}

static inline AST_NODE* makeDeclNode(DECL_KIND declKind)
{
    AST_NODE* declNode = Allocate(DECLARATION_NODE);
    declNode->semantic_value.declSemanticValue.kind = declKind;
    return declNode;                        
}

static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)
{
    AST_NODE* exprNode = Allocate(EXPR_NODE);
    exprNode->semantic_value.exprSemanticValue.isConstEval = 0;
    exprNode->semantic_value.exprSemanticValue.kind = exprKind;
    if (exprKind == BINARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.binaryOp = operationEnumValue;
    } else if (exprKind == UNARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.unaryOp = operationEnumValue;
    } else {
        printf("Error in static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)\n");
    }
    return exprNode;                        
}



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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 112 "parser.y"
{
	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;
}
/* Line 193 of yacc.c.  */
#line 286 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 299 "parser.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   308

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNRULES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    14,    16,    25,
      34,    42,    50,    54,    56,    59,    63,    67,    72,    74,
      75,    78,    80,    82,    83,    86,    88,    90,    92,    97,
     102,   106,   108,   110,   112,   114,   118,   123,   126,   130,
     135,   139,   143,   145,   149,   153,   155,   157,   160,   164,
     169,   171,   175,   177,   180,   184,   187,   189,   193,   199,
     209,   214,   220,   228,   234,   236,   239,   243,   246,   248,
     249,   253,   255,   259,   261,   265,   267,   271,   273,   277,
     279,   283,   285,   287,   289,   291,   293,   295,   297,   298,
     302,   304,   308,   310,   312,   314,   318,   320,   322,   324,
     328,   333,   335,   338,   343,   349,   351,   354,   356,   359,
     362,   365,   368,   372,   376,   380,   384,   386,   388,   390,
     392,   395,   400
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    -1,    42,    43,    -1,    43,
      -1,    50,    44,    -1,    44,    -1,    54,     3,    31,    45,
      32,    33,    49,    34,    -1,     5,     3,    31,    45,    32,
      33,    49,    34,    -1,    54,     3,    31,    32,    33,    49,
      34,    -1,     5,     3,    31,    32,    33,    49,    34,    -1,
      45,    35,    46,    -1,    46,    -1,    54,     3,    -1,    54,
       3,    47,    -1,    29,    48,    30,    -1,    47,    29,    73,
      30,    -1,    73,    -1,    -1,    50,    62,    -1,    62,    -1,
      50,    -1,    -1,    50,    51,    -1,    51,    -1,    52,    -1,
      53,    -1,    12,    54,    55,    36,    -1,    12,     5,    55,
      36,    -1,    54,    60,    36,    -1,     6,    -1,     7,    -1,
       3,    -1,     3,    -1,    55,    35,     3,    -1,    55,    35,
       3,    56,    -1,     3,    56,    -1,    29,    57,    30,    -1,
      56,    29,    57,    30,    -1,    57,    23,    58,    -1,    57,
      25,    58,    -1,    58,    -1,    58,    27,    59,    -1,    58,
      28,    59,    -1,    59,    -1,     4,    -1,    79,     4,    -1,
      31,    57,    32,    -1,    79,    31,    57,    32,    -1,    61,
      -1,    60,    35,    61,    -1,     3,    -1,     3,    56,    -1,
       3,    13,    67,    -1,    62,    63,    -1,    63,    -1,    33,
      49,    34,    -1,    10,    31,    65,    32,    63,    -1,    11,
      31,    64,    36,    71,    36,    64,    32,    63,    -1,    80,
      13,    67,    36,    -1,     8,    31,    65,    32,    63,    -1,
       8,    31,    65,    32,    63,     9,    63,    -1,    80,    31,
      71,    32,    36,    -1,    36,    -1,    39,    36,    -1,    39,
      67,    36,    -1,    78,    36,    -1,    65,    -1,    -1,    65,
      35,    66,    -1,    66,    -1,     3,    13,    67,    -1,    67,
      -1,    31,    65,    32,    -1,    68,    -1,    67,    14,    68,
      -1,    69,    -1,    68,    15,    69,    -1,    73,    -1,    73,
      70,    73,    -1,    17,    -1,    21,    -1,    22,    -1,    18,
      -1,    19,    -1,    20,    -1,    72,    -1,    -1,    72,    35,
      67,    -1,    67,    -1,    73,    74,    75,    -1,    75,    -1,
      23,    -1,    25,    -1,    75,    76,    77,    -1,    77,    -1,
      27,    -1,    28,    -1,    31,    67,    32,    -1,    79,    31,
      67,    32,    -1,     4,    -1,    79,     4,    -1,     3,    31,
      71,    32,    -1,    79,     3,    31,    71,    32,    -1,    80,
      -1,    79,    80,    -1,    78,    -1,    24,     3,    -1,     3,
      24,    -1,    26,     3,    -1,     3,    26,    -1,    24,     3,
      81,    -1,     3,    81,    24,    -1,    26,     3,    81,    -1,
       3,    81,    26,    -1,    16,    -1,    23,    -1,    25,    -1,
       3,    -1,     3,    81,    -1,    81,    29,    73,    30,    -1,
      29,    73,    30,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   168,   171,   175,   181,   185,   191,   198,
     206,   212,   221,   225,   233,   238,   245,   249,   255,   261,
     266,   272,   277,   282,   288,   293,   300,   304,   310,   316,
     324,   332,   336,   340,   346,   350,   355,   360,   366,   374,
     379,   384,   390,   396,   402,   408,   415,   421,   427,   432,
     439,   444,   451,   455,   460,   467,   472,   481,   487,   491,
     496,   502,   507,   512,   516,   521,   526,   531,   537,   543,
     548,   553,   566,   571,   576,   582,   586,   593,   598,   605,
     610,   617,   622,   627,   632,   637,   642,   650,   656,   661,
     666,   673,   678,   685,   689,   695,   700,   707,   712,   719,
     725,   730,   736,   742,   748,   753,   759,   763,   769,   773,
     777,   781,   785,   789,   793,   797,   803,   807,   811,   818,
     823,   831,   836
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CONST", "VOID", "INT", "FLOAT",
  "IF", "ELSE", "WHILE", "FOR", "TYPEDEF", "OP_ASSIGN", "OP_OR", "OP_AND",
  "OP_NOT", "OP_EQ", "OP_NE", "OP_GT", "OP_LT", "OP_GE", "OP_LE",
  "OP_PLUS", "OP_PP", "OP_MINUS", "OP_MM", "OP_TIMES", "OP_DIVIDE",
  "MK_LB", "MK_RB", "MK_LPAREN", "MK_RPAREN", "MK_LBRACE", "MK_RBRACE",
  "MK_COMMA", "MK_SEMICOLON", "MK_DOT", "ERROR", "RETURN", "$accept",
  "program", "global_decl_list", "global_decl", "function_decl",
  "param_list", "param", "dim_fn", "expr_null", "block", "decl_list",
  "decl", "type_decl", "var_decl", "type", "id_list", "dim_decl", "cexpr",
  "mcexpr", "cfactor", "init_id_list", "init_id", "stmt_list", "stmt",
  "assign_expr_list", "nonempty_assign_expr_list", "assign_expr",
  "relop_expr", "relop_term", "relop_factor", "rel_op", "relop_expr_list",
  "nonempty_relop_expr_list", "expr", "add_op", "term", "mul_op", "factor",
  "double_add_id", "unary_op", "var_ref", "dim_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    42,    42,    43,    43,    44,    44,
      44,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    49,    49,    49,    50,    50,    51,    51,    52,    52,
      53,    54,    54,    54,    55,    55,    55,    55,    56,    56,
      57,    57,    57,    58,    58,    58,    59,    59,    59,    59,
      60,    60,    61,    61,    61,    62,    62,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    67,    67,    68,    68,    69,
      69,    70,    70,    70,    70,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    76,    76,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    78,    78,
      78,    78,    78,    78,    78,    78,    79,    79,    79,    80,
      80,    81,    81
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     3,     4,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     1,     4,     4,
       3,     1,     1,     1,     1,     3,     4,     2,     3,     4,
       3,     3,     1,     3,     3,     1,     1,     2,     3,     4,
       1,     3,     1,     2,     3,     2,     1,     3,     5,     9,
       4,     5,     7,     5,     1,     2,     3,     2,     1,     0,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     3,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     3,
       4,     1,     2,     4,     5,     1,     2,     1,     2,     2,
       2,     2,     3,     3,     3,     3,     1,     1,     1,     1,
       2,     4,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    33,     0,    31,    32,     0,     0,     2,     5,     7,
       0,    25,    26,    27,     0,     0,     0,     0,     1,     4,
       6,    24,    52,     0,    50,     0,    34,     0,     0,     0,
       0,     0,    53,     0,    30,     0,     0,    13,     0,    37,
       0,    29,    28,   119,   101,   116,   117,     0,   118,     0,
       0,    54,    75,    77,    79,    92,    96,   107,     0,   105,
      46,     0,     0,    42,    45,     0,     0,     0,     0,    52,
      51,    23,     0,     0,    14,    35,   109,   111,     0,    88,
     120,   108,   110,     0,     0,     0,    81,    84,    85,    86,
      82,    83,    93,    94,     0,     0,    97,    98,     0,   119,
     102,     0,   106,     0,     0,     0,    38,     0,     0,    47,
       0,    23,     0,     0,   119,     0,     0,     0,    23,    64,
       0,     0,    22,     0,    21,    56,     0,     0,    23,    12,
      19,    15,    36,     0,    90,     0,    87,   113,   115,     0,
     112,   114,    99,    76,    78,    80,    91,    95,    88,   120,
       0,    48,    40,    41,    43,    44,     0,     0,    23,    39,
       0,     0,    69,     0,    65,     0,    11,    20,   119,    55,
      67,     0,    88,     0,     0,    18,     0,   122,   103,     0,
       0,     0,   100,    49,    10,     0,   119,     0,     0,    71,
      73,     0,     0,    68,    57,    66,     0,     0,     9,    16,
       0,    89,   121,   104,     8,     0,     0,    73,     0,     0,
       0,    88,    60,     0,    17,    72,    74,    61,    70,    58,
       0,    63,     0,    69,    62,     0,     0,    59
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    36,    37,   131,   174,   121,
     122,    11,    12,    13,   123,    27,    32,    62,    63,    64,
      23,    24,   124,   125,   192,   193,   189,   190,    52,    53,
      94,   135,   136,    54,    95,    55,    98,    56,    57,    58,
      59,    80
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -142
static const yytype_int16 yypact[] =
{
     219,  -142,    13,  -142,  -142,   256,    44,   219,  -142,  -142,
     219,  -142,  -142,  -142,    55,    42,    91,    91,  -142,  -142,
    -142,  -142,   107,    51,  -142,    20,   103,   165,   184,   181,
      14,    86,   110,   146,  -142,   123,    94,  -142,   171,   110,
     218,  -142,  -142,   217,  -142,  -142,  -142,   241,  -142,   247,
     181,   252,   166,  -142,   215,   117,  -142,  -142,    37,  -142,
    -142,    14,   148,   175,  -142,     7,   234,   140,    14,    19,
    -142,   101,   235,   251,   240,   103,  -142,  -142,   181,   181,
     133,   242,   242,    49,   181,   181,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,   181,   181,  -142,  -142,   181,   132,
    -142,   181,  -142,    52,    14,    14,  -142,    14,    14,  -142,
      14,   101,   237,   168,    71,   243,   244,   245,   101,  -142,
     163,   238,   101,   146,   144,  -142,   246,    90,   101,  -142,
     181,   248,   110,   222,   252,   249,   250,  -142,  -142,   181,
     254,   254,  -142,   166,  -142,   167,   117,  -142,   181,   254,
     109,  -142,   175,   175,  -142,  -142,    99,   239,   101,  -142,
     192,   192,   192,   253,  -142,     6,  -142,   144,   185,  -142,
    -142,   181,   181,   255,   258,   167,   181,  -142,  -142,   181,
     226,   259,  -142,  -142,  -142,   260,   104,   192,   178,  -142,
     252,   195,   257,   261,  -142,  -142,    21,   263,  -142,  -142,
     230,   252,  -142,  -142,  -142,   181,   207,    49,   144,   192,
     144,   181,  -142,   262,  -142,   252,  -142,   269,  -142,  -142,
     264,  -142,   144,   192,  -142,   265,   144,  -142
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,   272,   270,   268,   211,  -142,  -142,   -99,
      46,    -8,  -142,  -142,     3,   273,   -20,   -46,   124,   157,
    -142,   271,   164,  -120,    69,  -136,    92,   -29,   221,   223,
    -142,  -141,  -142,   -61,  -142,   208,  -142,   204,   -62,   -25,
     -57,    17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -34
static const yytype_int16 yytable[] =
{
      51,   102,    21,    14,   169,    65,    39,   181,    17,   126,
      14,   109,   157,    14,   127,   103,    15,   133,    60,   163,
      84,    83,   113,     1,   188,   191,     3,     4,    38,   173,
      45,   197,    29,   145,    38,    84,    65,    46,   110,    48,
      99,   100,   195,    65,    18,    61,    10,   169,    30,   126,
     134,   206,    35,    10,   127,   132,   126,   212,    22,   185,
     126,   127,   126,    84,   156,   127,   126,   127,   101,   175,
     220,   127,   150,    25,   -33,   104,    38,   105,   180,    65,
      65,   142,    65,    65,   151,    65,    33,    34,   217,     1,
     219,   165,     3,     4,    26,    76,   126,    77,   140,   141,
      78,   127,   224,   171,   114,   126,   227,     3,     4,   115,
     127,   116,   117,     5,    21,   200,   149,   205,    66,   134,
      29,   172,   104,    84,   105,    47,    72,    49,    76,    73,
      77,   183,    30,    78,   118,    79,    30,   119,    31,    68,
     120,   182,   196,   134,    96,    97,   126,   168,   126,    69,
     201,   127,   115,   127,   116,   117,    71,   137,   207,   138,
     126,    78,   139,   148,   126,   127,    43,    44,    47,   127,
      49,   104,   112,   105,    74,    73,   215,   118,   106,    45,
     119,    85,   134,   120,    43,    44,    46,    47,    48,    49,
      92,   104,    93,   105,    50,   186,    44,    45,   159,   164,
      40,    41,   107,   108,    46,    47,    48,    49,    45,    76,
     208,    77,    50,   209,    78,    46,    47,    48,    49,    40,
      42,    75,     1,   187,     2,     3,     4,   210,   152,   153,
     209,     5,    86,    87,    88,    89,    90,    91,    92,   216,
      93,    76,   209,    77,    81,    92,    78,    93,    79,    92,
      82,    93,   177,    92,     1,    93,   202,     3,     4,     1,
     214,    16,     3,     4,   154,   155,    84,   111,   128,   130,
     158,    78,   166,   184,   160,   161,   162,   176,   222,    19,
      20,   178,   170,   139,   129,   179,   167,   194,   199,   198,
      28,   203,   225,   211,   204,   213,   209,   226,   221,    67,
     223,   218,   147,   146,    70,   143,     0,     0,   144
};

static const yytype_int16 yycheck[] =
{
      29,    58,    10,     0,   124,    30,    26,   148,     5,    71,
       7,     4,   111,    10,    71,    61,     3,    78,     4,   118,
      14,    50,    68,     3,   160,   161,     6,     7,    25,   128,
      16,   172,    13,    94,    31,    14,    61,    23,    31,    25,
       3,     4,    36,    68,     0,    31,     0,   167,    29,   111,
      79,   187,    32,     7,   111,    75,   118,    36,     3,   158,
     122,   118,   124,    14,   110,   122,   128,   124,    31,   130,
     211,   128,   101,    31,     3,    23,    73,    25,   139,   104,
     105,    32,   107,   108,    32,   110,    35,    36,   208,     3,
     210,   120,     6,     7,     3,    24,   158,    26,    81,    82,
      29,   158,   222,    13,     3,   167,   226,     6,     7,     8,
     167,    10,    11,    12,   122,   176,    99,    13,    32,   148,
      13,    31,    23,    14,    25,    24,    32,    26,    24,    35,
      26,    32,    29,    29,    33,    31,    29,    36,    31,    29,
      39,    32,   171,   172,    27,    28,   208,     3,   210,     3,
     179,   208,     8,   210,    10,    11,    33,    24,   187,    26,
     222,    29,    29,    31,   226,   222,     3,     4,    24,   226,
      26,    23,    32,    25,     3,    35,   205,    33,    30,    16,
      36,    15,   211,    39,     3,     4,    23,    24,    25,    26,
      23,    23,    25,    25,    31,     3,     4,    16,    30,    36,
      35,    36,    27,    28,    23,    24,    25,    26,    16,    24,
      32,    26,    31,    35,    29,    23,    24,    25,    26,    35,
      36,     3,     3,    31,     5,     6,     7,    32,   104,   105,
      35,    12,    17,    18,    19,    20,    21,    22,    23,    32,
      25,    24,    35,    26,     3,    23,    29,    25,    31,    23,
       3,    25,    30,    23,     3,    25,    30,     6,     7,     3,
      30,     5,     6,     7,   107,   108,    14,    33,    33,    29,
      33,    29,    34,    34,    31,    31,    31,    29,     9,     7,
      10,    32,    36,    29,    73,    35,   122,    34,    30,    34,
      17,    32,   223,    36,    34,    32,    35,    32,    36,    31,
      36,   209,    98,    95,    33,    84,    -1,    -1,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    41,    42,    43,    44,
      50,    51,    52,    53,    54,     3,     5,    54,     0,    43,
      44,    51,     3,    60,    61,    31,     3,    55,    55,    13,
      29,    31,    56,    35,    36,    32,    45,    46,    54,    56,
      35,    36,    36,     3,     4,    16,    23,    24,    25,    26,
      31,    67,    68,    69,    73,    75,    77,    78,    79,    80,
       4,    31,    57,    58,    59,    79,    32,    45,    29,     3,
      61,    33,    32,    35,     3,     3,    24,    26,    29,    31,
      81,     3,     3,    67,    14,    15,    17,    18,    19,    20,
      21,    22,    23,    25,    70,    74,    27,    28,    76,     3,
       4,    31,    80,    57,    23,    25,    30,    27,    28,     4,
      31,    33,    32,    57,     3,     8,    10,    11,    33,    36,
      39,    49,    50,    54,    62,    63,    78,    80,    33,    46,
      29,    47,    56,    73,    67,    71,    72,    24,    26,    29,
      81,    81,    32,    68,    69,    73,    75,    77,    31,    81,
      67,    32,    58,    58,    59,    59,    57,    49,    33,    30,
      31,    31,    31,    49,    36,    67,    34,    62,     3,    63,
      36,    13,    31,    49,    48,    73,    29,    30,    32,    35,
      73,    71,    32,    32,    34,    49,     3,    31,    65,    66,
      67,    65,    64,    65,    34,    36,    67,    71,    34,    30,
      73,    67,    30,    32,    34,    13,    65,    67,    32,    35,
      32,    36,    36,    32,    30,    67,    32,    63,    66,    63,
      71,    36,     9,    36,    63,    64,    32,    63
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 2:
#line 167 "parser.y"
    { (yyval.node)=Allocate(PROGRAM_NODE);  makeChild((yyval.node),(yyvsp[(1) - (1)].node)); prog=(yyval.node);;}
    break;

  case 3:
#line 168 "parser.y"
    { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);;}
    break;

  case 4:
#line 172 "parser.y"
    {
                        (yyval.node) = makeSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
                    ;}
    break;

  case 5:
#line 176 "parser.y"
    {
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                    ;}
    break;

  case 6:
#line 182 "parser.y"
    {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[(1) - (2)].node)), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 7:
#line 186 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 8:
#line 192 "parser.y"
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[(4) - (8)].node));
                        makeFamily((yyval.node), 4, (yyvsp[(1) - (8)].node), makeIDNode((yyvsp[(2) - (8)].lexeme), NORMAL_ID), parameterList, (yyvsp[(7) - (8)].node));
                    ;}
    break;

  case 9:
#line 199 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[(4) - (8)].node));
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[(2) - (8)].lexeme), NORMAL_ID), parameterList, (yyvsp[(7) - (8)].node));
                    ;}
    break;

  case 10:
#line 207 "parser.y"
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, (yyvsp[(1) - (7)].node), makeIDNode((yyvsp[(2) - (7)].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[(6) - (7)].node));
                    ;}
    break;

  case 11:
#line 213 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[(2) - (7)].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[(6) - (7)].node));
                    ;}
    break;

  case 12:
#line 222 "parser.y"
    {
                    (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 13:
#line 226 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node)= (yyvsp[(1) - (1)].node);
                    
                ;}
    break;

  case 14:
#line 234 "parser.y"
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (2)].node), makeIDNode((yyvsp[(2) - (2)].lexeme), NORMAL_ID));
                ;}
    break;

  case 15:
#line 239 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), makeChild(makeIDNode((yyvsp[(2) - (3)].lexeme), ARRAY_ID), (yyvsp[(3) - (3)].node)));
                ;}
    break;

  case 16:
#line 246 "parser.y"
    {
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 17:
#line 250 "parser.y"
    {
                    (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 18:
#line 256 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 19:
#line 261 "parser.y"
    {
                    (yyval.node) = Allocate(NUL_NODE); 
                ;}
    break;

  case 20:
#line 267 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[(1) - (2)].node)), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[(2) - (2)].node)));
                    ;}
    break;

  case 21:
#line 273 "parser.y"
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[(1) - (1)].node)));
                    ;}
    break;

  case 22:
#line 278 "parser.y"
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[(1) - (1)].node)));
                    ;}
    break;

  case 23:
#line 282 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                    ;}
    break;

  case 24:
#line 289 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = makeSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 25:
#line 294 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node)  = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 26:
#line 301 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 27:
#line 305 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 28:
#line 311 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 29:
#line 317 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode("void", NORMAL_ID), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 30:
#line 325 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
                ;}
    break;

  case 31:
#line 333 "parser.y"
    {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);  
                ;}
    break;

  case 32:
#line 337 "parser.y"
    {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                ;}
    break;

  case 33:
#line 341 "parser.y"
    {
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                ;}
    break;

  case 34:
#line 347 "parser.y"
    {
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                ;}
    break;

  case 35:
#line 351 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), makeIDNode((yyvsp[(3) - (3)].lexeme), NORMAL_ID));
                ;}
    break;

  case 36:
#line 356 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), makeChild(makeIDNode((yyvsp[(3) - (4)].lexeme), ARRAY_ID), (yyvsp[(4) - (4)].node)));
                ;}
    break;

  case 37:
#line 361 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[(1) - (2)].lexeme), ARRAY_ID), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 38:
#line 367 "parser.y"
    {
                    /*FINSH*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 39:
#line 375 "parser.y"
    {
                    (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 40:
#line 380 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 41:
#line 385 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 42:
#line 391 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 43:
#line 397 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 44:
#line 403 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 45:
#line 409 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 46:
#line 416 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[(1) - (1)].const1);
                ;}
    break;

  case 47:
#line 422 "parser.y"
    {
                    AST_NODE* const_node = Allocate(CONST_VALUE_NODE);
                    const_node->semantic_value.const1=(yyvsp[(2) - (2)].const1);
                    (yyval.node) = makeChild((yyvsp[(1) - (2)].node), const_node);
                ;}
    break;

  case 48:
#line 428 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 49:
#line 433 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 50:
#line 440 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                    ;}
    break;

  case 51:
#line 445 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                    ;}
    break;

  case 52:
#line 452 "parser.y"
    {
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                ;}
    break;

  case 53:
#line 456 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[(1) - (2)].lexeme), ARRAY_ID), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 54:
#line 461 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[(1) - (3)].lexeme), WITH_INIT_ID), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 55:
#line 468 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 56:
#line 473 "parser.y"
    {
                    /*FINSH*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 57:
#line 482 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 58:
#line 488 "parser.y"
    {
                    (yyval.node) = makeFamily(makeStmtNode(WHILE_STMT),2 , (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
                ;}
    break;

  case 59:
#line 492 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(FOR_STMT), 4, (yyvsp[(3) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(9) - (9)].node));
                ;}
    break;

  case 60:
#line 497 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(ASSIGN_STMT), 2, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 61:
#line 503 "parser.y"
    {
                    (yyval.node) = makeFamily(makeStmtNode(IF_STMT), 3, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node),  Allocate(NUL_NODE));
                ;}
    break;

  case 62:
#line 508 "parser.y"
    {
                    (yyval.node) = makeFamily(makeStmtNode(IF_STMT), 3, (yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node));
                ;}
    break;

  case 63:
#line 513 "parser.y"
    {
                    (yyval.node) = makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, (yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node));
                ;}
    break;

  case 64:
#line 517 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = Allocate(NUL_NODE);
                ;}
    break;

  case 65:
#line 522 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeStmtNode(RETURN_STMT), Allocate(NUL_NODE));
                ;}
    break;

  case 66:
#line 527 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeStmtNode(RETURN_STMT), (yyvsp[(2) - (3)].node));
                ;}
    break;

  case 67:
#line 532 "parser.y"
    {
                    (yyval.node) = makeChild(makeStmtNode(DOUBLE_ADD_STMT), (yyvsp[(1) - (2)].node));
                ;}
    break;

  case 68:
#line 538 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = makeChild(Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE), (yyvsp[(1) - (1)].node));
                     ;}
    break;

  case 69:
#line 543 "parser.y"
    {
                         (yyval.node) = Allocate(NUL_NODE); 
                     ;}
    break;

  case 70:
#line 549 "parser.y"
    {
                                    /*FINISH*/
                                    (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                                ;}
    break;

  case 71:
#line 554 "parser.y"
    {
                                    /*FINISH*/
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 72:
#line 567 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = makeFamily(makeStmtNode(ASSIGN_STMT), 2, makeIDNode((yyvsp[(1) - (3)].lexeme), NORMAL_ID), (yyvsp[(3) - (3)].node));
                    ;}
    break;

  case 73:
#line 572 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                    ;}
    break;

  case 74:
#line 577 "parser.y"
    {
                        (yyval.node) = (yyvsp[(2) - (3)].node);
                    ;}
    break;

  case 75:
#line 583 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 76:
#line 587 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    (yyval.node) = makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 77:
#line 594 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 78:
#line 599 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeExprNode(BINARY_OPERATION, BINARY_OP_AND), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 79:
#line 606 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                    ;}
    break;

  case 80:
#line 611 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = makeFamily((yyvsp[(2) - (3)].node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                    ;}
    break;

  case 81:
#line 618 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                ;}
    break;

  case 82:
#line 623 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                ;}
    break;

  case 83:
#line 628 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                ;}
    break;

  case 84:
#line 633 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                ;}
    break;

  case 85:
#line 638 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                ;}
    break;

  case 86:
#line 643 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                ;}
    break;

  case 87:
#line 651 "parser.y"
    {
                        /*FINISH*/
                        (yyval.node) = makeChild(Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE), (yyvsp[(1) - (1)].node));
                    ;}
    break;

  case 88:
#line 656 "parser.y"
    {
                        (yyval.node) = Allocate(NUL_NODE);
                    ;}
    break;

  case 89:
#line 662 "parser.y"
    {
                                    /*FINISH*/
                                    (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                                ;}
    break;

  case 90:
#line 667 "parser.y"
    {
                                    /*FINISH*/
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 91:
#line 674 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily((yyvsp[(2) - (3)].node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 92:
#line 679 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 93:
#line 686 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                ;}
    break;

  case 94:
#line 690 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                ;}
    break;

  case 95:
#line 696 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily((yyvsp[(2) - (3)].node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 96:
#line 701 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 97:
#line 708 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                ;}
    break;

  case 98:
#line 713 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                ;}
    break;

  case 99:
#line 720 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 100:
#line 726 "parser.y"
    {   
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 101:
#line 731 "parser.y"
    {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[(1) - (1)].const1);
                ;}
    break;

  case 102:
#line 737 "parser.y"
    {
                    AST_NODE* const_node = Allocate(CONST_VALUE_NODE);
                    const_node->semantic_value.const1=(yyvsp[(2) - (2)].const1);
                    (yyval.node) = makeChild((yyvsp[(1) - (2)].node), const_node);
                ;}
    break;

  case 103:
#line 743 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, makeIDNode((yyvsp[(1) - (4)].lexeme), NORMAL_ID), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 104:
#line 749 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[(1) - (5)].node), makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, makeIDNode((yyvsp[(2) - (5)].lexeme), NORMAL_ID), (yyvsp[(4) - (5)].node)));
                ;}
    break;

  case 105:
#line 754 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 106:
#line 760 "parser.y"
    {
                    (yyval.node) = makeChild((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 107:
#line 764 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 108:
#line 770 "parser.y"
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_PP_ID), makeIDNode((yyvsp[(2) - (2)].lexeme), NORMAL_ID));
                    ;}
    break;

  case 109:
#line 774 "parser.y"
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_PP), makeIDNode((yyvsp[(1) - (2)].lexeme), NORMAL_ID));
                    ;}
    break;

  case 110:
#line 778 "parser.y"
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_MM_ID), makeIDNode((yyvsp[(2) - (2)].lexeme), NORMAL_ID));
                    ;}
    break;

  case 111:
#line 782 "parser.y"
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_MM), makeIDNode((yyvsp[(1) - (2)].lexeme), NORMAL_ID));
                    ;}
    break;

  case 112:
#line 786 "parser.y"
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_PP_ID), makeChild(makeIDNode((yyvsp[(2) - (3)].lexeme), ARRAY_ID), (yyvsp[(3) - (3)].node)) );
                    ;}
    break;

  case 113:
#line 790 "parser.y"
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_PP), makeChild(makeIDNode((yyvsp[(1) - (3)].lexeme), ARRAY_ID), (yyvsp[(2) - (3)].node)) );
                    ;}
    break;

  case 114:
#line 794 "parser.y"
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_MM_ID), makeChild(makeIDNode((yyvsp[(2) - (3)].lexeme), ARRAY_ID), (yyvsp[(3) - (3)].node)) );
                    ;}
    break;

  case 115:
#line 798 "parser.y"
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_MM), makeChild(makeIDNode((yyvsp[(1) - (3)].lexeme), ARRAY_ID), (yyvsp[(2) - (3)].node)) );
                    ;}
    break;

  case 116:
#line 804 "parser.y"
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                ;}
    break;

  case 117:
#line 808 "parser.y"
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_POSITIVE);
                ;}
    break;

  case 118:
#line 812 "parser.y"
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                ;}
    break;

  case 119:
#line 819 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                ;}
    break;

  case 120:
#line 824 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[(1) - (2)].lexeme), ARRAY_ID),(yyvsp[(2) - (2)].node));
                ;}
    break;

  case 121:
#line 832 "parser.y"
    {
                    /*FINISH*/
                   (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node)); 
                ;}
    break;

  case 122:
#line 837 "parser.y"
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2661 "parser.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 844 "parser.y"


#include "lex.yy.c"
main (argc, argv)
int argc;
char *argv[];
  {
     yyin = fopen(argv[1],"r");
     yyparse();
	 printf("%s\n", "Parsing completed. No errors found.");
	 printGV(prog, NULL);
  } /* main */


int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }
 

