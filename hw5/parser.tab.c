/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 4 "parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"
#include "symbolTable.h"
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


#line 173 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 113 "parser.y" /* yacc.c:355  */

    char *lexeme;
    CON_Type  *const1;
    AST_NODE  *node;

#line 259 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 276 "parser.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   168,   168,   169,   172,   176,   182,   186,   192,   199,
     207,   213,   222,   226,   234,   239,   246,   250,   256,   262,
     267,   273,   278,   283,   289,   294,   301,   305,   311,   317,
     325,   333,   337,   341,   347,   351,   356,   361,   367,   375,
     381,   385,   392,   397,   404,   409,   416,   421,   427,   433,
     439,   445,   453,   459,   465,   470,   477,   482,   489,   493,
     498,   505,   510,   519,   525,   529,   534,   539,   544,   550,
     554,   559,   564,   569,   575,   581,   587,   592,   597,   604,
     609,   614,   620,   624,   631,   636,   643,   648,   655,   660,
     665,   670,   675,   680,   688,   694,   699,   704,   711,   716,
     723,   727,   733,   738,   745,   750,   757,   763,   768,   774,
     780,   786,   791,   797,   801,   807,   811,   815,   819,   823,
     827,   831,   835,   841,   845,   849,   856,   861,   869,   874
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "decl", "type_decl", "var_decl", "type", "id_list", "dim_decl",
  "crelop_expr", "crelop_term", "crelop_factor", "cexpr", "mcexpr",
  "cfactor", "init_id_list", "init_id", "stmt_list", "stmt", "test",
  "assign_expr_list", "nonempty_assign_expr_list", "assign_expr",
  "relop_expr", "relop_term", "relop_factor", "rel_op", "relop_expr_list",
  "nonempty_relop_expr_list", "expr", "add_op", "term", "mul_op", "factor",
  "double_add_id", "unary_op", "var_ref", "dim_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF -156

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-156)))

