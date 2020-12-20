#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
FILE *fp;
void codeGen(AST_NODE *rootNode){
	fprintf(stderr, "Start Code generation\n");
	fp = fopen("output.S", "w+");
}
void gen_prologue (char *name){
	fprintf(fp, "\tsd ra, 8(sp)\n", name); // store return address
	fprintf(fp, "\tsd fp, 0(sp)\n"); // save old fp
	fprintf(fp, "\taddi fp, sp, -8\n"); // new fp
	fprintf(fp, "\taddi sp, sp, -16\n"); // new sp
	fprintf(fp, "\tla ra, _frameSize_name\n");
	fprintf(fp, "\tlw ra, 0(ra)\n");
	fprintf(fp, "\tsub sp, sp, ra\n"); // push new AR
	fprintf(fp, "_begin_main:\n");
} 
void gen_epilogue(char *name){
	fprintf(fp, "_end_%s:\n", name);
	fprintf(fp, "\tld ra, 8(fp)\n"); // restore return address
	fprintf(fp, "\taddi sp, fp, 8\n"); // pop AR
	fprintf(fp, "\tld fp, 0(fp)\n"); // restore caller (old) fp
	fprintf(fp, "\tjr ra\n");
	fprintf(fp, ".data\n");
	fprintf(fp, "_framesize_%s:\t.word\tsize\n", name);
}

void gen_head (char *name):{
	fprintf(fp, ".text %s:\n", name);
}