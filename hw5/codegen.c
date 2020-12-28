#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>
#include "header.h"
#include "symbolTable.h"
#define ERR_EXIT(a) { fprintf(stderr, "%s\n", a); exit(0); }
#define INT_REG_NUM 19
#define FLOAT_REG_NUM 8
typedef enum{
	GLOBAL,
	LOCAL
}TYPE;

FILE *fp;
char int_reg[INT_REG_NUM][10] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11"};
char float_reg[FLOAT_REG_NUM][10] = {"ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7"};
int int_ptr, float_ptr;
int AR_offset;
typedef struct{
	int ptr;
	char value[1000][200];
}Constant;
Constant constant;
void codeGen(AST_NODE *rootNode);
void gen_prologue (char *name);
void gen_epilogue(char *name);
void gen_head (char *name);
void globalDecl(TYPE type, char* name, int sizeOrValue, char* str);
int FloatToInt (float f);
int getArraySize(ArrayProperties ap);
void genStmt(AST_NODE *stmtNode);
void genDecl(AST_NODE *declNode, TYPE type);
void genVarDecl(AST_NODE* typeNode, TYPE type);
void genFuncDecl(AST_NODE* typeNode);
void ReleaseConst();

void genWhileStmt(AST_NODE* whileNode);
void genForStmt(AST_NODE* forNode);
void genAssignmentStmt(AST_NODE* assignmentNode);
void genIfStmt(AST_NODE* ifNode);
void genWriteFunction(AST_NODE* functionCallNode);
void genFunctionCall(AST_NODE* functionCallNode);
char* getOffsetPlace(AST_NODE* Node);
char* getRegName(AST_NODE* Node);
void genNode(AST_NODE* Node);
void genExprNode(AST_NODE* Node);
void genConstNode(AST_NODE* Node);
void genIDNode(AST_NODE* Node);
void genReturnNode(AST_NODE *Node);
void genBlockNode(AST_NODE* blockNode);
void genBinaryOp(BINARY_OPERATOR op, char *l_reg, char *r_reg, char * reg);
void genUnaryOp(UNARY_OPERATOR op, char *c_reg);
void genfBinaryOp(BINARY_OPERATOR op, char *l_reg, char *r_reg, char * reg);
void genfUnaryOp(UNARY_OPERATOR op, char *c_reg);



int getReg(DATA_TYPE type){
	int ret;
	if(type == INT_TYPE || type == CONST_STRING_TYPE){
		ret = int_ptr;
		int_ptr = (int_ptr + 1) % INT_REG_NUM;
	}
	else{
		ret = float_ptr;
		float_ptr = (float_ptr + 1) % FLOAT_REG_NUM;
	}
	return ret;
}
void freeReg(int reg, DATA_TYPE type){}

void ReleaseConst(){
	for(int i = 0; i < constant.ptr; i++){
		fprintf(fp, "%s", constant.value[i]);
	}
	constant.ptr = 0;
}
void codeGen(AST_NODE *rootNode){
	fprintf(stderr, "Start Code generation\n");
	fp = fopen("output.s", "w+");
	AST_NODE * declNode = rootNode->child;
	while(declNode != NULL){
		if(declNode->nodeType == VARIABLE_DECL_LIST_NODE){
			AST_NODE *varDeclNode = declNode->child;
			fprintf(fp, "\t.data\n");
			while(varDeclNode != NULL){
				genDecl(varDeclNode, GLOBAL);
				varDeclNode = varDeclNode->rightSibling;
			}
		}
		else if(declNode->nodeType != DECLARATION_NODE){
			fprintf(stderr, "Error in codeGen\n");
			exit(0);
		}
		genDecl(declNode, GLOBAL);
		declNode= declNode->rightSibling;
	}
	fclose(fp);
	fprintf(stderr, "End Code generation\n");
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
	for(int i = 0; i < INT_REG_NUM; i++){
		fprintf(fp, "\tsd %s, %d(sp)\n", int_reg[i], i*8 + 8);
	}
	for(int i = 0; i < FLOAT_REG_NUM; i++){
		fprintf(fp, "\tfsw %s, %d(sp)\n", float_reg[i], i*4 + 8 + INT_REG_NUM*8);
	}
	AR_offset = 0;
} 
void gen_epilogue(char *name){
	fprintf(fp, "_end_%s:\n", name);
	for(int i = 0; i < INT_REG_NUM; i++){
		fprintf(fp, "\tld %s, %d(sp)\n", int_reg[i], i*8 + 8);
	}
	for(int i = 0; i < FLOAT_REG_NUM; i++){
		fprintf(fp, "\tflw %s, %d(sp)\n", float_reg[i], i*4 + 8 + INT_REG_NUM*8);
	}
	fprintf(fp, "\tld ra, 8(fp)\n"); // restore return address
	fprintf(fp, "\taddi sp, fp, 8\n"); // pop AR
	fprintf(fp, "\tld fp, 0(fp)\n"); // restore caller (old) fp
	fprintf(fp, "\tjr ra\n");
	fprintf(fp, "\t.data\n");
	fprintf(fp, "\t_frameSize_%s:\t.word\t%d\n", name, INT_REG_NUM*8 + FLOAT_REG_NUM*4 + 8 - AR_offset);
	ReleaseConst();
}

