#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

SymbolTableStack *stackEntry;

SymbolTableEntry* newSymbolTableEntry(char* symbolName, SymbolAttribute* attribute){
    SymbolTableEntry* symbolTableEntry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    symbolTableEntry->next = NULL;
    symbolTableEntry->attribute = attribute;
    symbolTableEntry->name = symbolName;
    return symbolTableEntry;
}

void initializeSymbolTableStack(){
    stackEntry = NULL;
}

void openScope(){ //push stack
    //new a stack
    SymbolTableStack* newStack = (SymbolTableStack*)malloc(sizeof(SymbolTableStack));
    //init hashTable
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        newStack->hashTable[i]->next = NULL;
        newStack->hashTable[i]->name = NULL;
        newStack->hashTable[i]->attribute = NULL;
    }
    newStack->prevStack = stackEntry; //construct linklist
    stackEntry = newStack;
}
void closeScope(){ //pop stack
    if(stackEntry == NULL){
        fprintf(stderr, "Stack is null, Can't pop stack\n"); 
        exit(1);
    }
    SymbolTableStack* prevStack = stackEntry->prevStack;
    
    //free hash table
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        SymbolTableEntry* nowEntry = stackEntry->hashTable[i];
        while(nowEntry != NULL){
            SymbolTableEntry* tempEntry = nowEntry;
            nowEntry = nowEntry->next;
            free(tempEntry);
        }
    }
    free(stackEntry);
    stackEntry = prevStack;
}
void symbolTableEnd(){}

SymbolTableEntry* retrieveSymbol(char* symbolName){
    SymbolTableStack *nowStackEntry = stackEntry;
    while(nowStackEntry != NULL){
        SymbolTableEntry* targetEntry;
        if((targetEntry = declaredInThisScope(symbolName, nowStackEntry)) != NULL){
            return targetEntry;
        }
        nowStackEntry = nowStackEntry->prevStack;
    }
    fprintf(stderr, "Can't not find symbolName: %s\n", symbolName); 
    return NULL;
}

int enterSymbol(char* symbolName, SymbolAttribute* attribute){
    if(declaredInThisScope(symbolName, NULL) != NULL){
        fprintf(stderr, "Redeclearation of symbolName: [ %s ]\n", symbolName); 
        return 0;
    }
    //insert
    SymbolTableEntry* newSymbol = newSymbolTableEntry(symbolName, attribute);
    newSymbol->next = stackEntry->hashTable[HASH(symbolName)]->next;
    stackEntry->hashTable[HASH(symbolName)] = newSymbol;
    return 1;
}

//remove the symbol from the current scope
int removeSymbol(char* symbolName){
    SymbolTableEntry* nowEntry = stackEntry->hashTable[HASH(symbolName)];
    SymbolTableEntry* prevEntry = NULL;
    while(nowEntry != NULL){
        if(strcmp(nowEntry->name, symbolName) == 0){
            if(prevEntry == NULL){
                stackEntry->hashTable[HASH(symbolName)] = nowEntry->next;
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
    fprintf(stderr, "No symbolName: [ %s ] in this scope\n", symbolName); 
    return 0;
}

SymbolTableEntry* declaredInThisScope(char* symbolName, SymbolTableStack *nowStackEntry){
    if(stackEntry == NULL){
        fprintf(stderr, "Stack is null\n");
        return NULL;
    }
    if(nowStackEntry == NULL) nowStackEntry = stackEntry;
    SymbolTableEntry* nowEntry = nowStackEntry->hashTable[HASH(symbolName)];
    while(nowEntry != NULL){
        if(strcmp(nowEntry->name, symbolName) == 0) return nowEntry;
        nowEntry = nowEntry->next;
    }
    return NULL;
}

