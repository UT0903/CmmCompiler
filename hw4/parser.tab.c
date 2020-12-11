/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "parser.y"

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


#line 177 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 113 "parser.y"

    char *lexeme;
    CON_Type  *const1;
    AST_NODE  *node;

#line 275 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   363

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  246

#define YYUNDEFTOK  2
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
static const yytype_int16 yyrline[] =
{
       0,   168,   168,   169,   172,   176,   182,   186,   192,   199,
     207,   213,   222,   226,   234,   239,   246,   250,   256,   262,
     267,   273,   278,   283,   289,   294,   301,   305,   311,   317,
     325,   333,   337,   341,   347,   351,   356,   361,   367,   375,
     381,   385,   392,   397,   404,   409,   416,   421,   427,   433,
     439,   445,   453,   459,   465,   470,   477,   482,   489,   493,
     498,   505,   510,   519,   525,   529,   534,   539,   545,   550,
     555,   559,   564,   569,   574,   580,   586,   591,   596,   609,
     614,   619,   625,   629,   636,   641,   648,   653,   660,   665,
     670,   675,   680,   685,   693,   699,   704,   709,   716,   721,
     728,   732,   738,   743,   750,   755,   762,   768,   773,   779,
     785,   791,   796,   802,   806,   812,   816,   820,   824,   828,
     832,   836,   840,   846,   850,   854,   861,   866,   874,   879
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
  "cfactor", "init_id_list", "init_id", "stmt_list", "stmt",
  "assign_expr_list", "nonempty_assign_expr_list", "assign_expr",
  "relop_expr", "relop_term", "relop_factor", "rel_op", "relop_expr_list",
  "nonempty_relop_expr_list", "expr", "add_op", "term", "mul_op", "factor",
  "double_add_id", "unary_op", "var_ref", "dim_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF (-142)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-34)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     176,  -142,    23,  -142,  -142,   251,    32,   176,  -142,  -142,
     176,  -142,  -142,  -142,    67,    34,    91,    91,  -142,  -142,
    -142,  -142,    17,   121,  -142,    13,    80,   179,   234,   248,
      33,    44,    89,   127,  -142,   114,    -1,  -142,   162,    89,
     169,  -142,  -142,   187,  -142,  -142,  -142,   177,  -142,   186,
     248,   193,   206,  -142,   277,   249,  -142,  -142,     7,  -142,
    -142,    33,     9,   223,  -142,   286,   253,  -142,    10,   217,
      63,    33,    61,  -142,   198,   222,   189,   218,    80,  -142,
    -142,   248,   248,   119,   230,   230,    22,   248,   248,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,   248,   248,  -142,
    -142,   248,    76,  -142,   248,  -142,   152,    33,  -142,    33,
      33,    33,    33,    33,    33,  -142,    33,   198,   242,    85,
     120,   236,   258,   261,   198,  -142,    77,   250,   198,   127,
     209,  -142,   265,    11,   198,  -142,   248,   281,    89,   103,
     193,   282,   280,  -142,  -142,   248,   287,   287,  -142,   206,
    -142,   101,   249,  -142,   248,   287,    52,  -142,   223,  -142,
     253,   253,   146,  -142,  -142,   168,   283,   198,  -142,   262,
     262,   237,   284,  -142,    -8,  -142,   209,   203,  -142,  -142,
     248,   248,   285,   290,   101,   248,  -142,  -142,   248,   140,
     289,  -142,  -142,  -142,   288,   129,   262,   167,  -142,   193,
     204,   137,   127,   291,   293,  -142,  -142,     8,   292,  -142,
    -142,   200,   193,  -142,  -142,  -142,   248,   214,    22,   209,
     262,   209,   247,   248,  -142,   294,  -142,   193,  -142,   314,
    -142,  -142,   248,   295,  -142,   209,   296,   262,  -142,   262,
     297,   301,   209,   209,  -142,  -142
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
     126,     0,     0,     0,    23,    71,     0,     0,    22,     0,
      21,    62,     0,     0,    23,    12,    19,    15,    36,     0,
      97,     0,    94,   120,   122,     0,   119,   121,   106,    83,
      85,    87,    98,   102,    95,   127,     0,    54,    41,    43,
      46,    47,    45,    49,    50,     0,     0,    23,    39,     0,
       0,    76,     0,    72,     0,    11,    20,   126,    61,    74,
       0,    95,     0,     0,    18,     0,   129,   110,     0,     0,
       0,   107,    55,    10,     0,   126,     0,     0,    78,    80,
       0,   126,     0,     0,    75,    63,    73,     0,     0,     9,
      16,     0,    96,   128,   111,     8,     0,     0,    80,     0,
       0,     0,     0,    95,    67,     0,    17,    79,    81,    68,
      77,    64,    95,     0,    70,     0,     0,    76,    69,    76,
       0,     0,     0,     0,    65,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,  -142,   318,   316,   303,   259,  -142,  -142,   -99,
      62,    -7,  -142,  -142,     2,   319,   -21,   266,   231,   232,
     -53,   180,   199,   138,   306,   215,  -115,   -11,   -82,   122,
     -29,   257,   260,   298,  -141,  -142,   -93,  -142,   252,  -142,
     244,   -45,    25,   -57,    27
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    36,    37,   137,   183,   127,
     128,    11,    12,    13,   129,    27,    32,    62,    63,    64,
      65,    66,    67,    23,    24,   130,   131,   203,   204,   198,
     199,    52,    53,    97,   141,   142,    54,    98,    55,   101,
      56,    57,    58,    59,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   105,    14,    21,   151,    39,    87,    17,   106,    14,
     102,   103,    14,   190,   115,   178,     1,   133,   166,     3,
       4,    86,    87,   107,   180,   172,    15,    38,   206,   132,
      29,    75,    18,    38,    76,   182,    87,    60,   104,   108,
     208,   116,   181,   184,   224,    35,    30,     1,    31,    45,
       3,     4,   139,   140,   148,    68,    46,   138,    48,   162,
     133,   178,    10,   165,    61,    25,    87,   133,   194,    10,
      22,   133,   132,   133,    29,   156,    69,   133,    38,   132,
      43,    44,   233,   132,   191,   132,    68,   197,   200,   132,
      30,   236,   211,    45,    26,   118,    68,   174,    76,   107,
      46,    47,    48,    49,   229,    81,   231,   154,    50,    30,
     133,   146,   147,   173,   217,   168,   189,    87,    71,   133,
     238,    21,   132,   -33,    95,   140,    96,   244,   245,   155,
      72,   132,    68,   186,    68,    68,    68,    68,    68,    68,
     -33,    68,   216,   143,    79,   144,    80,    74,   145,    81,
     216,   207,   140,    79,    87,    80,    33,    34,    81,   212,
      82,    79,   133,    80,   133,    77,    81,   218,    82,   110,
     213,   111,    78,   202,   132,   110,   132,   111,   133,     1,
      84,     2,     3,     4,   157,   133,   133,   227,     5,    85,
     132,   110,     1,   111,   140,     3,     4,   132,   132,   219,
     192,   120,   220,   140,     3,     4,   121,    87,   122,   123,
       5,    79,   177,    80,    40,    41,    81,   121,    82,   122,
     123,    88,    47,    95,    49,    96,   240,    79,   241,    80,
     226,   124,    81,    47,   125,    49,   221,   126,   109,   220,
     201,    44,   124,     3,     4,   125,   228,   136,   126,   220,
     117,    43,    44,    45,     1,   134,    16,     3,     4,    81,
      46,    47,    48,    49,    45,   195,    44,   169,   196,    40,
      42,    46,    47,    48,    49,   167,    99,   100,    45,    50,
     113,   114,    33,   232,   175,    46,    47,    48,    49,   170,
     160,   161,   171,   196,    89,    90,    91,    92,    93,    94,
      95,   179,    96,    89,    90,    91,    92,    93,    94,   110,
     185,   111,   163,   164,   187,   188,   145,   193,   205,   209,
     210,   214,   215,   235,   225,    19,    20,   223,   220,   242,
     234,   237,   239,   243,    70,   135,    28,   119,   158,    73,
     222,   159,   230,   176,   149,   153,     0,     0,   150,     0,
     152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112
};