#define YYTABLE_NINF -34

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     225,  -156,    35,  -156,  -156,   259,    50,   225,  -156,  -156,
     225,  -156,  -156,  -156,    67,    48,    86,    86,  -156,  -156,
    -156,  -156,   159,    77,  -156,    17,   116,   191,   199,   194,
     113,    22,   125,   118,  -156,   130,   152,  -156,   165,   125,
     186,  -156,  -156,   232,  -156,  -156,  -156,   192,  -156,   196,
     194,   190,   193,  -156,   221,   245,  -156,  -156,    92,  -156,
    -156,   113,    13,   200,  -156,   230,   247,  -156,    26,   212,
     201,   113,    63,  -156,   170,   248,    97,   239,   116,  -156,
    -156,   194,   194,   117,   249,   249,     1,   194,   194,  -156,
    -156,  -156,  -156,  -156,  -156,  -156,  -156,   194,   194,  -156,
    -156,   194,   104,  -156,   194,  -156,   107,   113,  -156,   113,
     113,   113,   113,   113,   113,  -156,   113,   170,   250,    85,
      15,   251,   253,   254,   170,  -156,   124,   252,   170,   118,
      98,  -156,   243,    27,   170,  -156,   194,   258,   125,    88,
     190,   256,   255,  -156,  -156,   194,   260,   260,  -156,   193,
    -156,   160,   245,  -156,   194,   260,    66,  -156,   200,  -156,
     247,   247,   246,  -156,  -156,   168,   257,   170,  -156,   198,
     198,   198,   261,  -156,    -4,  -156,    98,   187,  -156,  -156,
     194,   194,   262,   263,   160,   194,  -156,  -156,   194,   112,
     265,  -156,  -156,  -156,   264,   140,   198,   267,  -156,   190,
     222,  -156,   244,   266,  -156,  -156,    42,   268,  -156,  -156,
     182,   190,  -156,  -156,  -156,   194,   235,     1,    98,    98,
     198,   194,  -156,   269,  -156,   190,  -156,   283,  -156,  -156,
     270,  -156,    98,   198,  -156,   271,    98,  -156
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    33,     0,    31,    32,     0,     0,     2,     5,     7,
       0,    25,    26,    27,     0,     0,     0,     0,     1,     4,
       6,    24,    58,     0,    56,     0,    34,     0,     0,     0,
       0,     0,    59,     0,    30,     0,     0,    13,     0,    37,
       0,    29,    28,   126,   108,   123,   124,     0,   125,     0,
       0,    60,    82,    84,    86,    99,   103,   114,     0,   112,
      52,     0,     0,    40,    42,    44,    48,    51,     0,     0,
       0,     0,    58,    57,    23,     0,     0,    14,    35,   116,
     118,     0,    95,   127,   115,   117,     0,     0,     0,    88,
      91,    92,    93,    89,    90,   100,   101,     0,     0,   104,
     105,     0,   126,   109,     0,   113,     0,     0,    38,     0,
       0,     0,     0,     0,     0,    53,     0,    23,     0,     0,
     126,     0,     0,     0,    23,    70,     0,     0,    22,     0,
      21,    62,     0,     0,    23,    12,    19,    15,    36,     0,
      97,     0,    94,   120,   122,     0,   119,   121,   106,    83,
      85,    87,    98,   102,    95,   127,     0,    54,    41,    43,
      46,    47,    45,    49,    50,     0,     0,    23,    39,     0,
       0,    76,     0,    71,     0,    11,    20,   126,    61,    73,
       0,    95,     0,     0,    18,     0,   129,   110,     0,     0,
       0,   107,    55,    10,     0,   126,     0,     0,    74,    80,
       0,    78,     0,    75,    63,    72,     0,     0,     9,    16,
       0,    96,   128,   111,     8,     0,     0,    80,     0,     0,
       0,    95,    66,     0,    17,    79,    81,    67,    64,    77,
       0,    69,     0,    76,    68,     0,     0,    65
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -156,  -156,  -156,   287,   292,   273,   231,  -156,  -156,   -98,
     158,    -8,  -156,  -156,     6,   291,   -17,   238,   203,   202,
     -53,   149,   163,  -156,   279,   185,  -125,  -156,    81,  -148,
    -155,   -29,   228,   229,   272,  -147,  -156,   -94,  -156,   218,
    -156,   217,   -62,   -26,   -57,   -38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    36,    37,   137,   183,   127,
     128,    11,    12,    13,   129,    27,    32,    62,    63,    64,
      65,    66,    67,    23,    24,   130,   131,   197,   202,   203,
     201,   199,    52,    53,    97,   141,   142,    54,    98,    55,
     101,    56,    57,    58,    59,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   105,    21,   151,    68,   178,    14,   190,   106,    39,
      87,    17,   132,    14,   198,    87,    14,   133,   -33,   166,
       1,    86,   200,     3,     4,     1,   172,   107,     3,     4,
     115,    38,   205,   148,   207,    68,   182,    38,    15,    79,
     180,    80,   184,   108,    81,    68,   146,   147,   216,    35,
      18,   178,   139,   140,    69,   132,    87,   116,   181,   162,
     133,   138,   132,   165,   155,   229,   132,   133,   132,   194,
      22,   133,   132,   133,   230,   156,    29,   133,   222,    25,
      87,    68,    38,    68,    68,    68,    68,    68,    68,    26,
      68,   210,    30,   227,   228,   102,   103,   174,   191,   107,
       1,   177,    87,     3,     4,   132,   121,   234,   122,   123,
     133,   237,    33,    34,   132,   168,   189,    60,   186,   133,
      21,    72,    47,   104,    49,   140,    87,    43,    44,    45,
     110,   124,   111,    81,   125,   154,    46,   126,    48,   157,
      45,   143,   212,   144,    61,    30,   145,    46,    47,    48,
      49,   206,   140,   215,    71,    50,   132,   132,    10,   211,
     173,   133,   133,    74,    79,    10,    80,   217,    77,    81,
     132,    82,    29,   120,   132,   133,     3,     4,   121,   133,
     122,   123,     5,    95,    75,    96,   225,    76,    30,    78,
      31,   110,   140,   111,    47,    84,    49,    43,    44,    85,
     192,   195,    44,   124,    87,    95,   125,    96,    88,   126,
      45,    79,   224,    80,    45,   109,    81,    46,    47,    48,
      49,    46,    47,    48,    49,    50,    40,    41,     1,   196,
       2,     3,     4,   118,    40,    42,    76,     5,    89,    90,
      91,    92,    93,    94,    95,   117,    96,    89,    90,    91,
      92,    93,    94,   110,   219,   111,    79,   220,    80,   160,
     161,    81,     1,    82,    16,     3,     4,   226,   136,   110,
     220,   111,    99,   100,   113,   114,   163,   164,    81,   179,
     221,   134,   169,   167,   170,   171,   175,   185,   187,   145,
     188,   193,   232,   209,    19,   204,   208,   213,   214,   218,
     223,   220,    20,   236,    70,   231,   233,   135,    28,   119,
     158,   159,    73,   176,   235,   149,   152,   150,   153,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112
};

