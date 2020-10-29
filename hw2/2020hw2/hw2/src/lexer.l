%option noyywrap 
%{
#include <stdio.h>
#include "header.h" 
int linenumber;
symtab * lookup();
symtab * ptr;
void     insertID();
void 	 printSymTab();
/* You need to define for all tokens in C--, here are some examples */

#define OP_GE		30
#define OP_LE		31
#define OP_NEQ		32
#define OP_EQ 		33
#define OP_OR 		34
#define OP_AND 		35

#define OP_NOT		36
#define OP_ADD		37
#define OP_MINUS	38
#define OP_MULTI	39
#define OP_DEVIDE	40
#define OP_GT		41
#define OP_LT 		42
#define OP_ASSIGN 	43
 
#define RETURN 		10
#define TYPEDEF 	11
#define IF 			12
#define ELSE 		13
#define INT 		14
#define FLOAT 		15
#define FOR 		16
#define VOID 		17
#define WHILE 		18


#define MK_LPAREN 	50 
#define MK_RPAREN 	51
#define MK_LBRACE	52
#define MK_RBRACE	53

#define ERROR 		100 

%}

letter   [A-Za-z]
digit    [0-9]
ID	 {letter}({letter}|{digit}|"_")*
WS	 [ \t]+
Int_constant {digit}+
comment_upper \/\*
comment_lower \*\/
sign [+-]
exponent [eE]{sign}?{Int_constant}
dottedDigits (({Int_constant}[.]({Int_constant}?))|([.]{Int_constant}))

/* You need to define the following RE's */
Float_constant {Int_constant}{exponent})|({dottedDigits}({exponent}?)|{Int_constant}
String_constant \"([^\\n\r"]*)\"
comment {comment_upper}([^*]|[*]+[^/*])*[*]+[/]


/* Other operators appear here */ 

newline  "\n"

DL_lparen "("
DL_rparen ")"
DL_lbrace "{"
DL_rbrace "}"
DL_comma  ","
DL_semicol ";"
DL_dot  "."

error    .

%%

{WS}            {}
"return"		/* return RETURN; */
"typedef"		/* return TYPEDEF; */
"if"		/* return IF; */
"else"		/* return ELSE; */
"int"		/* return INT; */
"float"		/* return FLOAT; */
"for"		/* return FOR; */
"void"		/* return VOID; */
"while"		/* return WHILE; */

{ID}            { 
			ptr = lookup(yytext);
			if (ptr == NULL)
			     insertID(yytext);	
			else 
			     ptr->counter++;
		}

">="			/* return OP_GE; */
"<="			/* return OP_LE; */
"!="			/* return OP_NEQ; */
"=="			/* return OP_EQ; */
"||"			/* return OP_OR; */
"&&"			/* return OP_AND; */

"!"				/* return OP_NOT; */
"+"				/* return OP_ADD; */
"-"				/* return OP_MINUS; */
"*" 			/* return OP_MULTI; */
"/" 			/* return OP_DEVIDE; */
">" 			/* return OP_GT; */
"<" 			/* return OP_LT; */
"="     		/* return OP_ASSIGN; */

{DL_lparen}     /* return MK_LPAREN; */
{DL_rparen}     /* return MK_RPAREN; */
{DL_lbrace}     /* return MK_LBRACE; */
{DL_rbrace}     /* return MK_RBRACE; */
{DL_comma}      {}
{DL_semicol}    {}
{DL_dot} 		{}
{newline}       linenumber += 1;
{comment}       printf("%s\n", yytext);
{Int_constant} {}
{String_constant} {}
{Float_constant} {}
{error}         printf("ERR: %s \n", yytext);/* return ERROR; */


%%

int main(int argc, char **argv)
{
 argc--; ++argv;
   if (argc > 0)
      yyin = fopen(argv[0], "r");
   else
      yyin = stdin;
   yylex();
   printSymTab();
}