static const yytype_int16 yycheck[] =
{
      29,    58,     0,    10,    97,    26,    14,     5,    61,     7,
       3,     4,    10,   154,     4,   130,     3,    74,   117,     6,
       7,    50,    14,    14,    13,   124,     3,    25,    36,    74,
      13,    32,     0,    31,    35,   134,    14,     4,    31,    30,
     181,    31,    31,   136,    36,    32,    29,     3,    31,    16,
       6,     7,    81,    82,    32,    30,    23,    78,    25,   112,
     117,   176,     0,   116,    31,    31,    14,   124,   167,     7,
       3,   128,   117,   130,    13,   104,    32,   134,    76,   124,
       3,     4,   223,   128,    32,   130,    61,   169,   170,   134,
      29,   232,   185,    16,     3,    32,    71,   126,    35,    14,
      23,    24,    25,    26,   219,    29,   221,    31,    31,    29,
     167,    84,    85,    36,   196,    30,   145,    14,    29,   176,
     235,   128,   167,     3,    23,   154,    25,   242,   243,   102,
       3,   176,   107,    30,   109,   110,   111,   112,   113,   114,
       3,   116,    13,    24,    24,    26,    26,    33,    29,    29,
      13,   180,   181,    24,    14,    26,    35,    36,    29,   188,
      31,    24,   219,    26,   221,     3,    29,   196,    31,    23,
      30,    25,     3,   171,   219,    23,   221,    25,   235,     3,
       3,     5,     6,     7,    32,   242,   243,   216,    12,     3,
     235,    23,     3,    25,   223,     6,     7,   242,   243,    32,
      32,     3,    35,   232,     6,     7,     8,    14,    10,    11,
      12,    24,     3,    26,    35,    36,    29,     8,    31,    10,
      11,    15,    24,    23,    26,    25,   237,    24,   239,    26,
      30,    33,    29,    24,    36,    26,    32,    39,    15,    35,
       3,     4,    33,     6,     7,    36,    32,    29,    39,    35,
      33,     3,     4,    16,     3,    33,     5,     6,     7,    29,
      23,    24,    25,    26,    16,     3,     4,    31,    31,    35,
      36,    23,    24,    25,    26,    33,    27,    28,    16,    31,
      27,    28,    35,    36,    34,    23,    24,    25,    26,    31,
     110,   111,    31,    31,    17,    18,    19,    20,    21,    22,
      23,    36,    25,    17,    18,    19,    20,    21,    22,    23,
      29,    25,   113,   114,    32,    35,    29,    34,    34,    34,
      30,    32,    34,     9,    32,     7,    10,    36,    35,    32,
      36,    36,    36,    32,    31,    76,    17,    71,   107,    33,
     202,   109,   220,   128,    87,   101,    -1,    -1,    88,    -1,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    41,    42,    43,    44,
      50,    51,    52,    53,    54,     3,     5,    54,     0,    43,
      44,    51,     3,    63,    64,    31,     3,    55,    55,    13,
      29,    31,    56,    35,    36,    32,    45,    46,    54,    56,
      35,    36,    36,     3,     4,    16,    23,    24,    25,    26,
      31,    70,    71,    72,    76,    78,    80,    81,    82,    83,
       4,    31,    57,    58,    59,    60,    61,    62,    82,    32,
      45,    29,     3,    64,    33,    32,    35,     3,     3,    24,
      26,    29,    31,    84,     3,     3,    70,    14,    15,    17,
      18,    19,    20,    21,    22,    23,    25,    73,    77,    27,
      28,    79,     3,     4,    31,    83,    60,    14,    30,    15,
      23,    25,    73,    27,    28,     4,    31,    33,    32,    57,
       3,     8,    10,    11,    33,    36,    39,    49,    50,    54,
      65,    66,    81,    83,    33,    46,    29,    47,    56,    70,
      70,    74,    75,    24,    26,    29,    84,    84,    32,    71,
      72,    76,    78,    80,    31,    84,    70,    32,    58,    59,
      61,    61,    60,    62,    62,    60,    49,    33,    30,    31,
      31,    31,    49,    36,    70,    34,    65,     3,    66,    36,
      13,    31,    49,    48,    76,    29,    30,    32,    35,    70,
      74,    32,    32,    34,    49,     3,    31,    68,    69,    70,
      68,     3,    54,    67,    68,    34,    36,    70,    74,    34,
      30,    76,    70,    30,    32,    34,    13,    68,    70,    32,
      35,    32,    63,    36,    36,    32,    30,    70,    32,    66,
      69,    66,    36,    74,    36,     9,    74,    36,    66,    36,
      67,    67,    32,    32,    66,    66
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    41,    42,    42,    43,    43,    44,    44,
      44,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    49,    49,    49,    50,    50,    51,    51,    52,    52,
      53,    54,    54,    54,    55,    55,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    60,    60,    60,    61,
      61,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      64,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    73,    73,
      73,    73,    73,    73,    74,    74,    75,    75,    76,    76,
      77,    77,    78,    78,    79,    79,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    82,    82,    83,    83,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     3,     4,     1,     0,
       2,     1,     1,     0,     2,     1,     1,     1,     4,     4,
       3,     1,     1,     1,     1,     3,     4,     2,     3,     4,
       1,     3,     1,     3,     1,     3,     3,     3,     1,     3,
       3,     1,     1,     2,     3,     4,     1,     3,     1,     2,
       3,     2,     1,     3,     5,     9,    10,     4,     5,     7,
       5,     1,     2,     3,     2,     1,     0,     3,     1,     3,
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

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 168 "parser.y"
                               { (yyval.node)=Allocate(PROGRAM_NODE);  makeChild((yyval.node),(yyvsp[0].node)); prog=(yyval.node);}
#line 1645 "parser.tab.c"
    break;

  case 3:
#line 169 "parser.y"
          { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);}
