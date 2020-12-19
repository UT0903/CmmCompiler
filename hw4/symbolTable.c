#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

// This file is for reference only, you are not required to follow the implementation. //

int HASH(char * str) {
	int idx=0;
	while (*str){
		idx = idx << 1;
		idx+=*str;
		str++;
	}
	return (idx & (HASH_TABLE_SIZE-1));
}

SymbolTableStack *TopStackEntry, *BottomStackEntry;

SymbolTableEntry* newSymbolTableEntry(char* symbolName, SymbolAttribute* attribute){
    SymbolTableEntry* symbolTableEntry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    symbolTableEntry->next = NULL;
    symbolTableEntry->attribute = attribute;
    symbolTableEntry->name = symbolName;
    return symbolTableEntry;
}

SymbolTableStack* newSymbolTableStackEntry(){
    SymbolTableStack* newStack = (SymbolTableStack*)malloc(sizeof(SymbolTableStack));
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        newStack->hashTable[i] = NULL;
    }
    newStack->prevStack = NULL;
    newStack->currentScope = -1;
    return newStack;
}

void initializeSymbolTable(){
    SymbolTableStack* newStack = newSymbolTableStackEntry();
    newStack->prevStack = NULL; //construct linklist
    newStack->currentScope = 0;
    TopStackEntry = newStack;
    BottomStackEntry = newStack;
}

void openScope(){ //push stack
    SymbolTableStack* newStack = newSymbolTableStackEntry();
    newStack->prevStack = TopStackEntry; //construct linklist
    newStack->currentScope = newStack->prevStack->currentScope + 1;
    TopStackEntry = newStack;
}
void closeScope(){ //pop stack
    if(TopStackEntry == BottomStackEntry){
        fprintf(stderr, "Scope is 0, Can't pop stack\n"); 
        exit(1);
    }
    SymbolTableStack* prevStack = TopStackEntry->prevStack;
    
    //free hash table
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        SymbolTableEntry* nowEntry = TopStackEntry->hashTable[i];
        while(nowEntry != NULL){
            SymbolTableEntry* tempEntry = nowEntry;
            nowEntry = nowEntry->next;
            free(tempEntry);
        }
    }
    free(TopStackEntry);
    TopStackEntry = prevStack;
}
void symbolTableEnd(){}

SymbolTableStack* getStackEntry(int scope){
    SymbolTableStack *nowStackEntry = TopStackEntry;
    while(nowStackEntry != NULL){
        if(nowStackEntry->currentScope == scope){
            return nowStackEntry;
        }
        nowStackEntry = nowStackEntry->prevStack;
    }
    return NULL;
}
SymbolTableEntry* retrieveSymbol(char* symbolName){
    SymbolTableStack *nowStackEntry = TopStackEntry;
    while(nowStackEntry != NULL){
        SymbolTableEntry* targetEntry;
        if((targetEntry = declaredInThisScope(symbolName, nowStackEntry->currentScope)) != NULL){
            return targetEntry;
        }
        nowStackEntry = nowStackEntry->prevStack;
    }
    //fprintf(stderr, "Can't not find symbolName: %s\n", symbolName); 
    return NULL;
}

int enterSymbol(char* symbolName, SymbolAttribute* attribute, int scope){
    SymbolTableStack *nowStackEntry = getStackEntry(scope);
    if(nowStackEntry == NULL){
        //fprintf(stderr, "Can't find stack entry\n");
        return 0;
    }
    if(declaredInThisScope(symbolName, scope) != NULL){
        //fprintf(stderr, "Redeclearation of symbolName: [ %s ]\n", symbolName); 
        return 0;
    }
    //insert
    SymbolTableEntry* newSymbol = newSymbolTableEntry(symbolName, attribute);
    newSymbol->next = nowStackEntry->hashTable[HASH(symbolName)];
    nowStackEntry->hashTable[HASH(symbolName)] = newSymbol;
    return 1;
}

//remove the symbol from the certain scope
int removeSymbol(char* symbolName, int scope){
    SymbolTableStack *nowStackEntry = getStackEntry(scope);
    if(nowStackEntry == NULL){
        //fprintf(stderr, "Can't find stack entry\n");
        return 0;
    }

    SymbolTableEntry* nowEntry = nowStackEntry->hashTable[HASH(symbolName)];
    SymbolTableEntry* prevEntry = NULL;
    while(nowEntry != NULL){
        if(strcmp(nowEntry->name, symbolName) == 0){
            if(prevEntry == NULL){
                nowStackEntry->hashTable[HASH(symbolName)] = nowEntry->next;
            }
            else{
                prevEntry->next = nowEntry->next;
            }
            free(nowEntry);
            return 1;
        }
        prevEntry = nowEntry;
        nowEntry = nowEntry->next;
    }
    //fprintf(stderr, "No symbolName: [ %s ] in this scope\n", symbolName); 
    return 0;
}

