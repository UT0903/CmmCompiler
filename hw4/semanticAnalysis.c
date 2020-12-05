#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "header.h"
#include "symbolTable.h"
// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 document. //
int g_anyErrorOccur = 0;

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void processProgramNode(AST_NODE *programNode);
void processDeclarationNode(AST_NODE* declarationNode);
void declareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
void declareFunction(AST_NODE* declarationNode);
void processDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
void processTypeNode(AST_NODE* typeNode);
void processBlockNode(AST_NODE* blockNode);
void processStmtNode(AST_NODE* stmtNode);
void processGeneralNode(AST_NODE *node);
void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode);
void checkWhileStmt(AST_NODE* whileNode);
void checkForStmt(AST_NODE* forNode);
void checkAssignmentStmt(AST_NODE* assignmentNode);
void checkIfStmt(AST_NODE* ifNode);
void checkWriteFunction(AST_NODE* functionCallNode);
void checkFunctionCall(AST_NODE* functionCallNode);
void processExprRelatedNode(AST_NODE* exprRelatedNode);
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter);
void processExprNode(AST_NODE* exprNode);
void processVariableLValue(AST_NODE* idNode);
void processVariableRValue(AST_NODE* idNode);
void processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue);
void evaluateExprValue(AST_NODE* exprNode);


Parameter* makeParameter(AST_NODE* paramNode);
TypeDescriptor* makeTypeDescriptor(AST_NODE* ID, DATA_TYPE elementType);
int ConstantFolding(AST_NODE* dimInfoNode);
DATA_TYPE getDataType(AST_NODE* Node);
void declareVariable(AST_NODE* TypeNode);

typedef enum ErrorMsgKind
{
    SYMBOL_IS_NOT_TYPE,
    SYMBOL_REDECLARE,
    SYMBOL_UNDECLARED,
    NOT_FUNCTION_NAME,
    TRY_TO_INIT_ARRAY,
    EXCESSIVE_ARRAY_DIM_DECLARATION,
    RETURN_ARRAY,
    VOID_VARIABLE,
    TYPEDEF_VOID_ARRAY,
    PARAMETER_TYPE_UNMATCH,
    TOO_FEW_ARGUMENTS,
    TOO_MANY_ARGUMENTS,
    RETURN_TYPE_UNMATCH,
    INCOMPATIBLE_ARRAY_DIMENSION,
    NOT_ASSIGNABLE,
    NOT_ARRAY,
    IS_TYPE_NOT_VARIABLE,
    IS_FUNCTION_NOT_VARIABLE,
    STRING_OPERATION,
    ARRAY_SIZE_NOT_INT,
    ARRAY_SIZE_NEGATIVE,
    ARRAY_SUBSCRIPT_NOT_INT,
    PASS_ARRAY_TO_SCALAR,
    PASS_SCALAR_TO_ARRAY
} ErrorMsgKind;

void printErrorMsgSpecial(AST_NODE* node1, char* name2, ErrorMsgKind errorMsgKind){
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node1->linenumber);
    /*
    switch(errorMsgKind)
    {
    default:
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
    */
}


void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node->linenumber);
    /*
    switch(errorMsgKind)
    {
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
    */
}


void semanticAnalysis(AST_NODE *root)
{
    processProgramNode(root);
}


DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2){
    if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE) {
        return FLOAT_TYPE;
    } else {
        return INT_TYPE;
    }
}


void processProgramNode(AST_NODE *programNode)
{
    processDeclarationNode(programNode->child->child);
}