#line 1651 "parser.tab.c"
    break;

  case 4:
#line 173 "parser.y"
                    {
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                    }
#line 1659 "parser.tab.c"
    break;

  case 5:
#line 177 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1667 "parser.tab.c"
    break;

  case 6:
#line 183 "parser.y"
                {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), (yyvsp[0].node));
                }
#line 1675 "parser.tab.c"
    break;

  case 7:
#line 187 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1683 "parser.tab.c"
    break;

  case 8:
#line 193 "parser.y"
                    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, (yyvsp[-7].node), makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
                    }
#line 1694 "parser.tab.c"
    break;

  case 9:
#line 200 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[-4].node));
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[-6].lexeme), NORMAL_ID), parameterList, (yyvsp[-1].node));
                    }
#line 1706 "parser.tab.c"
    break;

  case 10:
#line 208 "parser.y"
                    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, (yyvsp[-6].node), makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
                    }
#line 1716 "parser.tab.c"
    break;

  case 11:
#line 214 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[-5].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[-1].node));
                    }
#line 1727 "parser.tab.c"
    break;

  case 12:
#line 223 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1735 "parser.tab.c"
    break;

  case 13:
#line 227 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node)= (yyvsp[0].node);
                    
                }
#line 1745 "parser.tab.c"
    break;

  case 14:
