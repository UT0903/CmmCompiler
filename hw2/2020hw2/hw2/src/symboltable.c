#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"header.h"

#define TABLE_SIZE	512

symtab * hash_table[TABLE_SIZE];
extern int linenumber;

int HASH(char * str){
	int idx=0;
	while(*str){
		idx = idx << 1;
		idx+=*str;
		str++;
	}	
	return (idx & (TABLE_SIZE-1));
}

/*returns the symbol table entry if found else NULL*/

symtab * lookup(char *name){
	int hash_key;
	symtab* symptr;
	if(!name)
		return NULL;
	hash_key=HASH(name);
	symptr=hash_table[hash_key];

	while(symptr){
		if(!(strcmp(name,symptr->lexeme)))
			return symptr;
		symptr=symptr->front;
	}
	return NULL;
}


void insertID(char *name, int isReserve){
	int hash_key;
	symtab* ptr;
	symtab* symptr=(symtab*)malloc(sizeof(symtab));	
	
	hash_key=HASH(name);
	ptr=hash_table[hash_key];
	
	if(ptr==NULL){
		/*first entry for this hash_key*/
		hash_table[hash_key]=symptr;
		symptr->front=NULL;
		symptr->back=symptr;
	}
	else{
		symptr->front=ptr;
		ptr->back=symptr;
		symptr->back=symptr;
		hash_table[hash_key]=symptr;	
	}
	
	strcpy(symptr->lexeme,name);
	symptr->line=linenumber;
	symptr->counter=1;
	if(isReserve)
		symptr->type = Reserve;
	else
		symptr->type = NReserve;
}

typedef struct{
	char lex[35];
	int cnt;
}WORD;
void printSym(WORD word) {
		printf("%s %d\n", word.lex, word.cnt);
}

int cmp(const void *pa, const void *pb){
	WORD *a = (WORD *)pa;
	WORD *b = (WORD *)pb;
	return strcmp(a->lex, b->lex);
}
WORD word[1000000];
void printSymTab()
{
    int i, now = 0;
    
    // printf("----- Symbol Table ---------\n");
    for (i=0; i<TABLE_SIZE; i++)
    {
        symtab* symptr;
		symptr = hash_table[i];
		while (symptr != NULL)
		{
			//printf("====>  index = %d \n", i);
			if(symptr->type == NReserve){
				strcpy(word[now].lex, symptr->lexeme);
				word[now ++].cnt = symptr->counter;
			}
			symptr=symptr->front;
		}
    }
    //printf("OK\n");
    qsort(word, now, sizeof(WORD), cmp);
    for(int i = 0; i < now; i++){
    	printSym(word[i]);
    }
}
