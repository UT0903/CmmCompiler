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
TypeDescriptor* extendTypeDescriptor(AST_NODE* ID, TypeDescriptor* elementType);
AST_NODE* ConstantFolding(AST_NODE* ExprNode);
TypeDescriptor* getTypeDescriptor(AST_NODE* IDNode);
void declareVariable(AST_NODE* TypeNode);
void FillInSymbolTable(char *name, TypeDescriptor* typeDescStruct, SymbolAttributeKind attrKind);
void declareTypedef(AST_NODE* TypeNode);
float handleBinaryFloatFolding(float a, float b, BINARY_OPERATOR op);
float handleUnaryFloatFolding(float a, UNARY_OPERATOR op);
int handleUnaryIntFolding(int a, UNARY_OPERATOR op);
int handleBinaryIntFolding(int a, int b, BINARY_OPERATOR op);


typedef enum ErrorMsgKind
{
    NOT_DECLARED_IN_THIS_SCOPE, // ‘<name>’ was not declared in this scope
    REDECLARATION, //redeclaration of ‘<type> <name>’
    TOO_FEW_ARGUMENTS_TO_FUNCTION, //too few arguments to function ‘<function signature>’
    TOO_MANY_ARGUMENTS_TO_FUNCTION,  //too many arguments to function ‘<function signature>’
    //subscripted value is neither array nor pointer nor vector
} ErrorMsgKind;