#line 235 "parser.y"
                {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1754 "parser.tab.c"
    break;

  case 15:
#line 240 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1764 "parser.tab.c"
    break;

  case 16:
#line 247 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1772 "parser.tab.c"
    break;

  case 17:
#line 251 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1780 "parser.tab.c"
    break;

  case 18:
#line 257 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1789 "parser.tab.c"
    break;

  case 19:
#line 262 "parser.y"
                {
                    (yyval.node) = Allocate(NUL_NODE); 
                }
#line 1797 "parser.tab.c"
    break;

  case 20:
#line 268 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1807 "parser.tab.c"
    break;

  case 21:
#line 274 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1816 "parser.tab.c"
    break;

  case 22:
#line 279 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1825 "parser.tab.c"
    break;

  case 23:
#line 283 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                    }
#line 1834 "parser.tab.c"
    break;

  case 24:
#line 290 "parser.y"
                {
                        /*FINISH*/
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1843 "parser.tab.c"
    break;

  case 25:
#line 295 "parser.y"
                {
                        /*FINISH*/
                        (yyval.node)  = (yyvsp[0].node);
                }
#line 1852 "parser.tab.c"
    break;

  case 26:
#line 302 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1860 "parser.tab.c"
    break;

  case 27:
#line 306 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1868 "parser.tab.c"
    break;

  case 28:
#line 312 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1878 "parser.tab.c"
    break;

  case 29:
#line 318 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode("void", NORMAL_ID), (yyvsp[-1].node));
                }
#line 1888 "parser.tab.c"
    break;

  case 30:
#line 326 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1898 "parser.tab.c"
    break;

  case 31:
#line 334 "parser.y"
                {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);  
                }