SymbolTableEntry* declaredInThisScope(char* symbolName, int scope){
    SymbolTableStack *nowStackEntry = getStackEntry(scope);
    if(nowStackEntry == NULL){
        //fprintf(stderr, "Can't find stack entry\n");
        return 0;
    }

    SymbolTableEntry* nowEntry = nowStackEntry->hashTable[HASH(symbolName)];
    while(nowEntry != NULL){
        if(strcmp(nowEntry->name, symbolName) == 0) return nowEntry;
        nowEntry = nowEntry->next;
    }
    return NULL;
}
int getCurrentScope(){
    return TopStackEntry->currentScope;
}

void PrintTypeDescriptor(TypeDescriptor* type){
    if(type->kind == ARRAY_TYPE_DESCRIPTOR){
        if(type->properties.arrayProperties.elementType == INT_TYPE){
            fprintf(stderr, "Int Array with dim: %d (", type->properties.arrayProperties.dimension);
        }
        else if(type->properties.arrayProperties.elementType == FLOAT_TYPE){
            fprintf(stderr, "Float Array with dim: %d (", type->properties.arrayProperties.dimension);
        }
        else{
            fprintf(stderr, "ERROR in printTable, This should not happen1\n");
            exit(0);
        }
        for(int i = 0; i < type->properties.arrayProperties.dimension; i++){
            fprintf(stderr, "%d%s", type->properties.arrayProperties.sizeInEachDimension[i], (i == type->properties.arrayProperties.dimension - 1)? ")\n":", ");
        }
    }
    else if(type->kind == SCALAR_TYPE_DESCRIPTOR){
        if(type->properties.dataType == INT_TYPE){
            fprintf(stderr, "Int\n");
        }
        else if(type->properties.dataType == FLOAT_TYPE){
            fprintf(stderr, "Float\n");
        }
        else if(type->properties.dataType == VOID_TYPE){
            fprintf(stderr, "Void\n");
        }
        else{
            fprintf(stderr, "ERROR in printTable, This should not happen2\n");
            fprintf(stderr, "%d\n", type->properties.dataType);
            exit(0);
        }
    }
    else{
        fprintf(stderr, "ERROR in printTable, This should not happen3\n");
        exit(0);
    }
}
void PrintSymbolTable(){
    SymbolTableStack *nowStackEntry = TopStackEntry;
    while(nowStackEntry != NULL){
        fprintf(stderr, "========================\n");
        fprintf(stderr, "Scope: %d\n", nowStackEntry->currentScope);
        for(int i = 0; i < HASH_TABLE_SIZE; i++){
            SymbolTableEntry* nowEntry = nowStackEntry->hashTable[i];
            while(nowEntry != NULL){
                fprintf(stderr, "----------------\n");
                fprintf(stderr, "Name: %s ", nowEntry->name);
                SymbolAttribute* attr = nowEntry->attribute;
                if(attr->attributeKind == VARIABLE_ATTRIBUTE){
                    fprintf(stderr, "AttrKind: VARIABLE\n");
                    PrintTypeDescriptor(attr->attr.typeDescriptor);
                }
                else if(attr->attributeKind == TYPE_ATTRIBUTE){
                    fprintf(stderr, "AttrKind: TYPEDEF\n");
                    PrintTypeDescriptor(attr->attr.typeDescriptor);   
                }
                else if(attr->attributeKind == FUNCTION_SIGNATURE){
                    fprintf(stderr, "AttrKind: FUNCTION\n");
                    FunctionSignature* func = attr->attr.functionSignature;
                    if(func->returnType == INT_TYPE){
                        fprintf(stderr, "ReturnType: Int\n");
                    }
                    else if(func->returnType == FLOAT_TYPE){
                        fprintf(stderr, "ReturnType: Float\n");
                    }
                    else if(func->returnType == VOID_TYPE){
                        fprintf(stderr, "ReturnType: Void\n");
                    }
                    else{
                        fprintf(stderr, "ERROR in printTable, This should not happen4\n");
                        exit(0);
                    }
                    fprintf(stderr, "Parameter num: %d\n", func->parametersCount);
                    Parameter* param = func->parameterList;
                    while(param != NULL){
                        fprintf(stderr, "%s: ", param->parameterName);
                        PrintTypeDescriptor(param->type);
                        param = param->next;
                    }
                }
                nowEntry = nowEntry->next;
            }
        }
        nowStackEntry = nowStackEntry->prevStack;
    }
    fprintf(stderr, "========================\n\n");
}