void printErrorMsg(AST_NODE* node1, char* name2, ErrorMsgKind errorMsgKind){
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node1->linenumber);
    
    /*switch(errorMsgKind){
    case(NOT_DECLARED_IN_THIS_SCOPE):
        printf("%s was not declared in this scope\n",  node1->semantic_value.identifierSemanticValue.identifierName);
        break;
    case(REDECLARATION):
        printf("redeclaration of ‘%s %s’\n", , node1->semantic_value.identifierSemanticValue.identifierName);
        break;
    case(TOO_FEW_ARGUMENTS_TO_FUNCTION):
        printf("too few arguments to function ‘%s’\n", );
        break;
    case(TOO_FEW_ARGUMENTS_TO_FUNCTION):
        break;
    default:
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }*/
    
    exit(0);
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
    AST_NODE *declaNode = programNode->child;
    while(declaNode != NULL){
        if(declaNode->nodeType == VARIABLE_DECL_LIST_NODE){ //variable declaration
            AST_NODE *varDeclNode = declaNode->child;
            while(varDeclNode != NULL){
                processDeclarationNode(varDeclNode);
                varDeclNode = varDeclNode->rightSibling;
            }
        }
        else if(declaNode->nodeType == DECLARATION_NODE){ //function declaration
            processDeclarationNode(declaNode);
        }
        declaNode = declaNode->rightSibling;
    }
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
        declareTypedef(declarationNode->child);
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
void declareTypedef(AST_NODE* TypeNode){
    AST_NODE* IDNode = TypeNode->rightSibling;
    while(IDNode != NULL){
        char *varName = IDNode->semantic_value.identifierSemanticValue.identifierName;
        TypeDescriptor* typeDescStruct = extendTypeDescriptor(IDNode, getTypeDescriptor(TypeNode));
        FillInSymbolTable(varName, typeDescStruct, TYPE_ATTRIBUTE);
        IDNode = IDNode->rightSibling;
    }
}
void declareVariable(AST_NODE* TypeNode){
    AST_NODE* IDNode = TypeNode->rightSibling;
    while(IDNode != NULL){
        char *varName = IDNode->semantic_value.identifierSemanticValue.identifierName;
        TypeDescriptor* typeDescStruct = extendTypeDescriptor(IDNode, getTypeDescriptor(TypeNode));
        FillInSymbolTable(varName, typeDescStruct, VARIABLE_ATTRIBUTE);
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
    funcSign->parametersCount = 0;
    
    TypeDescriptor* typeDescStruct = getTypeDescriptor(returnTypeNode); //check for return type
    if(typeDescStruct->kind != SCALAR_TYPE_DESCRIPTOR){
        fprintf(stderr, "Return type error\n");
        exit(0);
    }
    funcSign->returnType = typeDescStruct->properties.dataType;
    free(typeDescStruct);

    AST_NODE* funcNameNode = returnTypeNode->rightSibling;
    char *funcName = funcNameNode->semantic_value.identifierSemanticValue.identifierName;
    //check function 有沒有被declare過
    if(declaredInThisScope(funcName, 0) != NULL){
        fprintf(stderr, "redeclaration of function name\n");
        exit(0);
    }
    AST_NODE* paramListNode = funcNameNode->rightSibling;
    AST_NODE* paramNode = paramListNode->child; // collect params attr
    while(paramNode != NULL){
        Parameter* paramStruct = makeParameter(paramNode->child);
        funcSign->parametersCount++;
        paramStruct->next = funcSign->parameterList;
        funcSign->parameterList = paramStruct;
        paramNode = paramNode->rightSibling;
    }
    //TODO: deal with block node
    processBlockNode(paramListNode->rightSibling); //TODO: check return type is equal or not 
    if(!enterSymbol(funcName, funcAttr, 0)){
        fprintf(stderr, "Error in declareFunction\n");
        exit(0);
    }
    PrintSymbolTable();
    closeScope();
}
TypeDescriptor* getTypeDescriptor(AST_NODE* IDNode){ //get DATA_TYPE from ID Node
    if(IDNode->nodeType != IDENTIFIER_NODE){
        fprintf(stderr, "Should not pass node which is not IDENTIFIER_NODE into getTypeDescriptor function\n");
        exit(0);
    }
    TypeDescriptor* typeDescStruct = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));
    char *type = IDNode->semantic_value.identifierSemanticValue.identifierName;
    if(strcmp(type, "int") == 0 || strcmp(type, "float") == 0 || strcmp(type, "void") == 0){
        typeDescStruct->kind = SCALAR_TYPE_DESCRIPTOR;
        if(strcmp(type, "int") == 0) typeDescStruct->properties.dataType = INT_TYPE;
        else if(strcmp(type, "float") == 0) typeDescStruct->properties.dataType = FLOAT_TYPE;
        else if(strcmp(type, "void") == 0) typeDescStruct->properties.dataType = VOID_TYPE;
        else{
            fprintf(stderr, "Error in getTypeDescriptor()\n");
            exit(0);
        }
        return typeDescStruct;
    }
    else{ //deal with typedef condition
        SymbolTableEntry* entry;
        if((entry = retrieveSymbol(type)) != NULL){
            if(entry->attribute->attributeKind == TYPE_ATTRIBUTE){
                memcpy(typeDescStruct, entry->attribute->attr.typeDescriptor, sizeof(TypeDescriptor));
                return typeDescStruct;
            }
        }
        fprintf(stderr, "Ilegal type: %s\n", type);
        exit(0); 
    }
}
void FillInSymbolTable(char *name, TypeDescriptor* typeDescStruct, SymbolAttributeKind attrKind){ //fill Var in Symbol table
    //fprintf(stderr, "Insert: %s dataType: %d scope: %d\n", name, typeDescStruct->properties.dataType, getCurrentScope());
    if(attrKind != VARIABLE_ATTRIBUTE && attrKind != TYPE_ATTRIBUTE){
        fprintf(stderr, "FillInSymbolTable() Only support for VARIABLE_ATTRIBUTE and TYPE_ATTRIBUTE\n");
        exit(0);
    }
    SymbolAttribute *attr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
    attr->attributeKind = attrKind;
    attr->attr.typeDescriptor = typeDescStruct;
    if(declaredInThisScope(name, getCurrentScope()) != NULL){
        fprintf(stderr, "Redeclaration of symbol name: %s\n", name);
        exit(0);
    }
    if(!enterSymbol(name, attr, getCurrentScope())){
        fprintf(stderr, "Error in FillInSymbolTable\n");
        exit(0);
    }
}
Parameter* makeParameter(AST_NODE* typeNode){
    AST_NODE* ID = typeNode->rightSibling;

    char *name = ID->semantic_value.identifierSemanticValue.identifierName;
    TypeDescriptor* typeDescStruct = extendTypeDescriptor(ID, getTypeDescriptor(typeNode));

    //fill Parameter struct
    Parameter *paramStruct = (Parameter*)malloc(sizeof(Parameter));
    paramStruct->parameterName = name;
    paramStruct->type = typeDescStruct;

    FillInSymbolTable(name, typeDescStruct, VARIABLE_ATTRIBUTE);
    return paramStruct;
}