void processDeclarationNode(AST_NODE* declarationNode){
    if(declarationNode->nodeType != DECLARATION_NODE){
        fprintf(stderr, "Should not pass non-DECLARATION_NODE into processDeclarationNode()\n");
        exit(0);
    }
    DECL_KIND declKind =  declarationNode->semantic_value.declSemanticValue.kind;
    if(declKind == VARIABLE_DECL){
        declareVariable(declarationNode->child);
    }
    else if(declKind == TYPE_DECL){
        fprintf(stderr, "TODO\n");
        exit(0);
    }
    else if(declKind == FUNCTION_DECL){
        declareFunction(declarationNode->child);
    }
    else if(declKind == FUNCTION_PARAMETER_DECL){
        fprintf(stderr, "Should be finish in declareFunction()\n");
        exit(0);
    }
    else{
        fprintf(stderr, "Error in processDeclarationNode\n");
        exit(0);
    }
}


void processTypeNode(AST_NODE* idNodeAsType)
{
}


void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
}

void checkWhileStmt(AST_NODE* whileNode)
{
}


void checkForStmt(AST_NODE* forNode)
{
}


void checkAssignmentStmt(AST_NODE* assignmentNode)
{
}


void checkIfStmt(AST_NODE* ifNode)
{
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
}

void checkFunctionCall(AST_NODE* functionCallNode)
{
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
}


void processExprRelatedNode(AST_NODE* exprRelatedNode)
{
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue)
{
}

void evaluateExprValue(AST_NODE* exprNode)
{
}


void processExprNode(AST_NODE* exprNode)
{
}

void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize){

}
void processVariableLValue(AST_NODE* idNode)
{
}

void processVariableRValue(AST_NODE* idNode)
{
}


void processConstValueNode(AST_NODE* constValueNode)
{
}


void processBlockNode(AST_NODE* blockNode)
{
}


void processStmtNode(AST_NODE* stmtNode)
{
}


void processGeneralNode(AST_NODE *node)
{
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
}

