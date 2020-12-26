#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>
#include "header.h"
#include "symbolTable.h"
#define ERR_EXIT(a) { fprintf(stderr, "%s\n", a); exit(0); }
typedef enum{
	INT,
	FLOAT,
	STRING,
	GLOBAL,
	LOCAL
}TYPE;

FILE *fp;
char int_reg[19][10];
char float_reg[24][10];
int AR_offset;
typedef struct{
	int ptr;
	char value[1000][100];
	TYPE type[1000];
}Constant;
Constant constant;
void codeGen(AST_NODE *rootNode);
void gen_prologue (char *name);
void gen_epilogue(char *name);
void gen_head (char *name);
void globalDecl(TYPE type, char* name, int sizeOrValue, char* str);
void Init_reg();
int FloatToInt (float f);
int getArraySize(ArrayProperties ap);
void processStmt(AST_NODE *stmtNode);
void processDecl(AST_NODE *declNode, TYPE type);
void processVarDecl(AST_NODE* typeNode, TYPE type);
void processFuncDecl(AST_NODE* typeNode);
void ReleaseConst();
int processConstValueNode(AST_NODE *constNode);
void processBlock(AST_NODE* Node, AST_NODE* typeNode);


char *getReg(){
	return "t0"; 
}
int processConstValueNode(AST_NODE *constNode){
	CON_Type *const1 = constNode->semantic_value.const1;
	if(const1->const_type == INTEGERC){
		sprintf(constant.value[constant.ptr], "%d", const1->const_u.intval);
		constant.type[constant.ptr] = INT;
	}
	else if(const1->const_type == FLOATC){
		sprintf(constant.value[constant.ptr], "%d", FloatToInt(const1->const_u.fval));
		constant.type[constant.ptr] = INT;
	}
	else if(const1->const_type == STRINGC){
		sprintf(constant.value[constant.ptr], "%s", const1->const_u.sc);
		constant.type[constant.ptr] = STRING;
	}
	else ERR_EXIT("processConstValueNode");
	
	return constant.ptr++;
}
void ReleaseConst(){
	fprintf(fp, "\t.data\n");
	for(int i = 0; i < constant.ptr; i++){
		if(constant.type[i] == INT){
			fprintf(fp, "_CONSTANT_%d: .word \"%s\"", i, constant.value[i]);
		}
		else{
			fprintf(fp, "_CONSTANT_%d: .ascii \"%s\"", i, constant.value[i]);
		}
	}
}
void codeGen(AST_NODE *rootNode){
	fprintf(stderr, "Start Code generation\n");
	fp = fopen("output.s", "w+");
	//Init_reg();
	AST_NODE * declNode = rootNode->child;
	while(declNode != NULL){
		if(declNode->nodeType == VARIABLE_DECL_LIST_NODE){
			AST_NODE *varDeclNode = declNode->child;
			while(varDeclNode != NULL){
				processDecl(varDeclNode, GLOBAL);
				varDeclNode = varDeclNode->rightSibling;
			}
		}
		else if(declNode->nodeType != DECLARATION_NODE){
			fprintf(stderr, "Error in codeGen\n");
			exit(0);
		}
		processDecl(declNode, GLOBAL);
		declNode= declNode->rightSibling;
	}
	ReleaseConst();
	fclose(fp);
}
void gen_prologue (char *name){
	fprintf(fp, "\t.text\n");
	fprintf(fp, "_start_%s:\n", name);
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
	for(int i = 0; i < 8; i++){
		fprintf(fp, "\tfsw ft%d, %d(sp)\n", i, i*4 + 160);
	}
	AR_offset = 0;
} 
void gen_epilogue(char *name){
	fprintf(fp, "_end_%s:\n", name);
	for(int i = 0; i < 7; i++){
		fprintf(fp, "\tld t%d, %d(sp)\n", i, i*8 + 8);
	}
	for(int i = 0; i < 12; i++){
		fprintf(fp, "\tld s%d, %d(sp)\n", i, i*8 + 64);
	}
	for(int i = 0; i < 8; i++){
		fprintf(fp, "\tflw ft%d, %d(sp)\n", i, i*4 + 160);
	}
	fprintf(fp, "\tld ra, 8(fp)\n"); // restore return address
	fprintf(fp, "\taddi sp, fp, 8\n"); // pop AR
	fprintf(fp, "\tld fp, 0(fp)\n"); // restore caller (old) fp
	fprintf(fp, "\tjr ra\n");
	fprintf(fp, "\t.data\n");
	fprintf(fp, "\t_frameSize_%s:\t.word\t%d\n", name, 180 - AR_offset);
}

/*void Init_reg(){
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
}*/