static const yytype_int16 yycheck[] =
{
      29,    58,    10,    97,    30,   130,     0,   154,    61,    26,
      14,     5,    74,     7,   169,    14,    10,    74,     3,   117,
       3,    50,   170,     6,     7,     3,   124,    14,     6,     7,
       4,    25,    36,    32,   181,    61,   134,    31,     3,    24,
      13,    26,   136,    30,    29,    71,    84,    85,   196,    32,
       0,   176,    81,    82,    32,   117,    14,    31,    31,   112,
     117,    78,   124,   116,   102,   220,   128,   124,   130,   167,
       3,   128,   134,   130,   221,   104,    13,   134,    36,    31,
      14,   107,    76,   109,   110,   111,   112,   113,   114,     3,
     116,   185,    29,   218,   219,     3,     4,   126,    32,    14,
       3,     3,    14,     6,     7,   167,     8,   232,    10,    11,
     167,   236,    35,    36,   176,    30,   145,     4,    30,   176,
     128,     3,    24,    31,    26,   154,    14,     3,     4,    16,
      23,    33,    25,    29,    36,    31,    23,    39,    25,    32,
      16,    24,    30,    26,    31,    29,    29,    23,    24,    25,
      26,   180,   181,    13,    29,    31,   218,   219,     0,   188,
      36,   218,   219,    33,    24,     7,    26,   196,     3,    29,
     232,    31,    13,     3,   236,   232,     6,     7,     8,   236,
      10,    11,    12,    23,    32,    25,   215,    35,    29,     3,
      31,    23,   221,    25,    24,     3,    26,     3,     4,     3,
      32,     3,     4,    33,    14,    23,    36,    25,    15,    39,
      16,    24,    30,    26,    16,    15,    29,    23,    24,    25,
      26,    23,    24,    25,    26,    31,    35,    36,     3,    31,
       5,     6,     7,    32,    35,    36,    35,    12,    17,    18,
      19,    20,    21,    22,    23,    33,    25,    17,    18,    19,
      20,    21,    22,    23,    32,    25,    24,    35,    26,   110,
     111,    29,     3,    31,     5,     6,     7,    32,    29,    23,
      35,    25,    27,    28,    27,    28,   113,   114,    29,    36,
      36,    33,    31,    33,    31,    31,    34,    29,    32,    29,
      35,    34,     9,    30,     7,    34,    34,    32,    34,    32,
      32,    35,    10,    32,    31,    36,    36,    76,    17,    71,
     107,   109,    33,   128,   233,    87,    98,    88,   101,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    41,    42,    43,    44,
      50,    51,    52,    53,    54,     3,     5,    54,     0,    43,
      44,    51,     3,    63,    64,    31,     3,    55,    55,    13,
      29,    31,    56,    35,    36,    32,    45,    46,    54,    56,
      35,    36,    36,     3,     4,    16,    23,    24,    25,    26,
      31,    71,    72,    73,    77,    79,    81,    82,    83,    84,
       4,    31,    57,    58,    59,    60,    61,    62,    83,    32,
      45,    29,     3,    64,    33,    32,    35,     3,     3,    24,
      26,    29,    31,    85,     3,     3,    71,    14,    15,    17,
      18,    19,    20,    21,    22,    23,    25,    74,    78,    27,
      28,    80,     3,     4,    31,    84,    60,    14,    30,    15,
      23,    25,    74,    27,    28,     4,    31,    33,    32,    57,
       3,     8,    10,    11,    33,    36,    39,    49,    50,    54,
      65,    66,    82,    84,    33,    46,    29,    47,    56,    71,
      71,    75,    76,    24,    26,    29,    85,    85,    32,    72,
      73,    77,    79,    81,    31,    85,    71,    32,    58,    59,
      61,    61,    60,    62,    62,    60,    49,    33,    30,    31,
      31,    31,    49,    36,    71,    34,    65,     3,    66,    36,
      13,    31,    49,    48,    77,    29,    30,    32,    35,    71,
      75,    32,    32,    34,    49,     3,    31,    67,    70,    71,
      69,    70,    68,    69,    34,    36,    71,    75,    34,    30,
      77,    71,    30,    32,    34,    13,    69,    71,    32,    32,
      35,    36,    36,    32,    30,    71,    32,    66,    66,    70,
      75,    36,     9,    36,    66,    68,    32,    66
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    42,    42,    43,    43,    44,    44,
      44,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    49,    49,    49,    50,    50,    51,    51,    52,    52,
      53,    54,    54,    54,    55,    55,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    60,    60,    60,    61,
      61,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      64,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    67,    68,    68,    69,    69,    70,
      70,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      74,    74,    74,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    82,    82,    82,    82,    82,
      82,    82,    82,    83,    83,    83,    84,    84,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     3,     4,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     1,     4,     4,
       3,     1,     1,     1,     1,     3,     4,     2,     3,     4,
       1,     3,     1,     3,     1,     3,     3,     3,     1,     3,
       3,     1,     1,     2,     3,     4,     1,     3,     1,     2,
       3,     2,     1,     3,     5,     9,     4,     5,     7,     5,
       1,     2,     3,     2,     1,     1,     0,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     3,     1,     3,     1,
       1,     1,     3,     1,     1,     1,     3,     4,     1,     2,
       4,     5,     1,     2,     1,     2,     2,     2,     2,     3,
       3,     3,     3,     1,     1,     1,     1,     2,     4,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 168 "parser.y" /* yacc.c:1646  */
    { (yyval.node)=Allocate(PROGRAM_NODE);  makeChild((yyval.node),(yyvsp[0].node)); prog=(yyval.node);}
#line 1540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);}
#line 1546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 173 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                    }
#line 1554 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 177 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1562 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 183 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), (yyvsp[0].node));
                }