#line 1906 "parser.tab.c"
    break;

  case 32:
#line 338 "parser.y"
                {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                }
#line 1914 "parser.tab.c"
    break;

  case 33:
#line 342 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1922 "parser.tab.c"
    break;

  case 34:
#line 348 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1930 "parser.tab.c"
    break;

  case 35:
#line 352 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[-2].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1939 "parser.tab.c"
    break;

  case 36:
#line 357 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[-3].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1948 "parser.tab.c"
    break;

  case 37:
#line 362 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 1957 "parser.tab.c"
    break;

  case 38:
#line 368 "parser.y"
                {
                    /*FINSH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1966 "parser.tab.c"
    break;

  case 39:
#line 376 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1974 "parser.tab.c"
    break;

  case 40:
#line 382 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1982 "parser.tab.c"
    break;

  case 41:
#line 386 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    (yyval.node) = makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1991 "parser.tab.c"
    break;

  case 42:
#line 393 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2000 "parser.tab.c"
    break;

  case 43:
#line 398 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeExprNode(BINARY_OPERATION, BINARY_OP_AND), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2009 "parser.tab.c"
    break;

  case 44:
#line 405 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2018 "parser.tab.c"
    break;

  case 45:
#line 410 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2027 "parser.tab.c"
    break;

  case 46:
#line 417 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2036 "parser.tab.c"
    break;

  case 47:
#line 422 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2046 "parser.tab.c"
    break;

  case 48:
#line 428 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2055 "parser.tab.c"
    break;

  case 49:
#line 434 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2065 "parser.tab.c"
    break;

  case 50:
#line 440 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2075 "parser.tab.c"
    break;

  case 51:
#line 446 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2084 "parser.tab.c"
    break;

  case 52:
#line 454 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 2094 "parser.tab.c"
    break;

  case 53:
#line 460 "parser.y"
                {
                    AST_NODE* const_node = Allocate(CONST_VALUE_NODE);
                    const_node->semantic_value.const1=(yyvsp[0].const1);
                    (yyval.node) = makeChild((yyvsp[-1].node), const_node);
                }
#line 2104 "parser.tab.c"
    break;

  case 54:
#line 466 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2113 "parser.tab.c"
    break;

  case 55:
#line 471 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2122 "parser.tab.c"
    break;

  case 56:
#line 478 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2131 "parser.tab.c"
    break;

  case 57:
#line 483 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2140 "parser.tab.c"
    break;

  case 58:
#line 490 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2148 "parser.tab.c"
    break;

  case 59:
#line 494 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 2157 "parser.tab.c"
    break;

  case 60:
#line 499 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-2].lexeme), WITH_INIT_ID), (yyvsp[0].node));
                }
#line 2166 "parser.tab.c"
    break;

  case 61:
#line 506 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 2175 "parser.tab.c"
    break;

  case 62:
#line 511 "parser.y"
                {
                    /*FINSH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2184 "parser.tab.c"
    break;

  case 63:
#line 520 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2193 "parser.tab.c"
    break;

  case 64:
#line 526 "parser.y"
                {
                    (yyval.node) = makeFamily(makeStmtNode(WHILE_STMT),2 , (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2201 "parser.tab.c"
    break;

  case 65:
#line 530 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(FOR_STMT), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2210 "parser.tab.c"
    break;

  case 66:
#line 535 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(FOR_STMT), 4, makeFamily(makeDeclNode(VARIABLE_DECL), 2, (yyvsp[-7].node), (yyvsp[-6].node)), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2219 "parser.tab.c"
    break;

  case 67:
#line 540 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(ASSIGN_STMT), 2, (yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2228 "parser.tab.c"
    break;

  case 68:
#line 546 "parser.y"
                {
                    (yyval.node) = makeFamily(makeStmtNode(IF_STMT), 3, (yyvsp[-2].node), (yyvsp[0].node),  Allocate(NUL_NODE));
                }
#line 2236 "parser.tab.c"
    break;

  case 69:
#line 551 "parser.y"
                {
                    (yyval.node) = makeFamily(makeStmtNode(IF_STMT), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2244 "parser.tab.c"
    break;

  case 70:
#line 556 "parser.y"
                {
                    (yyval.node) = makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, (yyvsp[-4].node), (yyvsp[-2].node));
                }
#line 2252 "parser.tab.c"
    break;

  case 71:
#line 560 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = Allocate(NUL_NODE);
                }
#line 2261 "parser.tab.c"
    break;

  case 72:
#line 565 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeStmtNode(RETURN_STMT), Allocate(NUL_NODE));
                }
#line 2270 "parser.tab.c"
    break;

  case 73:
#line 570 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeStmtNode(RETURN_STMT), (yyvsp[-1].node));
                }
#line 2279 "parser.tab.c"
    break;

  case 74:
#line 575 "parser.y"
                {
                    (yyval.node) = makeChild(makeStmtNode(DOUBLE_ADD_STMT), (yyvsp[-1].node));
                }
#line 2287 "parser.tab.c"
    break;

  case 75:
#line 581 "parser.y"
                     {
                        /*FINISH*/
                        (yyval.node) = makeChild(Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE), (yyvsp[0].node));
                     }
