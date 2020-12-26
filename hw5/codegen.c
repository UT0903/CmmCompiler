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
	STRING,
	GLOBAL,
	LOCAL
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
	AST_NODE * declNode = rootNode->child;
	while(declNode != NULL){
		if(declNode.nodeType == VARIABLE_DECL_LIST_NODE){
			AST_NODE *varDeclNode = declNode->child;
			while(varDeclNode != NULL){
				processDecl(varDeclNode, GLOBAL);
				varDeclNode = varDeclNode->rightSibling;
			}
		}
		else if(declNode.nodeType != DECLARATION_NODE){
			fprintf(stderr, "Error in codeGen\n");
			exit(0);
		}
		processDecl(declNode, GLOBAL);
		declNode= declNode->rightSibling;
	}
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
/*char *getReg(TYPE type){
	if(TYPE == INT){
		for(int i = 0; i < ){

		}
	}
	else if(TYPE == FLOAT){

	}
	else{
		fprintf(stderr, "Error in getReg: Unknown type\n");
		exit(0);
	}
}*/
void Read(){
	fprintf(fp, "call _read_int\n");
}
void processDecl(AST_NODE *declNode, TYPE type){
	switch(declNode->semantic_value.declSemanticValue.kind){
		case(VARIABLE_DECL):
		case(FUNCTION_PARAMETER_DECL):
			processVarDecl(declNode->child, type);
			break;
		case(TYPE_DECL):
			break;
		case(FUNCTION_DECL):
			processFuncDecl(declNode->child);
			break;
		default:
			fprintf(stderr, "Error in processDecl\n");
			exit(0);
	}
}
void processFuncDecl(AST_NODE* typeNode){

}
void processVarDecl(AST_NODE* typeNode, TYPE type){
	AST_NODE* varNode = typeNode->rightSibling;
	while(varNode != NULL){
		SymbolTableEntry *entry = varNode->semantic_value.identifierSemanticValue.symbolTableEntry;
		assert(entry != NULL);
		entry->offset //offset
		entry->global
		entry->attribute->attr.typeDescriptor->properties.dataType //scalar
		entry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType //array
		int arr_total_size = 1;
		switch(varNode->semantic_value.identifierSemanticValue.kind){
			case(NORMAL_ID):
				switch(type){
					case(GLOBAL):
						fprintf(fp, ".data\n");
						fprintf(fp, "\t_g_%s: .word\n", entry->name);
						entry->global = 1;
						break;
					case(LOCAL):
						entry->offset = AR_offset;
						AR_offset += 8;
						entry->global = 0;
						break;
					default:
						fprintf(stderr, "Error in processVarDecl\n");
						exit(0);
				}
				break;
			case(ARRAY_ID):
				for(int i = 0; i < entry->attribute->attr.typeDescriptor->properties.arrayProperties.dimension; i++){
					arr_total_size *= entry->attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[i];
				}
				switch(type){
					case(GLOBAL):
						fprintf(fp, ".data\n");
						fprintf(fp, "\t_g_%s: .space %d\n", entry->name, arr_total_size*8);
						entry->global = 1;
						break;
					case(LOCAL):
						entry->offset = AR_offset;
						AR_offset += arr_total_size;
						entry->global = 0;
						break;
					default:
						fprintf(stderr, "Error in processVarDecl\n");
						exit(0);
				}
				break;
			case(WITH_INIT_ID):
				switch(type){
					case(GLOBAL):
						fprintf(fp, ".data\n");
						switch(varNode->child->semantic_value.const1->const_type){
							case(INTEGERC):
								fprintf(fp, "\t_g_%s: .word %d\n", entry->name, varNode->child->semantic_value.const1->const_u.intval);
								break;
							case(FLOATC):
								fprintf(fp, "\t_g_%s: .word %lf\n", entry->name, varNode->child->semantic_value.const1->const_u.fval);
								break;
							default:
								fprintf(stderr, "Error in processVarDecl\n");
								exit(0);
						}
						entry->global = 1;
						break;
					case(LOCAL):
						if(varNode->child->semantic_value.const1->const_type == INTEGERC){
							int reg = getReg();
							fprintf(fp, "li %s, %d\n", reg, varNode->child->semantic_value.const1->const_u.intval);
							fprintf(fp, "sd %s, %d(sp)\n", reg, AR_offset);
						}
						else if(varNode->child->semantic_value.const1->const_type == FLOATC){
							int val = FloatToInt(varNode->child->semantic_value.const1->const_u.fval);
							int reg = getReg();
							fprintf(fp, "li %s, %d\n", reg, val);
							fprintf(fp, "sd %s, %d(sp)\n", reg, AR_offset);
						}
						else{
							fprintf(stderr, "Error in processVarDecl\n");
							exit(0);
						}
						entry->offset = AR_offset;
						AR_offset += 8;
						entry->global = 0;
						break;
					default:
						fprintf(stderr, "Error in processVarDecl\n");
						exit(0);
				}
				break;
			default:
				fprintf(stderr, "Error in processVarDecl\n");
				exit(0);
		}
		
		varNode = varNode->rightSibling;
	}
}
void load(int rd, TYPE GL, TYPE IFS){
	assert(GL == GLOBAL || GL == LOCAL);
	assert(IFS == INT || IFS == FLOAT || IFS == STRING)
	if(GL == GLOBAL)
}
void store(int rs, TYPE GL, TYPE IFS){
	if(GL)
}