void Read(char* to, DATA_TYPE type){
	if(type == INT_TYPE){
		fprintf(fp, "\tcall _read_int\n");
		fprintf(fp, "\tmv %s a0\n", to);
	}
	else if(type == FLOAT_TYPE){
		fprintf(fp, "\tcall _read_float\n");
		fprintf(fp, "\tfmv.s %s fa0\n", to);
	}
	else ERR_EXIT("Read");
}
void genDecl(AST_NODE *declNode, TYPE type){
	switch(declNode->semantic_value.declSemanticValue.kind){
		case(VARIABLE_DECL):
		case(FUNCTION_PARAMETER_DECL):
			genVarDecl(declNode->child, type);
			break;
		case(TYPE_DECL):
			break;
		case(FUNCTION_DECL):
			genFuncDecl(declNode->child);
			break;
		default:
			fprintf(stderr, "Error in genDecl\n");
			exit(0);
	}
}
void genStmt(AST_NODE* stmtNode){
	//TODO
	if(stmtNode->nodeType == BLOCK_NODE){
        genBlockNode(stmtNode);
    }
    else if(stmtNode->nodeType == CONST_VALUE_NODE || stmtNode->nodeType == IDENTIFIER_NODE){
        genNode(stmtNode);
    }
    else if(stmtNode->nodeType == NUL_NODE){
        return;
    }
    else if(stmtNode->nodeType == STMT_NODE){
        switch (stmtNode->semantic_value.stmtSemanticValue.kind)
        {
        case WHILE_STMT:
            genWhileStmt(stmtNode);
            break;
        case IF_STMT:
            genIfStmt(stmtNode);
            break;
        case FOR_STMT:
            genForStmt(stmtNode);
            break;
        case ASSIGN_STMT:
            genAssignmentStmt(stmtNode);
            break;
        case FUNCTION_CALL_STMT:
            genFunctionCall(stmtNode);
            break;
        case RETURN_STMT:
            genReturnNode(stmtNode);
            break;
        default:
            perror("no match stmt");
            exit(0);
            break;
        }
    }
    else{
        perror("input no stmt");
        exit(0);
    }
}

void genAssignmentStmt(AST_NODE* assignmentNode){
	AST_NODE *l = assignmentNode->child;
    AST_NODE *r = l->rightSibling;
	genNode(r);
	char *id_reg = getOffsetPlace(l);
	char *reg = getRegName(r);
	if(l->dataType == INT_TYPE)
		fprintf(fp, "\tsw %s 0(%s)\n", reg, id_reg);
	else
		fprintf(fp, "\tfsw %s 0(%s)\n", reg, id_reg);
	return;
}

void genNode(AST_NODE* Node){
	switch (Node->nodeType)
	{
	case STMT_NODE:
		genStmt(Node);
		break;
	case EXPR_NODE:
		genExprNode(Node);
		break;
	case CONST_VALUE_NODE:
		genConstNode(Node);
		break;
	case IDENTIFIER_NODE:
		genIDNode(Node);
		break;
	default:
		break;
	}
	return;
}