#line 2296 "parser.tab.c"
    break;

  case 76:
#line 586 "parser.y"
                     {
                         (yyval.node) = Allocate(NUL_NODE); 
                     }
#line 2304 "parser.tab.c"
    break;

  case 77:
#line 592 "parser.y"
                                {
                                    /*FINISH*/
                                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                }
#line 2313 "parser.tab.c"
    break;

  case 78:
#line 597 "parser.y"
                                {
                                    /*FINISH*/
                                    (yyval.node) = (yyvsp[0].node);
                                }
#line 2322 "parser.tab.c"
    break;

  case 79:
#line 610 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = makeFamily(makeStmtNode(ASSIGN_STMT), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[0].node));
                    }
#line 2331 "parser.tab.c"
    break;

  case 80:
#line 615 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2340 "parser.tab.c"
    break;

  case 81:
#line 620 "parser.y"
                    {
                        (yyval.node) = (yyvsp[-1].node);
                    }
#line 2348 "parser.tab.c"
    break;

  case 82:
#line 626 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2356 "parser.tab.c"
    break;

  case 83:
#line 630 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    (yyval.node) = makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2365 "parser.tab.c"
    break;

  case 84:
#line 637 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2374 "parser.tab.c"
    break;

  case 85:
#line 642 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeExprNode(BINARY_OPERATION, BINARY_OP_AND), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2383 "parser.tab.c"
    break;

  case 86:
#line 649 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2392 "parser.tab.c"
    break;

  case 87:
#line 654 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2401 "parser.tab.c"
    break;

  case 88:
#line 661 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
#line 2410 "parser.tab.c"
    break;

  case 89:
#line 666 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
#line 2419 "parser.tab.c"
    break;

  case 90:
#line 671 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
#line 2428 "parser.tab.c"
    break;

  case 91:
#line 676 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
#line 2437 "parser.tab.c"
    break;

  case 92:
#line 681 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
#line 2446 "parser.tab.c"
    break;

  case 93:
#line 686 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
#line 2455 "parser.tab.c"
    break;

  case 94:
#line 694 "parser.y"
                    {
                        /*FINISH*/
                        (yyval.node) = makeChild(Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE), (yyvsp[0].node));
                    }
#line 2464 "parser.tab.c"
    break;

  case 95:
#line 699 "parser.y"
                    {
                        (yyval.node) = Allocate(NUL_NODE);
                    }
#line 2472 "parser.tab.c"
    break;

  case 96:
#line 705 "parser.y"
                                {
                                    /*FINISH*/
                                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                }
#line 2481 "parser.tab.c"
    break;

  case 97:
#line 710 "parser.y"
                                {
                                    /*FINISH*/
                                    (yyval.node) = (yyvsp[0].node);
                                }
#line 2490 "parser.tab.c"
    break;

  case 98:
#line 717 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2499 "parser.tab.c"
    break;

  case 99:
#line 722 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2508 "parser.tab.c"
    break;

  case 100:
