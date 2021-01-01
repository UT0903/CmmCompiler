#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "header.h"
#include "symbolTable.h"
#define ERR_EXIT(a) { fprintf(stderr, "%s\n", a); exit(0); }
#define REGNUM 25
typedef enum NodeKind{
    NOTUSED,
    ID,
    CONST
}NodeKind;
typedef struct{
    char name[10];
    int dirty;
    NodeKind kind;
    SymbolTableEntry *entry;
    int shift;
    int const_val;
}REG;
REG reg[REGNUM];
void InitReg();
void FlushReg();
int getTempReg(DATA_TYPE type);
int CheckInRegister(AST_NODE *node);
int useReg(AST_NODE *node, int shift, int readWrite);
char reg_name[REGNUM][10] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6", \ //7
     "ft0", "ft1", "ft2", "ft3", "ft4", "ft5", "ft6", "ft7", \ //8
     "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", \ //10
     "fs2", "fs3", "fs4", "fs5", "fs6", "fs7", "fs8", "fs9", "fs10", "fs11"}; //10

int CheckSRegister(AST_NODE *node, int shift){
    if(node->nodeType == IDENTIFIER_NODE){
        SymbolTableEntry* entry = node->semantic_value.identifierSemanticValue.symbolTableEntry;
        for(int i = 15; i < 35; i++){ // s reg
            if(reg[i].kind == ID && reg[i].entry = entry && reg[i].shift == shift)
                return i;
        }
        return -1;
    }
    //TODO
    return -1;
}
int useReg(AST_NODE *node, int shift, int readWrite){ //read:0 write:1
    assert(node->nodeType == IDENTIFIER_NODE || node->nodeType == CONST_VALUE_NODE);
    SymbolTableEntry *entry = NULL;
    if(node->nodeType == IDENTIFIER_NODE){
        entry = node->semantic_value.identifierSemanticValue.symbolTableEntry;
        assert(entry != NULL);
        int reg_num;
        if((reg_num = CheckInRegister(node, shift)) == -1){ //not load into reg yet
            DATA_TYPE dataType;
            if(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR){
                dataType = entry->attribute->attr.typeDescriptor->properties.dataType;
            }
            else{
                dataType = entry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
            }
            int temp_reg_num = getTempReg(INT_TYPE);
            int ret_reg;
            if(entry->global){
                fprintf(fp, "\tla %s, _g_%s\n", reg[temp_reg_num].name, entry->name);
                if(shift != 0){
                    int temp_reg_num2 = getTempReg(INT_TYPE);
                    fprintf(fp, "\tli %s %d\n", reg[temp_reg_num2].name, shift*4);
                    fprintf(fp, "\tadd %s %s %s\n", reg[temp_reg_num].name, reg[temp_reg_num].name, reg[temp_reg_num2].name);
                    freeReg(temp_reg_num2);
                }
                if(dataType == INT_TYPE){
                    ret_reg = getTempReg(INT_TYPE);
                    fprintf(fp, "\tlw %s, 0(%s)\n", reg[ret_reg].name, reg[temp_reg_num].name);
                }
                else if(dataType == FLOAT_TYPE){
                    ret_reg = getTempReg(FLOAT_TYPE);
                    fprintf(fp, "\tflw %s, 0(%s)\n", reg[ret_reg].name, reg[temp_reg_num].name);
                }
                else ERR_EXIT("Error in useReg1\n");
            }
            else{
                fprintf(fp, "\tli %s %d\n", reg[temp_reg_num].name, entry->offset);
                fprintf(fp, "\tadd %s %s fp\n", reg[temp_reg_num].name, reg[temp_reg_num].name);
                if(shift != 0){
                    int temp_reg_num2 = getTempReg(INT_TYPE);
                    fprintf(fp, "\tli %s %d\n", reg[temp_reg_num2].name, shift*4);
                    fprintf(fp, "\tadd %s %s %s\n", reg[temp_reg_num].name, reg[temp_reg_num].name, reg[temp_reg_num2].name);
                    freeReg(temp_reg_num2);
                }
                if(dataType == INT_TYPE){
                    ret_reg = getTempReg(INT_TYPE);
                    fprintf(fp, "\tlw %s, 0(%s)\n", reg[ret_reg].name, reg[temp_reg_num].name);
                }
                else if(dataType == FLOAT_TYPE){
                    ret_reg = getTempReg(FLOAT_TYPE);
                    fprintf(fp, "\tflw %s, 0(%s)\n", reg[ret_reg].name, reg[temp_reg_num].name);
                }
                else ERR_EXIT("Error in useReg2\n");
            }
            freeReg(temp_reg_num);
            reg[ret_reg].entry = entry;
            if(readWrite == 1){
                reg[ret_reg].dirty = 2;
            }
            else{
                reg[ret_reg].dirty = (reg[ret_reg].dirty == 2)? 2:1;
            }
            return ret_reg;
        }
        else{
            if(readWrite == 1){
                reg[reg_num].dirty = 2;
            }
            else{
                reg[reg_num].dirty = (reg[reg_num].dirty == 2)? 2:1;
            }
            return reg_num;
        }
    }
    //TODO: const node
}

char* getRegName(AST_NODE* Node){
	if(Node->dataType == INT_TYPE || Node->dataType == CONST_STRING_TYPE){
		return int_reg[Node->place];
	}
	else{
		return float_reg[Node->place];
	}
}
int getReg(DATA_TYPE type){
	int ret;
	if(type == INT_TYPE || type == CONST_STRING_TYPE){
		ret = int_ptr;
		while(used_int[ret]){
			int_ptr = (int_ptr + 1) % INT_REG_NUM;
			ret = int_ptr;
		}
		int_ptr = (int_ptr + 1) % INT_REG_NUM;
	}
	else{
		ret = float_ptr;
		while (used_float[ret])
		{
			float_ptr = (float_ptr + 1) % FLOAT_REG_NUM;
			ret = float_ptr;
		}
		float_ptr = (float_ptr + 1) % FLOAT_REG_NUM;
	}
	return ret;
}
void freeReg(int reg, DATA_TYPE type){
	if(type == INT_TYPE){
		used_int[reg] = 0;
	}
	else{
		used_float[reg] = 0;
	}
	return;
}
void InitReg(){
    for(int i = 0; i < REGNUM; i++){
        strcpy(reg[i].name, reg_name[i]);
        reg[i].dirty = 0;
        reg[i].kind = NOTUSED;
        reg[i].entry = NULL;
        reg[i].shift = 0;
        reg[i].const_val = -1;
    }
}