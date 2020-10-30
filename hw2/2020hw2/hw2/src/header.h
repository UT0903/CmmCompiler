enum symType {
	NReserve,
	Reserve,
};

struct symtab{
	char lexeme[32];
	struct symtab *front;
	struct symtab *back;
	int line;
	int counter;
	enum symType type;
};
typedef struct symtab symtab;
symtab * lookup(char *name);
void insert(char *name);