TypeDescriptor* extendTypeDescriptor(AST_NODE* ID, TypeDescriptor* typeDescStruct){
    if(ID->semantic_value.identifierSemanticValue.kind == NORMAL_ID){} //No need to change
    else if(ID->semantic_value.identifierSemanticValue.kind == ARRAY_ID){
        DATA_TYPE newDataType;
        if(typeDescStruct->kind == SCALAR_TYPE_DESCRIPTOR){
            //fprintf(stderr, "Extend SCALAR_TYPE to ARRAY_TYPE\n");
            newDataType = typeDescStruct->properties.dataType;
            typeDescStruct->properties.arrayProperties.dimension = 0;
        }
        else if(typeDescStruct->kind == ARRAY_TYPE_DESCRIPTOR){
            newDataType = typeDescStruct->properties.arrayProperties.elementType;
        }
        else{
            fprintf(stderr, "Error in extendTypeDescriptor1\n");
            exit(0);
        }
        AST_NODE *dimInfo = ID->child;
        while(dimInfo != NULL){ //TODO: typeDescStruct from SCALAR to ARRAY type
            //TODO: do constant folding
            AST_NODE* exprNode = ConstantFolding(dimInfo);
            assert(exprNode != NULL);
            if(exprNode->semantic_value.exprSemanticValue.isConstEval != 1){
                fprintf(stderr, "Cannot have non-int in array dimension declaration\n");
                exit(0);
            }
            typeDescStruct->properties.arrayProperties.sizeInEachDimension[typeDescStruct->properties.arrayProperties.dimension++] \
                = exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue;
            dimInfo = dimInfo->rightSibling;
        }
        typeDescStruct->properties.arrayProperties.elementType = newDataType;
        typeDescStruct->kind = ARRAY_TYPE_DESCRIPTOR;
    }
    else if(ID->semantic_value.identifierSemanticValue.kind == WITH_INIT_ID){
        //TODO:type check for init value
        if(typeDescStruct->kind != SCALAR_TYPE_DESCRIPTOR){
            fprintf(stderr, "Does not support for Initializing Array\n");
            exit(0);
        }
        AST_NODE* exprNode = ConstantFolding(ID->child);
        assert(exprNode != NULL);
        if(exprNode->semantic_value.exprSemanticValue.isConstEval == 0){
            fprintf(stderr, "Not support for dynamic declaration in global\n");
            exit(0);
        }
        else if(exprNode->semantic_value.exprSemanticValue.isConstEval == 2 && typeDescStruct->properties.dataType == INT_TYPE){
            fprintf(stderr, "Cannot assign float to int\n");
            exit(0);
        }
    }
    else{
        fprintf(stderr, "Error in extendTypeDescriptor2\n");
        //fprintf(stderr, "kind: %d\n", ID->semantic_value.identifierSemanticValue.kind);
        exit(0);
    }
    return typeDescStruct;
}

AST_NODE* ConstantFolding(AST_NODE* Node){
    if(Node->nodeType != EXPR_NODE)
        return NULL;
    EXPRSemanticValue *expr = &Node->semantic_value.exprSemanticValue;    
    if(expr->kind == BINARY_OPERATION){
        AST_NODE *l = Node->child, *r = Node->child->rightSibling;
        if(r->nodeType == CONST_VALUE_NODE && l->rightSibling->nodeType == CONST_VALUE_NODE){
            CON_Type *c1 = r->semantic_value.const1, *c2 = l->semantic_value.const1;
            if(c1->const_type == INTEGERC && c2->const_type == INTEGERC){
                expr->isConstEval = 1;
                expr->constEvalValue.iValue = handleBinaryIntFolding(c1->const_u.intval, c2->const_u.intval, expr->op.binaryOp);
            }
            else if(c1->const_type == FLOATC && c2->const_type == FLOATC){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding(c1->const_u.fval, c2->const_u.fval, expr->op.binaryOp);
            }
            else if(c1->const_type == FLOATC && c2->const_type == INTEGERC){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding(c1->const_u.fval, (float)c2->const_u.intval, expr->op.binaryOp);
            }
            else if(c1->const_type == INTEGERC && c2->const_type == FLOATC){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding((float)c1->const_u.intval, c2->const_u.fval, expr->op.binaryOp);
            }
            else{
                //handle string in expr error
            }
            return Node;
        }
        else if((r->nodeType == CONST_VALUE_NODE && l->nodeType == EXPR_NODE) || (l->nodeType == CONST_VALUE_NODE && r->nodeType == EXPR_NODE)){
            AST_NODE *C_Node, *E_Node;
            if(r->nodeType == CONST_VALUE_NODE){
                C_Node = r;
                E_Node = ConstantFolding(l);
            }
            else{
                C_Node = l;
                E_Node = ConstantFolding(r);
            }
            EXPRSemanticValue *e = &E_Node->semantic_value.exprSemanticValue;
            if(e->isConstEval == 0)
                return Node;
            CON_Type *c = C_Node->semantic_value.const1;
            if(c->const_type == INTEGERC && e->isConstEval == 1){
                expr->isConstEval = 1;
                expr->constEvalValue.iValue = handleBinaryIntFolding(c->const_u.intval, e->constEvalValue.iValue, expr->op.binaryOp);
            }
            else if(c->const_type == FLOATC && e->isConstEval == 2){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding(c->const_u.fval, e->constEvalValue.fValue, expr->op.binaryOp);
            }
            else if(c->const_type == FLOATC && e->isConstEval == 1){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding(c->const_u.fval, (float)e->constEvalValue.iValue, expr->op.binaryOp);
            }
            else if(c->const_type == INTEGERC && e->isConstEval == 2){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding((float)c->const_u.intval, e->constEvalValue.fValue, expr->op.binaryOp);
            }
            else{
                //handle string in expr error
            }
            return Node;
        }
        else if(r->nodeType == EXPR_NODE && l->nodeType == EXPR_NODE){
            ConstantFolding(r);
            ConstantFolding(l);
            EXPRSemanticValue *e1 = &r->semantic_value.exprSemanticValue, *e2 = &l->semantic_value.exprSemanticValue;
            if(e1->isConstEval == 1 && e2->isConstEval == 1){
                expr->isConstEval = 1;
                expr->constEvalValue.iValue = handleBinaryIntFolding(e1->constEvalValue.iValue, e2->constEvalValue.iValue, expr->op.binaryOp);
            }
            else if(e1->isConstEval == 2 && e2->isConstEval == 2){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding(e1->constEvalValue.fValue, e2->constEvalValue.fValue, expr->op.binaryOp);
            }
            else if(e1->isConstEval == 2 && e2->isConstEval == 1){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding(e1->constEvalValue.fValue, (float)e2->constEvalValue.iValue, expr->op.binaryOp);
            }
            else if(e1->isConstEval == 1 && e2->isConstEval == 2){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleBinaryFloatFolding((float)e1->constEvalValue.iValue, e2->constEvalValue.fValue, expr->op.binaryOp);
            }
            return Node;
        }
    }
    else{
        AST_NODE *child = Node->child;
        if(child->nodeType == CONST_VALUE_NODE){
            CON_Type *c = child->semantic_value.const1;
            if(c->const_type == INTEGERC){
                expr->isConstEval = 1;
                expr->constEvalValue.iValue = handleUnaryIntFolding(c->const_u.intval, expr->op.unaryOp);
            }
            else if(c->const_type == FLOATC){
                expr->isConstEval = 2;
                expr->constEvalValue.fValue = handleUnaryFloatFolding(c->const_u.fval, expr->op.unaryOp);
            }
            else{
                //handle string in expr error
            }
        }
        return Node;
    }
    return NULL;
}