#line 1570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 187 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 193 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, (yyvsp[-7].node), makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
                    }
#line 1589 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 200 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
                    }
#line 1601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 208 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, (yyvsp[-6].node), makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
                    }
#line 1611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 214 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
                    }
#line 1622 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 223 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1630 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 227 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node)= (yyvsp[0].node);
                    
                }
#line 1640 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 235 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 240 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 247 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1667 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 251 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 257 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1684 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 262 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 1692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 268 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 274 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 279 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 283 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                    }
#line 1729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 290 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 295 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node)  = (yyvsp[0].node);
                }
#line 1747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 302 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1755 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 306 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1763 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 312 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 318 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode("void", NORMAL_ID), (yyvsp[-1].node));
                }
#line 1783 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 326 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 334 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);  
                }
#line 1801 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 338 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                }
#line 1809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 342 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1817 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 348 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1825 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 352 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[-2].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1834 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 357 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[-3].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 362 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 1852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 368 "parser.y" /* yacc.c:1646  */
    {
                    /*FINSH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 376 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 382 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 386 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    (yyval.node) = makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 393 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 398 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeExprNode(BINARY_OPERATION, BINARY_OP_AND), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 405 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 410 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 1922 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 417 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1931 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 422 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1941 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 428 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1950 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 434 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 440 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 446 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1979 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 454 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 1989 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 460 "parser.y" /* yacc.c:1646  */
    {
                    AST_NODE* const_node = Allocate(CONST_VALUE_NODE);
                    const_node->semantic_value.const1=(yyvsp[0].const1);
                    (yyval.node) = makeChild((yyvsp[-1].node), const_node);
                }
#line 1999 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 466 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2008 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 471 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2017 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 478 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2026 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 483 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2035 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 490 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2043 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 494 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 2052 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 499 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-2].lexeme), WITH_INIT_ID), (yyvsp[0].node));
                }