void Read(char* to, TYPE type){
	if(type == INT){
		fprintf(fp, "\tcall _read_int\n");
		fprintf(fp, "\tmv %s a0\n", to);
	}
	else if(type == FLOAT){
		fprintf(fp, "\tcall _read_float\n");
		fprintf(fp, "\tfmv.s %s fa0\n", to);
	}
	else ERR_EXIT("Read");
	
}
void processDecl(AST_NODE *declNode, TYPE type){
	assert(type == GLOBAL || type == LOCAL);
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
void processStmt(AST_NODE* stmtNode){
	//TODO
}
void processBlock(AST_NODE* Node, AST_NODE* typeNode){
	while(Node != NULL){
		if(Node->nodeType == VARIABLE_DECL_LIST_NODE){
			AST_NODE *declNode = Node->child;
			while(declNode != NULL){
				processDecl(declNode, LOCAL);
				declNode = declNode->rightSibling;
			}
		}
		else if(Node->nodeType == STMT_LIST_NODE){
			AST_NODE *stmtNode = Node->child;
			while(stmtNode != NULL){
				processStmt(stmtNode);
				stmtNode = stmtNode->rightSibling;
			}
		}
		Node = Node->rightSibling;
	}
}
void processFuncDecl(AST_NODE* typeNode){
	AST_NODE *nameNode = typeNode->rightSibling;
	gen_prologue(nameNode->semantic_value.identifierSemanticValue.identifierName);
	AST_NODE *paramListNode = nameNode->rightSibling;
	AST_NODE *paramDeclNode = paramListNode->child;
	while(paramDeclNode != NULL){
		processDecl(paramDeclNode, LOCAL);
		paramDeclNode = paramDeclNode->rightSibling;
	}
	AST_NODE *blockNode = paramListNode->rightSibling;
	processBlock(blockNode->child, typeNode);
	gen_epilogue(nameNode->semantic_value.identifierSemanticValue.identifierName);
}
void processVarDecl(AST_NODE* typeNode, TYPE type){
	AST_NODE* varNode = typeNode->rightSibling;
	while(varNode != NULL){
		SymbolTableEntry *entry = varNode->semantic_value.identifierSemanticValue.symbolTableEntry;
		assert(entry != NULL);
		if(varNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID){
			if(type == GLOBAL){
				fprintf(fp, "\t.data\n");
				fprintf(fp, "_g_%s: .word\n", entry->name);
				entry->global = 1;
			}
			else if(type == LOCAL){
				AR_offset -= 4;
				entry->offset = AR_offset;
				entry->global = 0;
			}
			else ERR_EXIT("processVarDecl1");
		}
		else if(varNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID){
			int arr_size = getArraySize(entry->attribute->attr.typeDescriptor->properties.arrayProperties);
			if(type == GLOBAL){
				fprintf(fp, "\t.data\n");
				fprintf(fp, "_g_%s: .space %d\n", entry->name, arr_size*4);
				entry->global = 1;
			}
			else if(type == LOCAL){
				AR_offset -= arr_size*4;
				entry->offset = AR_offset;
				entry->global = 0;
			}
			else ERR_EXIT("processVarDecl2");
		}
		else if(varNode->semantic_value.identifierSemanticValue.kind == WITH_INIT_ID){
			if(type == GLOBAL){
				fprintf(fp, "\t.data\n");
				if(varNode->child->semantic_value.const1->const_type == INTEGERC){
					fprintf(fp, "_g_%s: .word %d\n", entry->name, varNode->child->semantic_value.const1->const_u.intval);
				}
				else if(varNode->child->semantic_value.const1->const_type == FLOATC){
					fprintf(fp, "_g_%s: .word %d\n", entry->name, FloatToInt(varNode->child->semantic_value.const1->const_u.fval));
				}
				else ERR_EXIT("processVarDecl3");
				entry->global = 1;
			}
			else if(type == LOCAL){
				fprintf(fp, "\t.text\n");
				AR_offset -= 4;
				if(varNode->child->semantic_value.const1->const_type == INTEGERC){
					char* reg = getReg(); //TODO
					fprintf(fp, "\tli %s, %d\n", reg, varNode->child->semantic_value.const1->const_u.intval);
					fprintf(fp, "\tsw %s, %d(sp)\n", reg, AR_offset);
				}
				else if(varNode->child->semantic_value.const1->const_type == FLOATC){
					char* reg = getReg(); //TODO
					fprintf(fp, "\tli %s, %d\n", reg, FloatToInt(varNode->child->semantic_value.const1->const_u.fval));
					fprintf(fp, "\tsw %s, %d(sp)\n", reg, AR_offset);
				}
				else ERR_EXIT("processVarDecl4");
				entry->offset = AR_offset;
				entry->global = 0;
			}
			else ERR_EXIT("processVarDecl5");
		}
		else ERR_EXIT("processVarDecl6");
		varNode = varNode->rightSibling;
	}
}
void load(char* rd, SymbolTableEntry *entry, int shift){
	if(entry->global == 1){
		fprintf(fp, "la %s, _g_%s\n", rd, entry->name);
		if(entry->attribute->attributeKind)
		fprintf(fp, "lw %s, _g_%s\n", rd, entry->name);
	}
	else{

	}
}
int FloatToInt (float f){
    union {
        float f;
        uint32_t u;
    } fu = { .f = f };
    int i = sizeof f * CHAR_BIT;
    unsigned int ret = 0;
    while (i--){
        ret = ret << 1;
        ret += ((fu.u >> i) & 0x1);
    }
    return (int)ret;
}
int getArraySize(ArrayProperties ap){
	int ret = 1;
	for(int i = 0; i < ap.dimension; i++){
		ret *= ap.sizeInEachDimension[i];
	}
	return ret;
}