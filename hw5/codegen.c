#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"

typedef enum{
	INT,
	FLOAT,
	ARRAY,
	INIT_INT,
	INIT_FLOAT,
	STRING
}TYPE;

FILE *fp;
char int_reg[19][10];
char float_reg[24][10];

void codeGen(AST_NODE *rootNode);
void gen_prologue (char *name);
void gen_epilogue(char *name, int size);
void gen_head (char *name);
void globalDecl(TYPE type, char* name, int sizeOrValue, char* str);
void Init_reg();

void codeGen(AST_NODE *rootNode){
	fprintf(stderr, "Start Code generation\n");
	fp = fopen("output.s", "w+");
	Init_reg();
	gen_prologue("MAIN");
	gen_epilogue("MAIN", int size);
	fclose(fp);
}
void gen_prologue (char *name){
	fprintf(fp, ".text\n");
	fprintf(fp, "\t_start_%s:\n", name);
	fprintf(fp, "\tsd ra, 0(sp)\n"); // store return address
	fprintf(fp, "\tsd fp, -8(sp)\n"); // save old fp
	fprintf(fp, "\taddi fp, sp, -8\n"); // new fp
	fprintf(fp, "\taddi sp, sp, -16\n"); // new sp
	fprintf(fp, "\tla ra, _frameSize_%s\n", name);
	fprintf(fp, "\tlw ra, 0(ra)\n");
	fprintf(fp, "\tsub sp, sp, ra\n"); // push new AR
	for(int i = 0; i < 7; i++){
		fprintf(fp, "\tsd t%d, %d(sp)\n", i, i*8 + 8);
	}
	for(int i = 0; i < 12; i++){
		fprintf(fp, "\tsd s%d, %d(sp)\n", i, i*8 + 64);
	}
	for(int i = 0; i < 18; i++){
		fprintf(fp, "\tfsw ft%d, %d(sp)\n", i, i*4 + 160);
	}
} 
void gen_epilogue(char *name, int size){
	fprintf(fp, "_end_%s:\n", name);
	for(int i = 0; i < 7; i++){
		fprintf(fp, "\tld t%d, %d(sp)\n", i, i*8 + 8);
	}
	for(int i = 0; i < 12; i++){
		fprintf(fp, "\tld s%d, %d(sp)\n", i, i*8 + 64);
	}
	for(int i = 0; i < 18; i++){
		fprintf(fp, "\tflw ft%d, %d(sp)\n", i, i*4 + 160);
	}
	fprintf(fp, "\tld ra, 8(fp)\n"); // restore return address
	fprintf(fp, "\taddi sp, fp, 8\n"); // pop AR
	fprintf(fp, "\tld fp, 0(fp)\n"); // restore caller (old) fp
	fprintf(fp, "\tjr ra\n");
	fprintf(fp, ".data\n");
	fprintf(fp, "\t_framesize_%s:\t.word\t%d\n", name, size);
}

void globalDecl(TYPE type, char* name, int sizeOrValue, char* str){
	fprintf(fp, ".data\n");
	if(type == INT){
		fprintf(fp, "\t%s: .word\n", name);
	}
	else if(type == FLOAT){
		fprintf(fp, "\t%s: .float\n", name);
	}
	else if(type == ARRAY){
		fprintf(fp, "\t%s: .space %d\n", name, sizeOrValue); //size = sizeof(type) * arr_dim1 * arr_dim2...
	}
	else if(type == INIT_INT){
		fprintf(fp, "\t%s: .word %d\n", name, sizeOrValue); //value
	}
	else if(type == INIT_FLOAT){
		fprintf(fp, "\t%s: .float %d\n", name, sizeOrValue); //value
	}
	else if(type == STRING){
		fprintf(fp, "\t%s: .ascii \"%s\"\n", name, str);
	}
	else{
		fprintf(stderr, "error in globalDecl\n");
		exit(0);
	}
}

void Init_reg(){
	for(int i = 0; i < 7; i++){
		sprintf(int_reg[i], "t%d", i);
		int_dirty[i] = 0;
	}
	for(int i = 0; i < 12; i++){
		sprintf(int_reg[i+7], "s%d", i);
		int_dirty[i+7] = 1;
	}
	for(int i = 0; i < 12; i++){
		sprintf(float_reg[i], "ft%d", i);
		float_dirty[i] = 0;
	}
	for(int i = 0; i < 12; i++){
		sprintf(float_reg[i+12], "fs%d", i);
		float_dirty[i+12] = 1;
	}
}
char *getReg(TYPE type){
	if(TYPE == INT){
		//for(int i = 0; i < )
	}
	else if(TYPE == FLOAT){

	}
	else{
		fprintf(stderr, "Error in getReg: Unknown type\n");
		exit(0);
	}
}
void Read(){
	fprintf(fp, "call _read_int\n");
}