char* getOffsetPlace(AST_NODE* Node){
	Node->place = getReg(Node->dataType);
	char *reg = getRegName(Node);
	if(Node->semantic_value.identifierSemanticValue.symbolTableEntry->global){
		if(Node->semantic_value.identifierSemanticValue.kind == NORMAL_ID){
			fprintf(fp, "\tla %s _g_%s\n", reg, Node->semantic_value.identifierSemanticValue.identifierName);
		}
		else{
			AST_NODE *dim = Node->child;
			genNode(dim);
			char *dim_reg = getRegName(dim);
			fprintf(fp, "\tla %s _g_%s\n", reg, Node->semantic_value.identifierSemanticValue.identifierName);
			fprintf(fp, "\tslli %s %s 2\n", dim_reg, dim_reg);
			fprintf(fp, "\tadd %s %s %s\n", reg, reg, dim_reg);
		}
	}
	else{
		if(Node->semantic_value.identifierSemanticValue.kind == NORMAL_ID){
			fprintf(fp, "\taddi %s fp %d\n", reg, Node->semantic_value.identifierSemanticValue.symbolTableEntry->offset);
		}
		else{
			AST_NODE *dim = Node->child;
			genNode(dim);
			char *dim_reg = getRegName(dim);
			fprintf(fp, "\taddi %s %d fp\n", reg, Node->semantic_value.identifierSemanticValue.symbolTableEntry->offset);
			fprintf(fp, "\tslli %s %s 2\n", dim_reg, dim_reg);
			fprintf(fp, "\tadd %s %s %s\n", reg, reg, dim_reg);
		}
	}
	return reg;
}

char* getRegName(AST_NODE* Node){
	if(Node->dataType == INT_TYPE || Node->dataType == CONST_STRING_TYPE){
		return int_reg[Node->place];
	}
	else{
		return float_reg[Node->place];
	}
}

void genExprNode(AST_NODE* Node){
	EXPRSemanticValue *expr = &Node->semantic_value.exprSemanticValue; 
	if(Node->semantic_value.exprSemanticValue.kind == BINARY_OPERATION){
		BINARY_OPERATOR op = expr->op.binaryOp;
		AST_NODE *l = Node->child, *r = Node->child->rightSibling;
		genNode(l);
		genNode(r);
		Node->place = getReg(Node->dataType);
		char *l_reg = getRegName(l), *r_reg = getRegName(r), *reg = getRegName(Node);
		if(l->dataType == FLOAT_TYPE || r->dataType == FLOAT_TYPE)
			genfBinaryOp(op, l_reg, r_reg, reg);
		else
			genBinaryOp(op, l_reg, r_reg, reg);
	}
	else{
		AST_NODE *child = Node->child;
		genNode(child);
		UNARY_OPERATOR op =expr->op.unaryOp;
		Node->place = child->place;
		char *c_reg = getRegName(child);
		if(child->dataType == FLOAT_TYPE)
			genfUnaryOp(op, c_reg);
		else
			genUnaryOp(op, c_reg);
	}
	return;
}

void genBinaryOp(BINARY_OPERATOR op, char *l_reg, char *r_reg, char * reg){
	switch (op)
    {
    case BINARY_OP_ADD:
		fprintf(fp, "\tadd %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_SUB:
		fprintf(fp, "\tsub %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_MUL:
		fprintf(fp, "\tmul %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_DIV:
		fprintf(fp, "\tdiv %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_EQ:
		fprintf(fp, "\tsub %s %s %s\n", l_reg, l_reg, r_reg);
		fprintf(fp, "\tseqz %s %s\n", reg, l_reg );
        break;
    case BINARY_OP_GE:
		fprintf(fp, "\tslt %s %s %s\n", l_reg, l_reg, r_reg);
		fprintf(fp, "\tsnez %s %s\n", reg, reg );
        break;
    case BINARY_OP_LE:
		fprintf(fp, "\tslt %s %s %s\n", l_reg, r_reg, l_reg);
		fprintf(fp, "\tsnez %s %s\n", reg, reg );
        break;
    case BINARY_OP_NE:
		fprintf(fp, "\tsub %s %s %s\n", l_reg, l_reg, r_reg);
		fprintf(fp, "\tsnez %s %s\n", reg, reg );
        break;
    case BINARY_OP_GT:
		fprintf(fp, "\tslt %s %s %s\n", reg, r_reg, l_reg);
        break;
    case BINARY_OP_LT:
		fprintf(fp, "\tslt %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_AND:
		fprintf(fp, "\tand %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_OR:
		fprintf(fp, "\tor %s %s %s\n", reg, l_reg, r_reg);
        break;
    default:
        break;
    }
	return;
}

void genUnaryOp(UNARY_OPERATOR op, char *c_reg){
	switch (op)
    {
    case UNARY_OP_POSITIVE:
        break;
    case UNARY_OP_NEGATIVE:
		fprintf(fp, "\tsub %s x0 %s\n", c_reg, c_reg);
        break;
    case UNARY_OP_LOGICAL_NEGATION:
		fprintf(fp, "\tseqz %s %s\n", c_reg, c_reg);
        break;
    default:
        break;
    }
    return;
}

void genfBinaryOp(BINARY_OPERATOR op, char *l_reg, char *r_reg, char * reg){
	switch (op)
    {
    case BINARY_OP_ADD:
		fprintf(fp, "\tfadd.s %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_SUB:
		fprintf(fp, "\tfsub.s %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_MUL:
		fprintf(fp, "\tfmul.s %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_DIV:
		fprintf(fp, "\tfdiv.s %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_EQ:
		fprintf(fp, "\tfeq.s %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_GE:
		fprintf(fp, "\tflt.s %s %s %s\n", l_reg, l_reg, r_reg);
		fprintf(fp, "\tsnez %s %s\n", reg, reg );
        break;
    case BINARY_OP_LE:
		fprintf(fp, "\tflt.s %s %s %s\n", l_reg, r_reg, l_reg);
		fprintf(fp, "\tsnez %s %s\n", reg, reg );
        break;
    case BINARY_OP_NE:
		fprintf(fp, "\tfeq.s %s %s %s\n", reg, l_reg, r_reg);
		fprintf(fp, "\tsnez %s %s\n", reg, reg );
        break;
    case BINARY_OP_GT:
		fprintf(fp, "\tflt.s %s %s %s\n", reg, r_reg, l_reg);
        break;
    case BINARY_OP_LT:
		fprintf(fp, "\tflt.s %s %s %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_AND:
        break;
    case BINARY_OP_OR:
        break;
    default:
        break;
    }
	return;
}

void genfUnaryOp(UNARY_OPERATOR op, char *c_reg){
	switch (op)
    {
    case UNARY_OP_POSITIVE:
        break;
    case UNARY_OP_NEGATIVE:
		fprintf(fp, "\tfneg.s %s %s\n", c_reg, c_reg);
        break;
    case UNARY_OP_LOGICAL_NEGATION:
        break;
    default:
        break;
    }
    return;
}

void genConstNode(AST_NODE* Node){
	Node->place = getReg(Node->dataType);
	if(Node->dataType == INT_TYPE){
		fprintf(fp, "\tli %s, %d\n", getRegName(Node), Node->semantic_value.const1->const_u.intval);
	}
	else if(Node->dataType == FLOAT_TYPE){
		int tmp_reg = getReg(INT_TYPE);
		sprintf(constant.value[constant.ptr], "_CONSTANT_%d: .word %d\n", constant.ptr, FloatToInt(Node->semantic_value.const1->const_u.fval));
		fprintf(fp, "\tla %s, _CONSTANT_%d\n", int_reg[tmp_reg], constant.ptr);
		fprintf(fp, "\tflw %s, 0(%s)\n", getRegName(Node), int_reg[tmp_reg]);
		freeReg(tmp_reg, INT_TYPE);
		constant.ptr++;
	}
	else if(Node->dataType == CONST_STRING_TYPE){
		sprintf(constant.value[constant.ptr], "_CONSTANT_%d: .ascii \"%s\"\n", constant.ptr, Node->semantic_value.const1->const_u.sc);
		fprintf(fp, "\tla %s, _CONSTANT_%d\n", getRegName(Node), constant.ptr);
		constant.ptr++;
	}
	else ERR_EXIT("genConstNode");
	return;
}
void genIDNode(AST_NODE* Node){
	char *reg = getOffsetPlace(Node);
	fprintf(fp, "\tlw %s 0(%s)\n", reg, reg);
	return;
}

void genIfStmt(AST_NODE* ifNode){
	return;
}
void genWriteFunction(AST_NODE* functionCallNode){
	return;
}
void genFunctionCall(AST_NODE* functionCallNode){
	AST_NODE *funcName = functionCallNode->child, *paramList = funcName->rightSibling;
	char *name = funcName->semantic_value.identifierSemanticValue.identifierName;
	if(!strcmp(name, "write")){
		AST_NODE *param = paramList->child;
		genNode(param);
		if(param->dataType == INT_TYPE){
			fprintf(fp, "\tmv a0 %s\n", getRegName(param));
			fprintf(fp, "\tjal _write_int\n");
		}
		else if(param->dataType == INT_TYPE){
			fprintf(fp, "\tfmv.s fa0 %s\n", getRegName(param));
			fprintf(fp, "\tjal _write_float\n");
		}
		else{
			fprintf(fp, "\tmv a0 %s\n", getRegName(param));
			fprintf(fp, "\tjal _write_str\n");
		}
	}
	else{
		fprintf(fp, "\tjal _start_%s\n", name);
		FunctionSignature *signature = funcName->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.functionSignature;
		if(signature->returnType != VOID_TYPE){
			functionCallNode->place = getReg(signature->returnType);
			if(functionCallNode->dataType == INT_TYPE){
				fprintf(fp, "\tmv %s a0\n", getRegName(functionCallNode));
			}
			else{
				fprintf(fp, "\tfmv %s fa0\n", getRegName(functionCallNode));
			}
		}
	}
	return;
}

void genWhileStmt(AST_NODE* whileNode){
	return;
}

void genForStmt(AST_NODE* forNode){
	return;
}

void genReturnNode(AST_NODE *Node){
	return;
}

void genBlockNode(AST_NODE* blockNode){
	AST_NODE* Node = blockNode->child;
	while(Node != NULL){
		if(Node->nodeType == VARIABLE_DECL_LIST_NODE){
			AST_NODE *declNode = Node->child;
			while(declNode != NULL){
				genDecl(declNode, LOCAL);
				declNode = declNode->rightSibling;
			}
		}
		else if(Node->nodeType == STMT_LIST_NODE){
			AST_NODE *stmtNode = Node->child;
			while(stmtNode != NULL){
				genStmt(stmtNode);
				stmtNode = stmtNode->rightSibling;
			}
		}
		Node = Node->rightSibling;
	}
}
void genFuncDecl(AST_NODE* typeNode){
	AST_NODE *nameNode = typeNode->rightSibling;
	gen_prologue(nameNode->semantic_value.identifierSemanticValue.identifierName);
	AST_NODE *paramListNode = nameNode->rightSibling;
	AST_NODE *paramDeclNode = paramListNode->child;
	while(paramDeclNode != NULL){
		genDecl(paramDeclNode, LOCAL);
		paramDeclNode = paramDeclNode->rightSibling;
	}
	AST_NODE *blockNode = paramListNode->rightSibling;
	genBlockNode(blockNode);
	gen_epilogue(nameNode->semantic_value.identifierSemanticValue.identifierName);
}
void genVarDecl(AST_NODE* typeNode, TYPE type){
	AST_NODE* varNode = typeNode->rightSibling;
	while(varNode != NULL){
		SymbolTableEntry *entry = varNode->semantic_value.identifierSemanticValue.symbolTableEntry;
		assert(entry != NULL);
		if(varNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID){
			if(type == GLOBAL){
				fprintf(fp, "_g_%s: .word\n", entry->name);
				entry->global = 1;
			}
			else if(type == LOCAL){
				AR_offset -= 4;
				entry->offset = AR_offset;
				entry->global = 0;
			}
			else ERR_EXIT("genVarDecl1");
		}
		else if(varNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID){
			int arr_size = getArraySize(entry->attribute->attr.typeDescriptor->properties.arrayProperties);
			if(type == GLOBAL){
				fprintf(fp, "_g_%s: .space %d\n", entry->name, arr_size*4);
				entry->global = 1;
			}
			else if(type == LOCAL){
				AR_offset -= arr_size*4;
				entry->offset = AR_offset;
				entry->global = 0;
			}
			else ERR_EXIT("genVarDecl2");
		}
		else if(varNode->semantic_value.identifierSemanticValue.kind == WITH_INIT_ID){
			if(type == GLOBAL){
				if(varNode->child->semantic_value.const1->const_type == INTEGERC){
					fprintf(fp, "_g_%s: .word %d\n", entry->name, varNode->child->semantic_value.const1->const_u.intval);
				}
				else if(varNode->child->semantic_value.const1->const_type == FLOATC){
					fprintf(fp, "_g_%s: .word %d\n", entry->name, FloatToInt(varNode->child->semantic_value.const1->const_u.fval));
				}
				else ERR_EXIT("genVarDecl3");
				entry->global = 1;
			}
			else if(type == LOCAL){
				AR_offset -= 4;
				if(varNode->child->semantic_value.const1->const_type == INTEGERC){
					int reg = getReg(INT_TYPE);
					fprintf(fp, "\tli %s, %d\n", int_reg[reg], varNode->child->semantic_value.const1->const_u.intval);
					fprintf(fp, "\tsw %s, %d(sp)\n", int_reg[reg], AR_offset);
				}
				else if(varNode->child->semantic_value.const1->const_type == FLOATC){
					int reg = getReg(FLOAT_TYPE);
					fprintf(fp, "\tli %s, %d\n", float_reg[reg], FloatToInt(varNode->child->semantic_value.const1->const_u.fval));
					fprintf(fp, "\tsw %s, %d(sp)\n", float_reg[reg], AR_offset);
				}
				else ERR_EXIT("genVarDecl4");
				entry->offset = AR_offset;
				entry->global = 0;
			}
			else ERR_EXIT("genVarDecl5");
		}
		else ERR_EXIT("genVarDecl6");
		varNode = varNode->rightSibling;
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
/*int load(AST_NODE *node, int shift){
	int rd;
	if(node->nodeType == CONST_VALUE_NODE){
		if(node->semantic_value.const1->const_type == INTEGERC){
			rd = getReg(INT_TYPE);
			fprintf(fp, "\tla %s, _CONSTANT_%d\n", int_reg[rd], node->place);
			fprintf(fp, "\tlw %s, %d(%s)\n", int_reg[rd], shift, int_reg[rd]);
		}
		else if(node->semantic_value.const1->const_type == FLOATC){
			rd = getReg(FLOAT_TYPE);
			int tmp = getReg(INT_TYPE);
			fprintf(fp, "\tla %s, _CONSTANT_%d\n", int_reg[tmp], node->place);
			fprintf(fp, "\tflw %s, %d(%s)\n", float_reg[rd], shift, int_reg[tmp]);
			freeReg(tmp, INT);
		}
		else{
			rd = getReg(INT_TYPE);
			fprintf(fp, "\tla %s, _CONSTANT_%d\n", float_reg[rd], node->place);
		}
	}
	else if(node->nodeType == IDENTIFIER_NODE){
		SymbolTableEntry *entry = node->semantic_value.identifierSemanticValue.symbolTableEntry;
		TypeDescriptor *td = entry->attribute->attr.typeDescriptor;
		DATA_TYPE data_type;
		if(td->kind == SCALAR_TYPE_DESCRIPTOR){
			data_type = td->properties.dataType;
		}
		else{
			data_type = td->properties.arrayProperties.elementType;
		}
		if(entry->global == 1){
			if(data_type == INT_TYPE){
				rd = getReg(INT_TYPE);
				fprintf(fp, "\tla %s, _g_%s\n", int_reg[rd], entry->name);
				fprintf(fp, "\tlw %s, %d(%s)\n", int_reg[rd], shift, int_reg[rd]);
			}
			else{
				rd = getReg(FLOAT_TYPE);
				int tmp = getReg(INT_TYPE);
				fprintf(fp, "\tla %s, _g_%s\n", int_reg[tmp], entry->name);
				fprintf(fp, "\tflw %s, %d(%s)\n", float_reg[rd], shift, int_reg[tmp]);
				freeReg(tmp, INT);
			}
			fprintf(fp, "\tlw %s, %d(%s)\n", rd, shift, rd);
		}
		else{ //local
			if(data_type == INT_TYPE){
				rd = getReg(INT_TYPE);
				fprintf(fp, "\tlw %s, %d(sp)\n", int_reg[rd], entry->offset + shift);
			}
			else{
				rd = getReg(FLOAT_TYPE);
				fprintf(fp, "\tflw %s, %d(sp)\n", float_reg[rd], entry->offset + shift);
			}	
		}
	}
	return rd;
}*/
