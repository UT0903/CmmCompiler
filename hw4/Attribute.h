struct SymbolAttribute
{
    enum SymbolAttributeKind
    {
	    VARIABLE_ATTRIBUTE,
	    TYPE_ATTRIBUTE,
	    FUNCTION_SIGNATURE
	} attributeKind;
    union{
        struct TypeDescriptor
        {
		    enum TypeDescriptorKind
			{
			    SCALAR_TYPE_DESCRIPTOR,
			    ARRAY_TYPE_DESCRIPTOR,
			} kind;

		    union
		    {
		        enum DATA_TYPE
		        {
				    INT_TYPE,
				    FLOAT_TYPE,
				    VOID_TYPE,
				    INT_PTR_TYPE,//for parameter passing
				    FLOAT_PTR_TYPE,//for parameter passing
				    CONST_STRING_TYPE,//for "const string"
				    NONE_TYPE,//for nodes like PROGRAM_NODE which has no type
				    ERROR_TYPE
				} dataType;//kind: SCALAR_TYPE_DESCRIPTOR
		        
		        struct ArrayProperties
		        {
				    int dimension;
				    int sizeInEachDimension[MAX_ARRAY_DIMENSION];
				    //point to a TypeDescriptor in the symbol table;
				    enum DATA_TYPE
				    {
					    INT_TYPE,
					    FLOAT_TYPE,
					    VOID_TYPE,
					    INT_PTR_TYPE,//for parameter passing
					    FLOAT_PTR_TYPE,//for parameter passing
					    CONST_STRING_TYPE,//for "const string"
					    NONE_TYPE,//for nodes like PROGRAM_NODE which has no type
					    ERROR_TYPE
					} elementType;
				} arrayProperties;//kind: ARRAY_TYPE_DESCRIPTOR
		    } properties;
		} *typeDescriptor;

        struct FunctionSignature
        {
		    int parametersCount;
		    struct Parameter
		    {
			    //point to a TypeDescriptor in the symbol table;
			    struct Parameter* next;
			    struct TypeDescriptor
			    {
				    TypeDescriptorKind kind;
				    union
				    {
				        enum DATA_TYPE
				        {
						    INT_TYPE,
						    FLOAT_TYPE,
						    VOID_TYPE,
						    INT_PTR_TYPE,//for parameter passing
						    FLOAT_PTR_TYPE,//for parameter passing
						    CONST_STRING_TYPE,//for "const string"
						    NONE_TYPE,//for nodes like PROGRAM_NODE which has no type
						    ERROR_TYPE
						} dataType;//kind: SCALAR_TYPE_DESCRIPTOR
				        struct ArrayProperties
				        {
						    int dimension;
						    int sizeInEachDimension[MAX_ARRAY_DIMENSION];
						    //point to a TypeDescriptor in the symbol table;
						    enum DATA_TYPE
						    {
							    INT_TYPE,
							    FLOAT_TYPE,
							    VOID_TYPE,
							    INT_PTR_TYPE,//for parameter passing
							    FLOAT_PTR_TYPE,//for parameter passing
							    CONST_STRING_TYPE,//for "const string"
							    NONE_TYPE,//for nodes like PROGRAM_NODE which has no type
							    ERROR_TYPE
							} elementType;
						} arrayProperties;//kind: ARRAY_TYPE_DESCRIPTOR
				    } properties;
				} *type;
			    char* parameterName;
			} *parameterList;
		    enum DATA_TYPE
	        {
			    INT_TYPE,
			    FLOAT_TYPE,
			    VOID_TYPE,
			    INT_PTR_TYPE,//for parameter passing
			    FLOAT_PTR_TYPE,//for parameter passing
			    CONST_STRING_TYPE,//for "const string"
			    NONE_TYPE,//for nodes like PROGRAM_NODE which has no type
			    ERROR_TYPE
			} returnType;
		} *functionSignature;
    } attr;
}