#line 729 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
#line 2516 "parser.tab.c"
    break;

  case 101:
#line 733 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
#line 2524 "parser.tab.c"
    break;

  case 102:
#line 739 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2533 "parser.tab.c"
    break;

  case 103:
#line 744 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2542 "parser.tab.c"
    break;

  case 104:
#line 751 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
#line 2551 "parser.tab.c"
    break;

  case 105:
#line 756 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
#line 2560 "parser.tab.c"
    break;

  case 106:
#line 763 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2569 "parser.tab.c"
    break;

  case 107:
#line 769 "parser.y"
                {   
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2578 "parser.tab.c"
    break;

  case 108:
#line 774 "parser.y"
                {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 2587 "parser.tab.c"
    break;

  case 109:
#line 780 "parser.y"
                {
                    AST_NODE* const_node = Allocate(CONST_VALUE_NODE);
                    const_node->semantic_value.const1=(yyvsp[0].const1);
                    (yyval.node) = makeChild((yyvsp[-1].node), const_node);
                }
#line 2597 "parser.tab.c"
    break;

  case 110:
#line 786 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                }
#line 2606 "parser.tab.c"
    break;

  case 111:
#line 792 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeChild((yyvsp[-4].node), makeFamily(makeStmtNode(FUNCTION_CALL_STMT), 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node)));
                }
#line 2615 "parser.tab.c"
    break;

  case 112:
#line 797 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2624 "parser.tab.c"
    break;

  case 113:
#line 803 "parser.y"
                {
                    (yyval.node) = makeChild((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 2632 "parser.tab.c"
    break;

  case 114:
#line 807 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2640 "parser.tab.c"
    break;

  case 115:
#line 813 "parser.y"
                    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_PP_ID), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 2648 "parser.tab.c"
    break;

  case 116:
#line 817 "parser.y"
                    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_PP), makeIDNode((yyvsp[-1].lexeme), NORMAL_ID));
                    }
#line 2656 "parser.tab.c"
    break;

  case 117:
#line 821 "parser.y"
                    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_MM_ID), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 2664 "parser.tab.c"
    break;

  case 118:
#line 825 "parser.y"
                    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_MM), makeIDNode((yyvsp[-1].lexeme), NORMAL_ID));
                    }
#line 2672 "parser.tab.c"
    break;

  case 119:
#line 829 "parser.y"
                    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_PP_ID), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)) );
                    }
#line 2680 "parser.tab.c"
    break;

  case 120:
#line 833 "parser.y"
                    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_PP), makeChild(makeIDNode((yyvsp[-2].lexeme), ARRAY_ID), (yyvsp[-1].node)) );
                    }
#line 2688 "parser.tab.c"
    break;

  case 121:
#line 837 "parser.y"
                    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_MM_ID), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)) );
                    }
#line 2696 "parser.tab.c"
    break;

  case 122:
#line 841 "parser.y"
                    {
                        (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_ID_MM), makeChild(makeIDNode((yyvsp[-2].lexeme), ARRAY_ID), (yyvsp[-1].node)) );
                    }
#line 2704 "parser.tab.c"
    break;

  case 123:
#line 847 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                }
#line 2712 "parser.tab.c"
    break;

  case 124:
#line 851 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_POSITIVE);
                }
#line 2720 "parser.tab.c"
    break;

  case 125:
#line 855 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                }
#line 2728 "parser.tab.c"
    break;

  case 126:
#line 862 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2737 "parser.tab.c"
    break;

  case 127:
#line 867 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID),(yyvsp[0].node));
                }
#line 2746 "parser.tab.c"
    break;

  case 128:
#line 875 "parser.y"
                {
                    /*FINISH*/
                   (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node)); 
                }
#line 2755 "parser.tab.c"
    break;

  case 129:
#line 880 "parser.y"
                {
                    /*FINISH*/
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2764 "parser.tab.c"
    break;


#line 2768 "parser.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 887 "parser.y"


#include "lex.yy.c"
int main (argc, argv)
int argc;
char *argv[];
  {
     yyin = fopen(argv[1],"r");
     yyparse();
     // printGV(prog, NULL);
     
     initializeSymbolTable();
     
     semanticAnalysis(prog);
     
     symbolTableEnd();
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