void declareVariable(AST_NODE* TypeNode){
    DATA_TYPE dataType = getDataType(TypeNode);
    AST_NODE* IDNode = TypeNode->rightSibling;
    while(IDNode != NULL){
        char *varName = IDNode->semantic_value.identifierSemanticValue.identifierName;
        //check variable 有沒有被declare過
        if(declaredInThisScope(varName, getCurrentScope()) != NULL){
            fprintf(stderr, "redeclaration of Variable name\n");
            exit(0);
        }
        //fill Symbol table in this scope
        SymbolAttribute *ScopeAttr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
        ScopeAttr->attributeKind = VARIABLE_ATTRIBUTE;
        ScopeAttr->attr.typeDescriptor = makeTypeDescriptor(IDNode, dataType);
        if(!enterSymbol(varName, ScopeAttr, getCurrentScope())){
            fprintf(stderr, "Error in declareVariable\n");
            exit(0);
        }
        IDNode = IDNode->rightSibling;
    }
}
void declareFunction(AST_NODE* returnTypeNode){
    openScope();
    //new func attr
    SymbolAttribute *funcAttr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
    funcAttr->attributeKind = FUNCTION_SIGNATURE;
    funcAttr->attr.functionSignature = (FunctionSignature*)malloc(sizeof(FunctionSignature));
    funcAttr->attr.functionSignature->parameterList = NULL;

    FunctionSignature* funcSign = funcAttr->attr.functionSignature;
    funcSign->returnType = getDataType(returnTypeNode); //check for return type
    AST_NODE* funcNameNode = returnTypeNode->rightSibling;
    char *funcName = funcNameNode->semantic_value.identifierSemanticValue.identifierName;
    //check function 有沒有被declare過
    if(declaredInThisScope(funcName, 0) != NULL){
        fprintf(stderr, "redeclaration of function name\n");
        exit(0);
    }
    AST_NODE* paramListNode = funcNameNode->rightSibling;
    // collect params attr
    AST_NODE* paramNode = paramListNode->child;
    while(paramNode != NULL){
        Parameter* paramStruct = makeParameter(paramNode->child);
        funcSign->parametersCount++;
        paramStruct->next = funcSign->parameterList;
        funcSign->parameterList = paramStruct;
        paramNode = paramNode->rightSibling;
    }
    //TODO: deal with block node
    processBlockNode(paramListNode->rightSibling);
    if(!enterSymbol(funcName, funcAttr, 0)){
        fprintf(stderr, "Error in declareFunction\n");
        exit(0);
    }


    //TODO: check return type is equal or not 
    closeScope();
}
DATA_TYPE getDataType(AST_NODE* Node){
    if(Node->nodeType != IDENTIFIER_NODE){
        fprintf(stderr, "Should not pass node which is not IDENTIFIER_NODE into getDataType function\n");
        exit(0);
    }
    char *type = Node->semantic_value.identifierSemanticValue.identifierName;
    if(strcmp(type, "int") == 0) return INT_TYPE;
    else if(strcmp(type, "float") == 0) return FLOAT_TYPE;
    else if(strcmp(type, "void") == 0) return VOID_TYPE;
    else{
        //deal with typedef condition
        SymbolTableEntry* entry;
        if((entry = retrieveSymbol(type)) != NULL){
            if(entry->attribute->attributeKind == TYPE_ATTRIBUTE){
                TypeDescriptor *type = entry->attribute->attr.typeDescriptor;
                if(type->kind == SCALAR_TYPE_DESCRIPTOR){
                    return type->properties.dataType;
                }   
            }
        }
        fprintf(stderr, "Ilegal type: %s\n", type);
        exit(0); 
    }
}
Parameter* makeParameter(AST_NODE* typeNode){
    AST_NODE* ID = typeNode->rightSibling;

    char *name = ID->semantic_value.identifierSemanticValue.identifierName;
    TypeDescriptor* typeDescStruct = makeTypeDescriptor(ID, getDataType(typeNode));

    //fill Parameter struct
    Parameter *paramStruct = (Parameter*)malloc(sizeof(Parameter));
    paramStruct->parameterName = name;
    paramStruct->type = typeDescStruct;

    //fill Symbol table in this scope
    SymbolAttribute *ScopeAttr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
    ScopeAttr->attributeKind = VARIABLE_ATTRIBUTE;
    ScopeAttr->attr.typeDescriptor = typeDescStruct;
    if(declaredInThisScope(name, getCurrentScope()) != NULL){
        fprintf(stderr, "redeclaration of symbol");
        exit(0);
    }
    if(!enterSymbol(name, ScopeAttr, getCurrentScope())){
        fprintf(stderr, "Error in makeParameter\n");
        exit(0);
    }
    return paramStruct;
}

TypeDescriptor* makeTypeDescriptor(AST_NODE* ID, DATA_TYPE elementType){
    if(elementType != INT_TYPE && elementType != FLOAT_TYPE){
        fprintf(stderr, "not int or float type\n");
        exit(0);
    }
    TypeDescriptor* typeDescStruct = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));
    if(ID->semantic_value.identifierSemanticValue.kind == NORMAL_ID){
        typeDescStruct->kind = SCALAR_TYPE_DESCRIPTOR;
        typeDescStruct->properties.dataType = elementType;
    }
    else if(ID->semantic_value.identifierSemanticValue.kind == ARRAY_ID){
        typeDescStruct->kind = ARRAY_TYPE_DESCRIPTOR;
        
        AST_NODE *dimInfo = ID->child;
        while(dimInfo != NULL){
            //TODO: do constant folding
            int res = ConstantFolding(dimInfo);
            typeDescStruct->properties.arrayProperties.sizeInEachDimension[typeDescStruct->properties.arrayProperties.dimension++] \
                = res;
            dimInfo = dimInfo->rightSibling;
        }
        typeDescStruct->properties.arrayProperties.elementType = elementType;
    }
    else{
        fprintf(stderr, "Error in makeTypeDescriptor\n");
        exit(0);
    }
    return typeDescStruct;
}

int ConstantFolding(AST_NODE* dimInfoNode){
    //TODO
    return 1;
}