float handleUnaryFloatFolding(float a, UNARY_OPERATOR op){
    switch (op)
    {
    case UNARY_OP_POSITIVE:
        return a;
    case UNARY_OP_NEGATIVE:
        return -a;
    case UNARY_OP_LOGICAL_NEGATION:
        //handle float ! error
        break;
    default:
        break;
    }
    return 0;
}

int handleUnaryIntFolding(int a, UNARY_OPERATOR op){
    switch (op)
    {
    case UNARY_OP_POSITIVE:
        return a;
    case UNARY_OP_NEGATIVE:
        return -a;
    case UNARY_OP_LOGICAL_NEGATION:
        return !a;
    default:
        break;
    }
    return 0;
}

float handleBinaryFloatFolding(float a, float b, BINARY_OPERATOR op){
    switch (op)
    {
    case BINARY_OP_ADD:
        return a + b;
    case BINARY_OP_SUB:
        return a - b;
    case BINARY_OP_MUL:
        return a * b;
    case BINARY_OP_DIV:
        return a / b;
    case BINARY_OP_EQ:
        return a == b;
    case BINARY_OP_GE:
        return a >= b;
    case BINARY_OP_LE:
        return a <= b;
    case BINARY_OP_NE:
        return a != b;
    case BINARY_OP_GT:
        return a > b;
    case BINARY_OP_LT:
        return a < b;
    case BINARY_OP_AND:
        //handle float & error
        break;
    case BINARY_OP_OR:
        //handle float & error
        break;
    default:
        break;
    }
    return 0;
}

int handleBinaryIntFolding(int a, int b, BINARY_OPERATOR op){
    switch (op)
    {
    case BINARY_OP_ADD:
        return a + b;
    case BINARY_OP_SUB:
        return a - b;
    case BINARY_OP_MUL:
        return a * b;
    case BINARY_OP_DIV:
        return a / b;
    case BINARY_OP_EQ:
        return a == b;
    case BINARY_OP_GE:
        return a >= b;
    case BINARY_OP_LE:
        return a <= b;
    case BINARY_OP_NE:
        return a != b;
    case BINARY_OP_GT:
        return a > b;
    case BINARY_OP_LT:
        return a < b;
    case BINARY_OP_AND:
        return a & b;
    case BINARY_OP_OR:
        return a | b;
    default:
        break;
    }
    return 0;
}