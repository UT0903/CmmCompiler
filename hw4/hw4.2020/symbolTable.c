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

SymbolTable symbolTable;

SymbolTableEntry* newSymbolTableEntry(int nestingLevel)
{
    SymbolTableEntry* symbolTableEntry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    symbolTableEntry->nextInHashChain = NULL;
    symbolTableEntry->prevInHashChain = NULL;
    symbolTableEntry->nextInSameLevel = NULL;
    symbolTableEntry->sameNameInOuterLevel = NULL;
    symbolTableEntry->attribute = NULL;
    symbolTableEntry->name = NULL;
    symbolTableEntry->nestingLevel = nestingLevel;
    return symbolTableEntry;
}

void removeFromHashTrain(int hashIndex, SymbolTableEntry* entry){
    if(entry->prevInHashChain == NULL)
        symbolTable.hashTable[hashIndex] = entry->nextInHashChain;
    else
        entry->nextInHashChain->prevInHashChain = entry->nextInHashChain;
    if(entry->nextInHashChain == NULL)
        entry->prevInHashChain->nextInHashChain = ;


    free(entry);
}

void enterIntoHashTrain(int hashIndex, SymbolTableEntry* entry)
{

}

void initializeSymbolTable()
{   
    /*symbolTable.currentLevel = 0;
    symbolTable.scopeDisplayElementCount = ; // WTF is this?
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        symbolTable.hashTable[i] = NULL;
        symbolTable.scopeDisplay[i] = NULL;
    }*/
}

void symbolTableEnd()
{
}

SymbolTableEntry* retrieveSymbol(char* symbolName)
{
}

SymbolTableEntry* enterSymbol(char* symbolName, SymbolAttribute* attribute)
{
}

//remove the symbol from the current scope
void removeSymbol(char* symbolName)
{
}

int declaredLocally(char* symbolName)
{
}

void openScope()
{
}

void closeScope()
{
}