#line 2061 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 506 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 2070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 511 "parser.y" /* yacc.c:1646  */
    {
                    /*FINSH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2079 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 520 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 526 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeFamily(makeStmtNode(WHILE_STMT),2 , (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2096 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 530 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(FOR_STMT), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2105 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 535 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(ASSIGN_STMT), 2, (yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 540 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-2].node), (yyvsp[0].node), Allocate(NUL_NODE));
                }
#line 2123 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 545 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2132 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 551 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, (yyvsp[-4].node), (yyvsp[-2].node));
                }
#line 2140 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 555 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = Allocate(NUL_NODE);
                }
#line 2149 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 560 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeStmtNode(RETURN_STMT), Allocate(NUL_NODE));
                }
#line 2158 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 565 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeStmtNode(RETURN_STMT), (yyvsp[-1].node));
                }
#line 2167 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 570 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeChild(makeStmtNode(DOUBLE_ADD_STMT), (yyvsp[-1].node));
                }
#line 2175 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 576 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2183 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 582 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeChild(Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE), (yyvsp[0].node));
                     }
#line 2192 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 587 "parser.y" /* yacc.c:1646  */
    {
                         (yyval.node) = Allocate(NUL_NODE); 
                     }
#line 2200 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 593 "parser.y" /* yacc.c:1646  */
    {
                                    /*FINISH*/
                                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                }
#line 2209 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 598 "parser.y" /* yacc.c:1646  */
    {
                                    /*FINISH*/
                                    (yyval.node) = (yyvsp[0].node);
                                }
#line 2218 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 605 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeFamily(makeStmtNode(ASSIGN_STMT), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[0].node));
                    }
#line 2227 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 610 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2236 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 615 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[-1].node);
                    }
#line 2244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 621 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 625 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    (yyval.node) = makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 632 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2270 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 637 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeExprNode(BINARY_OPERATION, BINARY_OP_AND), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2279 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 644 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2288 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 649 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2297 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 656 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
#line 2306 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 661 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
#line 2315 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 666 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
#line 2324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 671 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
#line 2333 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 676 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
#line 2342 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 681 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
#line 2351 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 689 "parser.y" /* yacc.c:1646  */
    {
                        /*FINISH*/
                        (yyval.node) = makeChild(Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE), (yyvsp[0].node));
                    }
#line 2360 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 694 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = Allocate(NUL_NODE);
                    }
#line 2368 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 700 "parser.y" /* yacc.c:1646  */
    {
                                    /*FINISH*/
                                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                }
#line 2377 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 705 "parser.y" /* yacc.c:1646  */
    {
                                    /*FINISH*/
                                    (yyval.node) = (yyvsp[0].node);
                                }
#line 2386 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 712 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2395 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 717 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 724 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
#line 2412 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 728 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
#line 2420 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 734 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2429 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 739 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 746 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
#line 2447 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 751 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
#line 2456 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 758 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2465 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 764 "parser.y" /* yacc.c:1646  */
    {   
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 769 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 2483 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 775 "parser.y" /* yacc.c:1646  */
    {
                    AST_NODE* const_node = Allocate(CONST_VALUE_NODE);
                    const_node->semantic_value.const1=(yyvsp[0].const1);
                    (yyval.node) = makeChild((yyvsp[-1].node), const_node);
                }
#line 2493 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 781 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                }
#line 2502 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 787 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[-4].node), makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node)));
                }
#line 2511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 792 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2520 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 798 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeChild((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 2528 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 802 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2536 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 808 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_PP_ID), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 2544 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 812 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_PP), makeIDNode((yyvsp[-1].lexeme), NORMAL_ID));
                    }
#line 2552 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 816 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_MM_ID), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 2560 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 820 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_MM), makeIDNode((yyvsp[-1].lexeme), NORMAL_ID));
                    }
#line 2568 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 824 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_PP_ID), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)) );
                    }
#line 2576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 828 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_PP), makeChild(makeIDNode((yyvsp[-2].lexeme), ARRAY_ID), (yyvsp[-1].node)) );
                    }
#line 2584 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 832 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_MM_ID), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)) );
                    }
#line 2592 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 836 "parser.y" /* yacc.c:1646  */
    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_MM), makeChild(makeIDNode((yyvsp[-2].lexeme), ARRAY_ID), (yyvsp[-1].node)) );
                    }
#line 2600 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 842 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                }
#line 2608 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 846 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_POSITIVE);
                }
#line 2616 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 850 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                }
#line 2624 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 857 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 862 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID),(yyvsp[0].node));
                }
#line 2642 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 870 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                   (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node)); 
                }
#line 2651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 875 "parser.y" /* yacc.c:1646  */
    {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2660 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2664 "parser.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 882 "parser.y" /* yacc.c:1906  */


#include "lex.yy.c"
int main (argc, argv)
int argc;
char *argv[];
  {
     yyin = fopen(argv[1],"r");
     yyparse();
        printGV(prog, NULL);
     initializeSymbolTable();
     
     semanticAnalysis(prog);
     
     symbolTableEnd();
     codeGen(prog);
     if (!g_anyErrorOccur) {
        printf("Parsing completed. No errors found.\n");
     }
  } /* main */


int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }
