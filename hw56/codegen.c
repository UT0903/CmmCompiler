#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>
#include "header.h"
#include "symbolTable.h"
//#include "reg_alloc.h"
#define ERR_EXIT(a) { fprintf(stderr, "%s\n", a); exit(0); }
#define INT_REG_NUM 17
#define FLOAT_REG_NUM 8
typedef enum{
	GLOBAL,
	LOCAL
}TYPE;

FILE *fp;
char int_reg[INT_REG_NUM][10] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11"};
int used_int[INT_REG_NUM] = {};
char float_reg[FLOAT_REG_NUM][10] = {"ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7"};
int used_float[FLOAT_REG_NUM] = {};
int int_ptr, float_ptr, L_ptr;
int AR_offset, param_offset;
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
void genGlobalVarDecl(AST_NODE* typeNode);
void genLocalVarDecl(AST_NODE* typeNode);
void genFuncDecl(AST_NODE* typeNode);
void ReleaseConst();

void genWhileStmt(AST_NODE* whileNode);
void genForStmt(AST_NODE* forNode);
void genAssignmentStmt(AST_NODE* assignmentNode);
void genIfStmt(AST_NODE* ifNode);
void genWriteFunction(AST_NODE* functionCallNode);
void genFunctionCall(AST_NODE* functionCallNode);
int getOffsetPlace(AST_NODE* Node);
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
void genRead(AST_NODE* functionCallNode);
void genFread(AST_NODE* functionCallNode);
int pushParamOnAR(AST_NODE* paramListNode);
void popParam(int num);
void typeConservation(AST_NODE *Node, DATA_TYPE target_type);
DATA_TYPE genReturnType(AST_NODE *now);

int int_reg_use = 0, float_reg_use = 0;


int getReg(DATA_TYPE type){
	int ret;
	if(type == INT_TYPE || type == CONST_STRING_TYPE){
		ret = int_ptr;
		// fprintf(stderr, "int less %d\n", INT_REG_NUM - int_reg_use);
		if(INT_REG_NUM - int_reg_use == 0){
			perror("no reg\n");
			exit(0);
		}
		while(used_int[ret]){
			int_ptr = (int_ptr + 1) % INT_REG_NUM;
			ret = int_ptr;
		}
		used_int[ret] = 1;
		//fprintf(stderr,"use %s\n", int_reg[ret]);
		int_ptr = (int_ptr + 1) % INT_REG_NUM;
		int_reg_use ++;
	}
	else{
		ret = float_ptr;
		// fprintf(stderr, "float less %d\n", FLOAT_REG_NUM - float_reg_use);
		if(INT_REG_NUM - float_reg_use == 0){
			perror("no reg\n");
			exit(0);
		}
		while (used_float[ret])
		{
			float_ptr = (float_ptr + 1) % FLOAT_REG_NUM;
			ret = float_ptr;
		}
		used_float[ret] = 1;
		//fprintf(stderr,"use %s\n", float_reg[ret]);
		float_ptr = (float_ptr + 1) % FLOAT_REG_NUM;
		float_reg_use ++;
	}
	return ret;
}
void freeReg(int reg, DATA_TYPE type){
	// fprintf(stderr, "freeReg\n");
	if(type == INT_TYPE || type == CONST_STRING_TYPE){
		used_int[reg] = 0;
		int_reg_use --;
		// fprintf(stderr, "free: int less %d\n", INT_REG_NUM - int_reg_use);
		//fprintf(stderr, "free %s\n", int_reg[reg]);
	}
	else{
		used_float[reg] = 0;
		float_reg_use --;
		// fprintf(stderr, "free: float less %d\n", FLOAT_REG_NUM - float_reg_use);
		//fprintf(stderr,"free %s\n", float_reg[reg]);
	}
	return;
}

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
		else{
			genDecl(declNode, GLOBAL);
		}
		declNode = declNode->rightSibling;
	}
	ReleaseConst();
	fclose(fp);
	fprintf(stderr, "End Code generation\n");
}

void genDecl(AST_NODE *declNode, TYPE type){
	
	//fprintf(stderr, "declNode type: %d\n", declNode->nodeType);
	assert(declNode->nodeType == DECLARATION_NODE);
	switch(declNode->semantic_value.declSemanticValue.kind){
		case(VARIABLE_DECL):
			if(type == GLOBAL){
				genGlobalVarDecl(declNode->child);
			}
			else if(type == LOCAL){
				genLocalVarDecl(declNode->child);
			}
			else ERR_EXIT("gen_decl");
			break;
		case(FUNCTION_PARAMETER_DECL):
			fprintf(stderr, "Eror in genDecl\n");
			exit(0);
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
		fprintf(stderr, "codegen stmtNode->nodeType: %d\n", stmtNode->nodeType);
        perror("input no stmt");
        exit(0);
    }
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

int getOffsetPlace(AST_NODE* Node){
	int reg_num = getReg(INT_TYPE);
	char *reg = int_reg[reg_num];
	SymbolTableEntry *entry = Node->semantic_value.identifierSemanticValue.symbolTableEntry;
	if(entry->global){
		if(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR){
			fprintf(fp, "\tla %s, _g_%s\n", reg, Node->semantic_value.identifierSemanticValue.identifierName);
		}
		else{
			AST_NODE *dim = Node->child;
			int *arraySize = entry->attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension;
			int dimSize = entry->attribute->attr.typeDescriptor->properties.arrayProperties.dimension;
			int tmp_reg = getReg(INT_TYPE);
			int size_reg = getReg(INT_TYPE);
			fprintf(fp, "\tli %s, 0\n", int_reg[tmp_reg]);
			for(int i = dimSize - 2; i >= 0; i --){
				genNode(dim);
				char *dim_reg = getRegName(dim);
				fprintf(fp, "\tadd %s, %s, %s\n", int_reg[tmp_reg], int_reg[tmp_reg], dim_reg);
				fprintf(fp, "\tli %s, %d\n", int_reg[size_reg], arraySize[dimSize - i - 1]);
				fprintf(fp, "\tmul %s, %s, %s\n", int_reg[tmp_reg], int_reg[tmp_reg], int_reg[size_reg]);
				freeReg(dim->place, dim->dataType);
				dim = dim->rightSibling;
			}
			genNode(dim);
			char *dim_reg = getRegName(dim);
			fprintf(fp, "\tadd %s, %s, %s\n", int_reg[tmp_reg], int_reg[tmp_reg], dim_reg);
			fprintf(fp, "\tla %s, _g_%s\n", reg, Node->semantic_value.identifierSemanticValue.identifierName);
			fprintf(fp, "\tslli %s, %s, 2\n", int_reg[tmp_reg], int_reg[tmp_reg]);
			fprintf(fp, "\tadd %s, %s, %s\n", reg, reg, int_reg[tmp_reg]);
			freeReg(dim->place, dim->dataType);
			freeReg(tmp_reg, INT_TYPE);
			freeReg(size_reg, INT_TYPE);
		}
	}
	else{
		if(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR){
			fprintf(fp, "\tli %s, %d\n", reg, Node->semantic_value.identifierSemanticValue.symbolTableEntry->offset);
			fprintf(fp, "\tadd %s, fp, %s\n", reg, reg);
		}
		else{
			AST_NODE *dim = Node->child;
			int *arraySize = entry->attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension;
			int dimSize = entry->attribute->attr.typeDescriptor->properties.arrayProperties.dimension;
			int tmp_reg = getReg(INT_TYPE);
			int size_reg = getReg(INT_TYPE);
			fprintf(fp, "\tadd %s, x0, x0\n", int_reg[tmp_reg]);
			for(int i = dimSize - 2; i >= 0; i --){
				genNode(dim);
				char *dim_reg = getRegName(dim);
				fprintf(fp, "\tadd %s, %s, %s\n", int_reg[tmp_reg], int_reg[tmp_reg], dim_reg);
				fprintf(fp, "\tli %s, %d\n", int_reg[size_reg], arraySize[dimSize - i - 1]);
				fprintf(fp, "\tmul %s, %s, %s\n", int_reg[tmp_reg], int_reg[tmp_reg], int_reg[size_reg]);
				freeReg(dim->place, dim->dataType);
				dim = dim->rightSibling;
			}
			genNode(dim);
			char *dim_reg = getRegName(dim);
			fprintf(fp, "\tadd %s, %s, %s\n", int_reg[tmp_reg], int_reg[tmp_reg], dim_reg);
			fprintf(fp, "\tli %s, %d\n", reg, Node->semantic_value.identifierSemanticValue.symbolTableEntry->offset);
			fprintf(fp, "\tadd %s, fp, %s\n", reg, reg);
			fprintf(fp, "\tslli %s, %s, 2\n", int_reg[tmp_reg], int_reg[tmp_reg]);
			fprintf(fp, "\tadd %s, %s, %s\n", reg, reg, int_reg[tmp_reg]);
			freeReg(dim->place, dim->dataType);
			freeReg(tmp_reg, INT_TYPE);
			freeReg(size_reg, INT_TYPE);
		}
	}
	return reg_num;
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
		if(op == BINARY_OP_AND){
			genNode(l);
			int L = L_ptr++;
			Node->place = getReg(Node->dataType);
			char  *reg = getRegName(Node);
			fprintf(fp, "\tmv %s, zero\n", reg);
			fprintf(fp, "\tbeqz %s, L%d\n", getRegName(l), L);
			genNode(r);
			fprintf(fp, "\tsnez %s, %s\n", reg, getRegName(r));
			fprintf(fp, "L%d:", L);
		}
		else if(op == BINARY_OP_OR){
			int L = L_ptr++;
			genNode(l);
			char *l_reg = getRegName(l);
			Node->place = getReg(Node->dataType);
			char  *reg = getRegName(Node);
			fprintf(fp, "\tli %s, 1\n", reg);
			fprintf(fp, "\tseqz %s, %s\n", l_reg, l_reg);
			fprintf(fp, "\tbeqz %s, L%d\n", l_reg, L);
			genNode(r);
			char *r_reg = getRegName(r);
			fprintf(fp, "\tsnez %s, %s\n", reg, r_reg);
			fprintf(fp, "L%d:", L);
		}
		else{
			genNode(l);
			genNode(r);
			Node->place = getReg(Node->dataType);
			char  *reg = getRegName(Node);
			if(l->dataType == FLOAT_TYPE || r->dataType == FLOAT_TYPE){
				if(l->dataType != FLOAT_TYPE){
					typeConservation(l, FLOAT_TYPE);
				}
				if(r->dataType != FLOAT_TYPE){
					typeConservation(r, FLOAT_TYPE);
				}
				genfBinaryOp(op, getRegName(l), getRegName(r), reg);
			}
			else
				genBinaryOp(op, getRegName(l), getRegName(r), reg);
		}
		freeReg(l->place, l->dataType);
		freeReg(r->place, r->dataType);
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
		freeReg(child->place, child->dataType);
	}
	return;
}

void genBinaryOp(BINARY_OPERATOR op, char *l_reg, char *r_reg, char * reg){
	int L;
	switch (op)
    {
    case BINARY_OP_ADD:
		fprintf(fp, "\tadd %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_SUB:
		fprintf(fp, "\tsub %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_MUL:
		fprintf(fp, "\tmul %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_DIV:
		fprintf(fp, "\tdiv %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_EQ:
		fprintf(fp, "\txor %s, %s, %s\n", l_reg, l_reg, r_reg);
		fprintf(fp, "\tseqz %s, %s\n", reg, l_reg );
        break;
    case BINARY_OP_GE:
		fprintf(fp, "\tslt %s, %s, %s\n", l_reg, l_reg, r_reg);
		fprintf(fp, "\tseqz %s, %s\n", reg, l_reg );
        break;
    case BINARY_OP_LE:
		fprintf(fp, "\tslt %s, %s, %s\n", l_reg, r_reg, l_reg);
		fprintf(fp, "\tseqz %s, %s\n", reg, l_reg );
        break;
    case BINARY_OP_NE:
		fprintf(fp, "\txor %s, %s, %s\n", l_reg, l_reg, r_reg);
		fprintf(fp, "\tsnez %s, %s\n", reg, l_reg );
        break;
    case BINARY_OP_GT:
		fprintf(fp, "\tslt %s, %s, %s\n", reg, r_reg, l_reg);
        break;
    case BINARY_OP_LT:
		fprintf(fp, "\tslt %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_AND:
		L = L_ptr++;
		fprintf(fp, "\tmv %s, zero\n", reg);
		fprintf(fp, "\tbeqz %s, L%d\n", l_reg, L);
		fprintf(fp, "\tsnez %s, %s\n", reg, r_reg);
		fprintf(fp, "L%d:", L);
        break;
    case BINARY_OP_OR:
		L = L_ptr++;
		fprintf(fp, "\tmv %s, zero\n", reg);
		fprintf(fp, "\tseqz %s, %s\n", l_reg, l_reg);
		fprintf(fp, "\tseqz %s, %s\n", r_reg, r_reg);
		fprintf(fp, "\tbeqz %s, L%d\n", l_reg, L);
		fprintf(fp, "\tsnez %s, %s\n", reg, r_reg);
		fprintf(fp, "L%d:", L);
		fprintf(fp, "\tseqz %s, %s\n", reg, reg);
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
		fprintf(fp, "\tsub %s, x0, %s\n", c_reg, c_reg);
        break;
    case UNARY_OP_LOGICAL_NEGATION:
		fprintf(fp, "\tseqz %s, %s\n", c_reg, c_reg);
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
		fprintf(fp, "\tfadd.s %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_SUB:
		fprintf(fp, "\tfsub.s %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_MUL:
		fprintf(fp, "\tfmul.s %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_DIV:
		fprintf(fp, "\tfdiv.s %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_EQ:
		fprintf(fp, "\tfeq.s %s, %s, %s\n", reg, l_reg, r_reg);
        break;
    case BINARY_OP_GE:
		fprintf(fp, "\tflt.s %s, %s, %s\n", reg, l_reg, r_reg);
		fprintf(fp, "\tseqz %s, %s\n", reg, reg );
        break;
    case BINARY_OP_LE:
		fprintf(fp, "\tflt.s %s, %s, %s\n", reg, r_reg, l_reg);
		fprintf(fp, "\tseqz %s, %s\n", reg, reg );
        break;
    case BINARY_OP_NE:
		fprintf(fp, "\tfeq.s %s, %s, %s\n", reg, l_reg, r_reg);
		fprintf(fp, "\tseqz %s, %s\n", reg, reg );
        break;
    case BINARY_OP_GT:
		fprintf(fp, "\tflt.s %s, %s, %s\n", reg, r_reg, l_reg);
        break;
    case BINARY_OP_LT:
		fprintf(fp, "\tflt.s %s, %s, %s\n", reg, l_reg, r_reg);
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
		fprintf(fp, "\tfneg.s %s, %s\n", c_reg, c_reg);
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
		//newConst(); //TODO
		sprintf(constant.value[constant.ptr], "_CONSTANT_%d: .word %d\n", constant.ptr, FloatToInt(Node->semantic_value.const1->const_u.fval));
		fprintf(fp, "\tla %s, _CONSTANT_%d\n", int_reg[tmp_reg], constant.ptr);
		fprintf(fp, "\tflw %s, 0(%s)\n", getRegName(Node), int_reg[tmp_reg]);
		freeReg(tmp_reg, INT_TYPE);
		constant.ptr++;
	}
	else if(Node->dataType == CONST_STRING_TYPE){
		sprintf(constant.value[constant.ptr], "_CONSTANT_%d: .string %s\n", constant.ptr, Node->semantic_value.const1->const_u.sc);
		fprintf(fp, "\tla %s, _CONSTANT_%d\n", getRegName(Node), constant.ptr);
		constant.ptr++;
	}
	else ERR_EXIT("genConstNode");
	return;
}
void genIDNode(AST_NODE* Node){
	int reg_num = getOffsetPlace(Node);
	char *reg = int_reg[reg_num];
	Node->place = getReg(Node->dataType);
	char *n_reg = getRegName(Node);
	if(Node->dataType == INT_TYPE)
		fprintf(fp, "\tlw %s, 0(%s)\n", n_reg, reg);
	else{
		fprintf(fp, "\tflw %s, 0(%s)\n", n_reg, reg);
	}
	freeReg(reg_num, INT_TYPE);
	return;
}

void genIfStmt(AST_NODE* ifNode){
	AST_NODE *test = ifNode->child;
	AST_NODE *stmt = test->rightSibling;
	AST_NODE *ELSE = stmt->rightSibling;
	if(ELSE->nodeType == NUL_NODE){
		genNode(test);
		int L1 = L_ptr++, L2 = L_ptr++;
		fprintf(fp, "\tbnez %s, _L%d\n", getRegName(test), L1);
		int j_reg = getReg(INT_TYPE);
		fprintf(fp, "\tla %s, _L%d\n", int_reg[j_reg], L2);
		fprintf(fp, "\tjr %s\n", int_reg[j_reg]);
		freeReg(j_reg, INT_TYPE);
		freeReg(test->place, test->dataType);
		fprintf(fp, "_L%d:\n", L1);
		genStmt(stmt);
		fprintf(fp, "_L%d:\n", L2);
	}
	else{
		genNode(test);
		int L1 = L_ptr++, L2 = L_ptr++, L3 = L_ptr++;
		fprintf(fp, "\tbnez %s, _L%d\n", getRegName(test), L1);
		int j_reg = getReg(INT_TYPE);
		fprintf(fp, "\tla %s, _L%d\n", int_reg[j_reg], L2);
		fprintf(fp, "\tjr %s\n", int_reg[j_reg]);
		freeReg(j_reg, INT_TYPE);
		freeReg(test->place, test->dataType);
		fprintf(fp, "_L%d:\n", L1);
		genStmt(stmt);
		j_reg = getReg(INT_TYPE);
		fprintf(fp, "\tla %s, _L%d\n", int_reg[j_reg], L3);
		fprintf(fp, "\tjr %s\n", int_reg[j_reg]);
		freeReg(j_reg, INT_TYPE);
		fprintf(fp, "_L%d:\n", L2);
		genStmt(ELSE);
		fprintf(fp, "_L%d:\n", L3);
	}
	return;
}

void genWriteFunction(AST_NODE* functionCallNode){
	AST_NODE *funcName = functionCallNode->child, *paramList = funcName->rightSibling;
	AST_NODE *param = paramList->child;
	genNode(param);
	int j_reg = getReg(INT_TYPE);
	if(param->dataType == INT_TYPE){
		fprintf(fp, "\tmv a0, %s\n", getRegName(param));
		fprintf(fp, "\tla %s, _write_int\n", int_reg[j_reg]);
		fprintf(fp, "\tjalr 0(%s)\n", int_reg[j_reg]);
	}
	else if(param->dataType == FLOAT_TYPE){
		fprintf(fp, "\tfmv.s fa0, %s\n", getRegName(param));
		fprintf(fp, "\tla %s, _write_float\n", int_reg[j_reg]);
		fprintf(fp, "\tjalr 0(%s)\n", int_reg[j_reg]);
	}
	else{
		fprintf(fp, "\tmv a0, %s\n", getRegName(param));
		fprintf(fp, "\tla %s, _write_str\n", int_reg[j_reg]);
		fprintf(fp, "\tjalr 0(%s)\n", int_reg[j_reg]);
	}
	freeReg(j_reg, INT_TYPE);
	freeReg(param->place, param->dataType);
	return;
}

void genRead(AST_NODE* functionCallNode){
	int j_reg = getReg(INT_TYPE);
	fprintf(fp, "\tla %s, _read_int\n", int_reg[j_reg]);
	fprintf(fp, "\tjalr 0(%s)\n", int_reg[j_reg]);
	freeReg(j_reg, INT_TYPE);
	functionCallNode->place = getReg(INT_TYPE);
	fprintf(fp, "\tmv %s, a0\n", getRegName(functionCallNode));
	return;
}

void genFread(AST_NODE* functionCallNode){
	int j_reg = getReg(INT_TYPE);
	fprintf(fp, "\tla %s, _read_float\n", int_reg[j_reg]);
	fprintf(fp, "\tjalr 0(%s)\n", int_reg[j_reg]);
	freeReg(j_reg, INT_TYPE);
	functionCallNode->place = getReg(FLOAT_TYPE);
	fprintf(fp, "\tfmv.s %s, fa0\n", getRegName(functionCallNode));
	return;
}
void genAssignmentStmt(AST_NODE* assignmentNode){
	AST_NODE *l = assignmentNode->child;
    AST_NODE *r = l->rightSibling;
	genNode(r);
	
	int reg_num = getOffsetPlace(l);
	char *id_reg = int_reg[reg_num];
	if(l->dataType == INT_TYPE){
		if(r->dataType != INT_TYPE){
			typeConservation(r, INT_TYPE);
		}
		fprintf(fp, "\tsw %s, 0(%s)\n", getRegName(r), id_reg);
	}
	else{
		if(r->dataType != FLOAT_TYPE){
			typeConservation(r, FLOAT_TYPE);
		}
		fprintf(fp, "\tfsw %s, 0(%s)\n", getRegName(r), id_reg);
	}
	freeReg(reg_num, INT_TYPE);
	freeReg(r->place, r->dataType);
	return;
}

void genFunctionCall(AST_NODE* functionCallNode){
	AST_NODE *funcName = functionCallNode->child, *paramList = funcName->rightSibling;
	char *name = funcName->semantic_value.identifierSemanticValue.identifierName;
	//printf("func call name: %s\n", name);
	if(!strcmp(name, "write")){
		genWriteFunction(functionCallNode);
	}
	else if(!strcmp(name, "read")){
		genRead(functionCallNode);
	}
	else if(!strcmp(name, "fread")){
		genFread(functionCallNode);
	}
	else{
		int paramCount = 0;
		if(paramList->nodeType == NUL_NODE){}
		else if(paramList->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE){
			AST_NODE* paramNode = paramList->child;
			Parameter* prmt = funcName->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.functionSignature->parameterList;
			while(paramNode != NULL){
				genNode(paramNode);
				//fprintf(stderr, "datatype: %d\n", paramNode->dataType);
				if(paramNode->dataType == INT_TYPE){
					if(prmt->type->properties.dataType == FLOAT_TYPE){
						typeConservation(paramNode, INT_TYPE);
					}
					fprintf(fp, "\tsd %s, 0(sp)\n", getRegName(paramNode));
					fprintf(fp, "\taddi sp, sp, -8\n");
				}
				else{
					if(prmt->type->properties.dataType == INT_TYPE){
						typeConservation(paramNode, FLOAT_TYPE);
					}
					fprintf(fp, "\tfsd %s, 0(sp)\n", getRegName(paramNode));
					fprintf(fp, "\taddi sp, sp, -8\n");
				}
				paramCount++;
				freeReg(paramNode->place, paramNode->dataType);
				paramNode = paramNode->rightSibling;
				prmt = prmt->next;
			}
		}
		else{
			fprintf(stderr, "error in pushParamOnAR\n");
		}
		int j_reg = getReg(INT_TYPE);
		fprintf(fp, "\tla %s, _start_%s\n", int_reg[j_reg], name);
		fprintf(fp, "\tjalr 0(%s)\n", int_reg[j_reg]);
		freeReg(j_reg, INT_TYPE);
		fprintf(fp, "\taddi sp, sp, %d\n", paramCount*8);
		FunctionSignature *signature = funcName->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.functionSignature;
		if(signature->returnType != VOID_TYPE){
			functionCallNode->place = getReg(signature->returnType);
			if(functionCallNode->dataType == INT_TYPE){
				fprintf(fp, "\tmv %s, a0\n", getRegName(functionCallNode));
			}
			else{
				fprintf(fp, "\tfmv.s %s, fa0\n", getRegName(functionCallNode));
			}
		}
	}
	return;
}
void genWhileStmt(AST_NODE* whileNode){
	AST_NODE *test = whileNode->child;
	AST_NODE *stmt = test->rightSibling;
	int L = L_ptr++, L2 = L_ptr++, L3 = L_ptr++;
	fprintf(fp, "_L%d:\n", L);
	genNode(test);
	fprintf(fp, "\tbnez %s, _L%d\n", getRegName(test), L2);
	freeReg(test->place, test->dataType);
	int j_reg = getReg(INT_TYPE);
	fprintf(fp, "\tla %s, _L%d\n", int_reg[j_reg], L3);
	fprintf(fp, "\tjr %s\n", int_reg[j_reg]);
	freeReg(j_reg, INT_TYPE);
	fprintf(fp, "_L%d:\n", L2);
	genStmt(stmt);
	j_reg = getReg(INT_TYPE);
	fprintf(fp, "\tla %s, _L%d\n", int_reg[j_reg], L);
	fprintf(fp, "\tjr %s\n", int_reg[j_reg]);
	freeReg(j_reg, INT_TYPE);
	fprintf(fp, "_L%d:\n", L3);
	return;
}

void genForStmt(AST_NODE* forNode){
    AST_NODE *assign_expr_list = forNode->child, *relop_expr_list = assign_expr_list->rightSibling, *second_assign_expr_list = relop_expr_list->rightSibling, *stmt = second_assign_expr_list->rightSibling;
	int L1 = L_ptr++, L2 = L_ptr++, L3 = L_ptr++, L4 = L_ptr++;
    if(assign_expr_list->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE){
        AST_NODE *assign_expr = assign_expr_list->child;
        while(assign_expr){
            if(assign_expr->nodeType == STMT_NODE && assign_expr->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT){
                genAssignmentStmt(assign_expr);
            }
            else{
                genNode(assign_expr);
				freeReg(assign_expr->place, assign_expr->dataType);
			}
            assign_expr = assign_expr->rightSibling;
        }
    }
	fprintf(fp, "L%d:\n", L1);
    if(relop_expr_list->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE){
        AST_NODE *relop_expr = relop_expr_list->child;
        while(relop_expr){
            genNode(relop_expr);
			fprintf(fp, "\tbeqz %s, L%d\n", getRegName(relop_expr), L4);
			freeReg(relop_expr->place, relop_expr->dataType);
            relop_expr = relop_expr->rightSibling;
        }
		fprintf(fp, "\tj L%d\n", L3);
    }
	fprintf(fp, "L%d:\n", L2);
    if(second_assign_expr_list->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE){
        AST_NODE *assign_expr = second_assign_expr_list->child;
        while(assign_expr){
            if(assign_expr->nodeType == STMT_NODE && assign_expr->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT){
                genAssignmentStmt(assign_expr);
            }
            else{
                genNode(assign_expr);
				freeReg(assign_expr->place, assign_expr->dataType);
			}
            assign_expr = assign_expr->rightSibling;
        }
		fprintf(fp, "\tj L%d\n", L1);
    }
	fprintf(fp, "L%d:\n", L3);
    genStmt(stmt);
	fprintf(fp, "\tj L%d\n", L2);
	fprintf(fp, "L%d:\n", L4);
}

void genReturnNode(AST_NODE *Node){
	AST_NODE *now = Node;
    while (now != NULL && now->nodeType != DECLARATION_NODE && now->semantic_value.declSemanticValue.kind != FUNCTION_DECL)
    {
        now = now->parent;
    }
    if(now == NULL){
        perror("wrong return place");
        exit(0);
        return ;
    }
    now = now->child->rightSibling;
    SymbolTableEntry *entry = now->semantic_value.identifierSemanticValue.symbolTableEntry;
    DATA_TYPE return_type = entry->attribute->attr.functionSignature->returnType;
	if(Node->child->nodeType != NUL_NODE){
		genNode(Node->child);
		if(return_type == INT_TYPE){
			if(Node->child->dataType != INT_TYPE){
				typeConservation(Node->child, INT_TYPE);
			}
			fprintf(fp, "\tmv a0, %s\n", getRegName(Node->child));
		}
		else{
			if(Node->child->dataType != FLOAT_TYPE){
				typeConservation(Node->child, FLOAT_TYPE);
			}
			fprintf(fp, "\tfmv.s fa0, %s\n", getRegName(Node->child));
		}
		freeReg(Node->child->place, Node->child->dataType);
	}
	
	int j_reg = getReg(INT_TYPE);

	if(strcmp(now->semantic_value.identifierSemanticValue.identifierName, "main") == 0){
		fprintf(fp, "\tla %s, _end_MAIN\n", int_reg[j_reg]);
		fprintf(fp, "\tjr %s\n", int_reg[j_reg]);
	}
	else{
		fprintf(fp, "\tla %s, _end_%s\n", int_reg[j_reg], now->semantic_value.identifierSemanticValue.identifierName);
		fprintf(fp, "\tjr %s\n", int_reg[j_reg]);
	}
	freeReg(j_reg, INT_TYPE);
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
		else ERR_EXIT("genBlockNode");
		Node = Node->rightSibling;
	}
}
void gen_prologue (char *name){
	if(strcmp(name, "main") == 0){
		fprintf(fp, "\tla ra, _frameSize_MAIN\n");
	}
	else{
		fprintf(fp, "\tla ra, _frameSize_%s\n", name);
	}
	fprintf(fp, "\tlw ra, 0(ra)\n");
	fprintf(fp, "\tsub sp, sp, ra\n"); // push new AR
	for(int i = 0; i < INT_REG_NUM; i++){
		fprintf(fp, "\tsd %s, %d(sp)\n", int_reg[i], i*8 + 8);
	}
	for(int i = 0; i < FLOAT_REG_NUM; i++){
		fprintf(fp, "\tfsw %s, %d(sp)\n", float_reg[i], i*4 + 8 + INT_REG_NUM*8);
	}
	AR_offset = 0;
	param_offset = 0;
}
void gen_epilogue(char *name){
	if(strcmp(name, "main") == 0){
		fprintf(fp, "_end_MAIN:\n");
	}
	else{
		fprintf(fp, "_end_%s:\n", name);
	}
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
	if(strcmp(name, "main") == 0){
		fprintf(fp, "_frameSize_MAIN:\t.word\t%d\n", INT_REG_NUM*8 + FLOAT_REG_NUM*4 + 8 - AR_offset);
	}
	else{
		fprintf(fp, "_frameSize_%s:\t.word\t%d\n", name, INT_REG_NUM*8 + FLOAT_REG_NUM*4 + 8 - AR_offset);
	}
}
void genFuncDecl(AST_NODE* typeNode){
	AST_NODE *nameNode = typeNode->rightSibling;
	//printf("funcName: %s\n", nameNode->semantic_value.identifierSemanticValue.identifierName);
	//gen_prologue(nameNode->semantic_value.identifierSemanticValue.identifierName);
	fprintf(fp, "\t.text\n");
	if(strcmp(nameNode->semantic_value.identifierSemanticValue.identifierName, "main") == 0){
		fprintf(fp, "_start_MAIN:\n");
	}
	else{
		fprintf(fp, "_start_%s:\n", nameNode->semantic_value.identifierSemanticValue.identifierName);
	}
	int paramCount = nameNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.functionSignature->parametersCount;
	
	fprintf(fp, "\tsd fp, -8(sp)\n"); // save old fp
	fprintf(fp, "\tsd ra, 0(sp)\n"); // store return address
	fprintf(fp, "\taddi fp, sp, -8\n"); // new fp
	fprintf(fp, "\taddi sp, sp, -16\n"); // new sp
	int offset = 8 + 8*paramCount;
	AST_NODE *paramListNode = nameNode->rightSibling;
	AST_NODE *paramDeclNode = paramListNode->child;
	while(paramDeclNode != NULL){
		paramDeclNode->child->rightSibling->semantic_value.identifierSemanticValue.symbolTableEntry->offset = offset;
		offset -= 8;
		paramDeclNode = paramDeclNode->rightSibling;
	}
	assert(offset == 8);
	gen_prologue(nameNode->semantic_value.identifierSemanticValue.identifierName);
	AST_NODE *blockNode = paramListNode->rightSibling;
	genBlockNode(blockNode);
	gen_epilogue(nameNode->semantic_value.identifierSemanticValue.identifierName);
}
void genGlobalVarDecl(AST_NODE* typeNode){
	AST_NODE* varNode = typeNode->rightSibling;
	while(varNode != NULL){
		SymbolTableEntry *entry = varNode->semantic_value.identifierSemanticValue.symbolTableEntry;
		assert(entry != NULL);
		if(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR){
			if(varNode->semantic_value.identifierSemanticValue.kind == WITH_INIT_ID){
				if(varNode->child->semantic_value.const1->const_type == INTEGERC){
					fprintf(fp, "_g_%s: .word %d\n", entry->name, varNode->child->semantic_value.const1->const_u.intval);
				}
				else if(varNode->child->semantic_value.const1->const_type == FLOATC){
					fprintf(fp, "_g_%s: .word %d\n", entry->name, FloatToInt(varNode->child->semantic_value.const1->const_u.fval));
				}
				else ERR_EXIT("genGlobalVarDecl1");
				entry->global = 1;
			}
			else if(varNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID){
				fprintf(fp, "_g_%s: .word 0\n", entry->name);
				entry->global = 1;
			}
			else ERR_EXIT("genGlobalVarDecl2");
			
		}
		else if(entry->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR){
			int arr_size = getArraySize(entry->attribute->attr.typeDescriptor->properties.arrayProperties);
			fprintf(fp, "_g_%s: .space %d\n", entry->name, arr_size*4);
			entry->global = 1;
		}
		else ERR_EXIT("genGlobalVarDecl3");
		varNode = varNode->rightSibling;
	}
}
void genLocalVarDecl(AST_NODE* typeNode){
	AST_NODE* varNode = typeNode->rightSibling;
	while(varNode != NULL){
		SymbolTableEntry *entry = varNode->semantic_value.identifierSemanticValue.symbolTableEntry;
		assert(entry != NULL);
		if(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR){
			if(varNode->semantic_value.identifierSemanticValue.kind == WITH_INIT_ID){
				AR_offset -= 4;
				genNode(varNode->child);
				int reg = getReg(INT_TYPE);
				if(entry->attribute->attr.typeDescriptor->properties.dataType == FLOAT_TYPE){
					if(varNode->child->dataType == INT_TYPE){
						typeConservation(varNode->child, FLOAT_TYPE);
					}
					fprintf(fp, "\tli %s, %d\n", int_reg[reg], AR_offset);
					fprintf(fp, "\tadd %s, fp, %s\n", int_reg[reg], int_reg[reg]);
					fprintf(fp, "\tfsw %s, 0(%s)\n", getRegName(varNode->child), int_reg[reg]);
				}
				else if(entry->attribute->attr.typeDescriptor->properties.dataType == INT_TYPE){
					if(varNode->child->dataType == FLOAT_TYPE){
						typeConservation(varNode->child, INT_TYPE);
					}
					fprintf(fp, "\tli %s, %d\n", int_reg[reg], AR_offset);
					fprintf(fp, "\tadd %s, fp, %s\n", int_reg[reg], int_reg[reg]);
					fprintf(fp, "\tsw %s, 0(%s)\n", getRegName(varNode->child), int_reg[reg]);
				}
				else ERR_EXIT("genLocalVarDecl1");
				
				freeReg(reg, INT_TYPE);
				entry->offset = AR_offset;
				entry->global = 0;
			}
			else if(varNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID){
				AR_offset -= 4;
				entry->offset = AR_offset;
				entry->global = 0;
			}
			else ERR_EXIT("genLocalVarDecl2");
			
		}
		else if(entry->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR){
			int arr_size = getArraySize(entry->attribute->attr.typeDescriptor->properties.arrayProperties);
			AR_offset -= arr_size*4;
			entry->offset = AR_offset;
			entry->global = 0;
		}
		else ERR_EXIT("genLocalVarDecl3");
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

void typeConservation(AST_NODE *Node, DATA_TYPE target_type){
	if(target_type == INT_TYPE){
		int reg_num = getReg(INT_TYPE);
		fprintf(fp, "\tfcvt.w.s %s, %s\n", int_reg[reg_num], getRegName(Node));
		freeReg(Node->place, Node->dataType);
		Node->place = reg_num;
		Node->dataType = INT_TYPE;
	}
	else{
		int reg_num = getReg(FLOAT_TYPE);
		fprintf(fp, "\tfcvt.s.w %s, %s\n", float_reg[reg_num], getRegName(Node));
		freeReg(Node->place, Node->dataType);
		Node->place = reg_num;
		Node->dataType = FLOAT_TYPE;
	}
}
