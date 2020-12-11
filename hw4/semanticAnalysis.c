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
void processDeclarationNode(AST_NODE* declarationNode, int LocalOrGlobalDecl);
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
TypeDescriptor* extendTypeDescriptor(AST_NODE* ID, TypeDescriptor* elementType, int LocalOrGlobalDecl, int voidValid);
AST_NODE* ExprNodeFolding(AST_NODE* ExprNode);
TypeDescriptor* getTypeDescriptor(AST_NODE* IDNode);
void declareVariable(AST_NODE* TypeNode, int LocalOrGlobalDecl);
void FillInSymbolTable(char *name, TypeDescriptor* typeDescStruct, SymbolAttributeKind attrKind);
void declareTypedef(AST_NODE* TypeNode, int LocalOrGlobalDecl);
float handleBinaryFloatFolding(float a, float b, BINARY_OPERATOR op);
float handleUnaryFloatFolding(float a, UNARY_OPERATOR op);
int handleUnaryIntFolding(int a, UNARY_OPERATOR op);
int handleBinaryIntFolding(int a, int b, BINARY_OPERATOR op);
SymbolTableEntry* getSymbol(AST_NODE* Node);
AST_NODE* NodeFolding(AST_NODE* Node);
DATA_TYPE checkType(AST_NODE *Node);
int checkArrayDim(AST_NODE *Node);
void handleReturnNode(AST_NODE *Node);
typedef enum ErrorMsgKind
{
    NOT_DECLARED_IN_THIS_SCOPE, // ‘<name>’ was not declared in this scope
    REDECLARATION, //redeclaration of ‘<type> <name>’
    TOO_FEW_ARGUMENTS_TO_FUNCTION, //too few arguments to function ‘<function signature>’
    TOO_MANY_ARGUMENTS_TO_FUNCTION,  //too many arguments to function ‘<function signature>’
    DIM_OVERSIZE,//subscripted value is neither array nor pointer nor vector
    ASSIGN_TO_ARRAY,
    ARRAY_SUBSCRIPT_NOT_INT,
    INT_TO_ARRAY_PARAM,
    ARRAY_TO_INT_PARAM,
    FUNC_DECL_IN_SCOPE,
    NON_VOLID_RETURN_ERROR,
    VOLID_RETURN_ERROR,
    INVALID_BINARY,
    INCOMPUTABLE_VOLID,
    STRING_IN_EXPR,
    NON_CALLABLE,
    DIM_INFO_NOT_INT,
    DIM_INFO_LESS_ZERO,
    GLOBAL_INIT_NOT_CONST,
    REDEC_TYDEDEF,
    VOID_TO_ARRAY_PARAM,
    VOID_TO_INT_PARAM

} ErrorMsgKind;
void printError(ErrorMsgKind error, const void *Node1){
    AST_NODE *Node = (AST_NODE *)Node1;
    printf("Error found in line %d\n", Node->linenumber);
    switch (error)
    {
    case NOT_DECLARED_IN_THIS_SCOPE:
        fprintf(stderr, "ERROR: \'%s\' was not declared in this scope\n", Node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case REDECLARATION:
        fprintf(stderr, "redeclaration of \'%s\'\n", Node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case DIM_INFO_NOT_INT:
        fprintf(stderr, "array subscript is not an integer\n");
        break;
    case DIM_INFO_LESS_ZERO:
        fprintf(stderr, "size of array \'%s\' is negative\n", Node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case GLOBAL_INIT_NOT_CONST:
        fprintf(stderr, "initializer element is not constant\n");
        break;
    case REDEC_TYDEDEF:
        fprintf(stderr, "conflicting types for \'%s\'\n", Node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case TOO_FEW_ARGUMENTS_TO_FUNCTION:
        fprintf(stderr, "ERROR: too few arguments to function \'%s\'\n", Node->child->semantic_value.identifierSemanticValue.identifierName);
        break;
    case TOO_MANY_ARGUMENTS_TO_FUNCTION:
        fprintf(stderr, "ERROR: too many arguments to function \'%s\'\n", Node->child->semantic_value.identifierSemanticValue.identifierName);
        break;
    case DIM_OVERSIZE:
        fprintf(stderr, "ERROR: subscripted value is neither array nor pointer nor vector\n");
        break;
    case ASSIGN_TO_ARRAY:
        fprintf(stderr, "ERROR: assignment to expression with array type\n");
        break;
    case ARRAY_SUBSCRIPT_NOT_INT:
        fprintf(stderr, "ERROR: array subscript is not an integer'\n");
        break;
    case INT_TO_ARRAY_PARAM:
        fprintf(stderr, "ERROR: invalid conversion from '<scalar type>' to '<array type>'\n");
        break;
    case ARRAY_TO_INT_PARAM: //TODO:
        fprintf(stderr, "ERROR: invalid conversion from '<array type>' to '<scalar type>'\n");
        break;
    case VOID_TO_ARRAY_PARAM:
        fprintf(stderr, "ERROR: invalid conversion from 'void' to '<array type>'\n");
        break;
    case VOID_TO_INT_PARAM: //TODO:
        fprintf(stderr, "ERROR: invalid conversion from '<array type>' to 'void'\n");
        break;
    case FUNC_DECL_IN_SCOPE:
        fprintf(stderr, "ERROR: function definition is not allowed here");   
        break;
    case INCOMPUTABLE_VOLID:
        fprintf(stderr, "ERROR: incompatible type 'void'\n");
        break;
    case VOLID_RETURN_ERROR:
        fprintf(stderr, "ERROR: function '%s' should be return type 'void'\n", Node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case NON_VOLID_RETURN_ERROR:
        fprintf(stderr, "ERROR: function '%s' should be return type '%s'\n", Node->semantic_value.identifierSemanticValue.identifierName, Node->leftmostSibling->semantic_value.identifierSemanticValue.identifierName);
        break;
    case NON_CALLABLE:
        fprintf(stderr, "ERROR: called object '%s' is not a function or function pointer\n", Node->child->semantic_value.identifierSemanticValue.identifierName);
        break;
    case INVALID_BINARY:
        fprintf(stderr, ":%d ERROR: invalid operands to binary expression ('float' and 'float')\n", Node->linenumber);
        break;
    case STRING_IN_EXPR:
        fprintf(stderr, ":%d ERROR: string in expr\n", Node->linenumber);
        break;
    default:
        fprintf(stderr, "error undefined\n");
        break;
    }
    return;
}


void semanticAnalysis(AST_NODE *root)
{
    processProgramNode(root);
    fprintf(stderr, "OKKKK\n");
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
                processDeclarationNode(varDeclNode, 0);
                varDeclNode = varDeclNode->rightSibling;
            }
        }
        else if(declaNode->nodeType == DECLARATION_NODE){ //function declaration
            processDeclarationNode(declaNode, 0);
        }
        declaNode = declaNode->rightSibling;
    }
}

void processDeclarationNode(AST_NODE* declarationNode, int LocalOrGlobalDecl){
    if(declarationNode->nodeType != DECLARATION_NODE){
        fprintf(stderr, "Should not pass non-DECLARATION_NODE into processDeclarationNode()\n");
        exit(0);
    }

    DECL_KIND declKind =  declarationNode->semantic_value.declSemanticValue.kind;
    if(declKind == VARIABLE_DECL){
        declareVariable(declarationNode->child, LocalOrGlobalDecl);
    }
    else if(declKind == TYPE_DECL){
        declareTypedef(declarationNode->child, LocalOrGlobalDecl);
    }
    else if(declKind == FUNCTION_DECL){
        if(LocalOrGlobalDecl == 1){
            printError(FUNC_DECL_IN_SCOPE, declarationNode);
        }
        else
            declareFunction(declarationNode->child);
    }
    else if(declKind == FUNCTION_PARAMETER_DECL){
        fprintf(stderr, "Should be handled in declareFunction()\n");
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
    openScope();
    AST_NODE *test = whileNode->child;
    if(test->nodeType == STMT_NODE && test->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT){
        checkAssignmentStmt(test);
    }
    else
        processExprNode(test);
    AST_NODE *stmt = test->rightSibling;
    processStmtNode(stmt);
    closeScope();
}


void checkForStmt(AST_NODE* forNode)
{
    openScope();
    AST_NODE *assign_expr_list = forNode->child, *relop_expr_list = assign_expr_list->rightSibling, *second_assign_expr_list = relop_expr_list->rightSibling, *stmt = second_assign_expr_list->rightSibling;
    if(assign_expr_list->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE){
        AST_NODE *assign_expr = assign_expr_list->child;
        while(assign_expr){
            if(assign_expr->nodeType == STMT_NODE && assign_expr->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT){
                checkAssignmentStmt(assign_expr);
            }
            else
                processExprNode(assign_expr);
            assign_expr = assign_expr->rightSibling;
        }
    }
    if(relop_expr_list->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE){
        AST_NODE *relop_expr = relop_expr_list->child;
        while(relop_expr){
            processExprNode(relop_expr);
            relop_expr = relop_expr->rightSibling;
        }
    }
    if(second_assign_expr_list->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE){
        AST_NODE *assign_expr = second_assign_expr_list->child;
        while(assign_expr){
            if(assign_expr->nodeType == STMT_NODE && assign_expr->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT){
                checkAssignmentStmt(assign_expr);
            }
            else
                processExprNode(assign_expr);
            assign_expr = assign_expr->rightSibling;
        }
    }
    processStmtNode(stmt);
    closeScope();
}


int checkArrayDim(AST_NODE *Node){
    SymbolTableEntry *entry = getSymbol(Node);
    int d = 0;
    if(entry == NULL){
        printError(NOT_DECLARED_IN_THIS_SCOPE, Node);
    }
    else if(entry->attribute->attributeKind == FUNCTION_SIGNATURE || entry->attribute->attr.typeDescriptor->kind != ARRAY_TYPE_DESCRIPTOR){
        printError(DIM_OVERSIZE, Node);
    }
    else{
        AST_NODE *dim = Node->child;
        while(dim){
            d ++;
            NodeFolding(dim);
            if(dim->dataType != INT_TYPE){
                printError(DIM_INFO_NOT_INT, Node);
            }
            dim = dim->rightSibling;
        }
        if(d == entry->attribute->attr.typeDescriptor->properties.arrayProperties.dimension)
            return 1;
        else if(d < entry->attribute->attr.typeDescriptor->properties.arrayProperties.dimension)
            return 0;
        else{
            printError(DIM_OVERSIZE, Node);
            return 0;
        }
    }
}

void checkAssignmentStmt(AST_NODE* assignmentNode)
{
    AST_NODE *l = assignmentNode->child;
    AST_NODE *r = l->rightSibling;
    if(l->nodeType != IDENTIFIER_NODE){
        perror("it need id node at assignment right side");
        exit(0);
    }
    else{
        if(l->semantic_value.identifierSemanticValue.kind == ARRAY_ID && !checkArrayDim(l)){
            printError(ASSIGN_TO_ARRAY, assignmentNode);
            return;
        }
        else{
            SymbolTableEntry *entry = getSymbol(l);
            if(entry == NULL){
                printError(NOT_DECLARED_IN_THIS_SCOPE, assignmentNode->child);
                return;
            }
        }
        NodeFolding(r);
        DATA_TYPE type = checkType(l);
        if(type == INT_TYPE && r->dataType != INT_TYPE){
            r->dataType = INT_TYPE;
        }
        else if(type == FLOAT_TYPE && r->dataType != FLOAT_TYPE){
            r->dataType = FLOAT_TYPE;
        }
    }
    return;
}


void checkIfStmt(AST_NODE* ifNode)
{
    openScope();
    AST_NODE *test = ifNode->child;
    if(test->nodeType == STMT_NODE && test->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT){
        checkAssignmentStmt(test);
    }
    else
        processExprNode(test);
    AST_NODE *stmt = test->rightSibling;
    processStmtNode(stmt);
    AST_NODE *ELSE = stmt->rightSibling;
    if(ELSE->nodeType != NUL_NODE)
        processStmtNode(ELSE);
    closeScope();
    return;
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
}

int checkArray(ArrayProperties *prop, AST_NODE *arr){
    if(arr->nodeType != IDENTIFIER_NODE){
        return 0;
    }
    if(checkArrayDim(arr)){
        return 0;
    }
    return 1;
}

int checkParam(Parameter *decl_param, AST_NODE *param){
    if(decl_param->type->kind == ARRAY_TYPE_DESCRIPTOR){
        if(!checkArray(&decl_param->type->properties.arrayProperties, param)){
            if(param->dataType == VOID_TYPE){
                printError(VOID_TO_ARRAY_PARAM, param);
            }
            else{
                printError(INT_TO_ARRAY_PARAM, param);
            }
        }
        else{

        }
    }
    else{
        NodeFolding(param);
        if(param->nodeType == IDENTIFIER_NODE && param->semantic_value.identifierSemanticValue.kind == ARRAY_ID && !checkArrayDim(param)){
            printError(ARRAY_TO_INT_PARAM, param);
        }
        if(param->dataType == VOID_TYPE){
            printError(VOID_TO_INT_PARAM, param);
            return 0;
        }
    }
    return 1;
}

void checkFunctionCall(AST_NODE* functionCallNode)
{
    SymbolTableEntry *entry = getSymbol(functionCallNode->child);
    if(entry == NULL){
        printError(NOT_DECLARED_IN_THIS_SCOPE, functionCallNode);
        return;
    }
    AST_NODE *param_list = functionCallNode->child->rightSibling;
    if(entry->attribute->attributeKind != FUNCTION_SIGNATURE){
        printError(NON_CALLABLE, functionCallNode);
        return;
    }
    FunctionSignature *signature = entry->attribute->attr.functionSignature;
    if(signature->parametersCount == 0 && param_list->nodeType == NUL_NODE)
        return;
    Parameter *decl_param = signature->parameterList;
    AST_NODE *param = param_list->child;
    while(decl_param){
        if(param == NULL){
            printError(TOO_FEW_ARGUMENTS_TO_FUNCTION, functionCallNode);
            return;
        }
        checkParam(decl_param, param);
        decl_param = decl_param->next;
        param = param->rightSibling;
    }
    if(param != NULL){
        printError(TOO_MANY_ARGUMENTS_TO_FUNCTION, functionCallNode);
    }
    return;
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
    NodeFolding(exprNode);
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
    AST_NODE *Stmts = NULL, *Decls = NULL;
    AST_NODE *Stmt = NULL, *Decl = NULL;
    if(blockNode->child == NULL)
        return;
    if(blockNode->child->nodeType == VARIABLE_DECL_LIST_NODE){
        Decls = blockNode->child;
        Decl = Decls->child;
        if(Decls->rightSibling != NULL && Decls->rightSibling->nodeType == STMT_LIST_NODE){
            Stmts = Decls->rightSibling;
            Stmt = Stmts->child;
        }
    }
    else if(blockNode->child->nodeType == STMT_LIST_NODE){
        Stmts = blockNode->child;
        Stmt = Stmts->child;
    }
    while (Decl)
    {   
        processDeclarationNode(Decl, 1);
        Decl = Decl->rightSibling;
    }
    while(Stmt){
        processStmtNode(Stmt);
        Stmt = Stmt->rightSibling;
    }
    return;
}


void processStmtNode(AST_NODE* stmtNode)
{
    if(stmtNode->nodeType == BLOCK_NODE){
        processBlockNode(stmtNode);
    }
    else if(stmtNode->nodeType == CONST_VALUE_NODE){
        NodeFolding(stmtNode);
    }
    else if(stmtNode->nodeType == NUL_NODE){
        return;
    }
    else if(stmtNode->nodeType == STMT_NODE){
        switch (stmtNode->semantic_value.stmtSemanticValue.kind)
        {
        case WHILE_STMT:
            checkWhileStmt(stmtNode);
            break;
        case IF_STMT:
            checkIfStmt(stmtNode);
            break;
        case FOR_STMT:
            checkForStmt(stmtNode);
            break;
        case ASSIGN_STMT:
            checkAssignmentStmt(stmtNode);
            break;
        case FUNCTION_CALL_STMT:
            checkFunctionCall(stmtNode);
            break;
        case RETURN_STMT:
            handleReturnNode(stmtNode);
            break;
        default:
            perror("no match stmt");
            exit(0);
            break;
        }
    }
    else{
        perror("input no stmt");
        exit(0);
    }
}


void processGeneralNode(AST_NODE *node)
{
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
}

void handleReturnNode(AST_NODE* returnNode){
    AST_NODE *now = returnNode;
    while (now != NULL && now->nodeType != DECLARATION_NODE && now->semantic_value.declSemanticValue.kind != FUNCTION_DECL)
    {
        now = now->parent;
    }
    if(now == NULL){
        perror("wrong return place");
        exit(0);
        return;
    }
    now = now->child->rightSibling;
    SymbolTableEntry *entry = getSymbol(now);
    DATA_TYPE return_type = entry->attribute->attr.functionSignature->returnType;
    if(return_type == VOID_TYPE && returnNode->child->nodeType != NUL_NODE){
        printError(VOLID_RETURN_ERROR, now);
    }
    if(return_type != VOID_TYPE && returnNode->child->nodeType == NUL_NODE){
        printError(NON_VOLID_RETURN_ERROR, now);
    }
}
void declareTypedef(AST_NODE* TypeNode, int LocalOrGlobalDecl){
    AST_NODE* IDNode = TypeNode->rightSibling;
    while(IDNode != NULL){
        char *varName = IDNode->semantic_value.identifierSemanticValue.identifierName;
        TypeDescriptor* typeDescStruct = extendTypeDescriptor(IDNode, getTypeDescriptor(TypeNode), LocalOrGlobalDecl, 1);
        FillInSymbolTable(varName, typeDescStruct, TYPE_ATTRIBUTE);
        IDNode = IDNode->rightSibling;
    }
}
void declareVariable(AST_NODE* TypeNode, int LocalOrGlobalDecl){
    AST_NODE* IDNode = TypeNode->rightSibling;
    while(IDNode != NULL){
        char *varName = IDNode->semantic_value.identifierSemanticValue.identifierName;
        TypeDescriptor* typeDescStruct = extendTypeDescriptor(IDNode, getTypeDescriptor(TypeNode), LocalOrGlobalDecl, 0);
        FillInSymbolTable(varName, typeDescStruct, VARIABLE_ATTRIBUTE);
        IDNode = IDNode->rightSibling;
    }
}
void declareFunction(AST_NODE* returnTypeNode){
    //new func attr
    openScope();
    SymbolAttribute *funcAttr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
    funcAttr->attributeKind = FUNCTION_SIGNATURE;
    funcAttr->attr.functionSignature = (FunctionSignature*)malloc(sizeof(FunctionSignature));
    funcAttr->attr.functionSignature->parameterList = NULL;

    FunctionSignature* funcSign = funcAttr->attr.functionSignature;
    funcSign->parametersCount = 0;
    
    TypeDescriptor* typeDescStruct = getTypeDescriptor(returnTypeNode); //check for return type
    if(typeDescStruct->kind != SCALAR_TYPE_DESCRIPTOR){
        fprintf(stderr, "Function return type can only be SCALAR\n");
        exit(0);
    }
    funcSign->returnType = typeDescStruct->properties.dataType;
    free(typeDescStruct);
    AST_NODE* funcNameNode = returnTypeNode->rightSibling;
    char *funcName = funcNameNode->semantic_value.identifierSemanticValue.identifierName;
    //check function 有沒有被declare過
    if(declaredInThisScope(funcName, 0) != NULL){
        printError(REDECLARATION, funcNameNode);
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
    if(!enterSymbol(funcName, funcAttr, 0)){
        fprintf(stderr, "Error in declareFunction\n");
        exit(0);
    }
    processBlockNode(paramListNode->rightSibling);
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
            fprintf(stderr, "Error in getTypeDescriptor(), Unknown dataType\n");
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
        printError(NOT_DECLARED_IN_THIS_SCOPE, IDNode);
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
        AST_NODE *ErrorNode = (AST_NODE*)malloc(sizeof(AST_NODE));
        ErrorNode->semantic_value.identifierSemanticValue.identifierName = name;
        if(attrKind == VARIABLE_ATTRIBUTE){
            printError(REDECLARATION, ErrorNode);
        }
        else{
            printError(REDEC_TYDEDEF, ErrorNode);
        }
        
        
    }
    if(!enterSymbol(name, attr, getCurrentScope())){
        fprintf(stderr, "Error in FillInSymbolTable\n");
        exit(0);
    }
}
Parameter* makeParameter(AST_NODE* typeNode){
    AST_NODE* ID = typeNode->rightSibling;

    char *name = ID->semantic_value.identifierSemanticValue.identifierName;
    TypeDescriptor* typeDescStruct = extendTypeDescriptor(ID, getTypeDescriptor(typeNode), 0, 0);

    //fill Parameter struct
    Parameter *paramStruct = (Parameter*)malloc(sizeof(Parameter));
    paramStruct->parameterName = name;
    paramStruct->type = typeDescStruct;

    FillInSymbolTable(name, typeDescStruct, VARIABLE_ATTRIBUTE);
    return paramStruct;
}

TypeDescriptor* extendTypeDescriptor(AST_NODE* ID, TypeDescriptor* typeDescStruct, int LocalOrGlobalDecl, int voidValid){
    DATA_TYPE tempDataType;
    if(typeDescStruct->kind == ARRAY_TYPE_DESCRIPTOR){
        tempDataType = typeDescStruct->properties.arrayProperties.elementType;
    }
    else if(typeDescStruct->kind == SCALAR_TYPE_DESCRIPTOR){
        tempDataType = typeDescStruct->properties.dataType;
    }
    else{
        fprintf(stderr, "Error in extendTypeDescriptor1\n");
        exit(0);
    }
    if(tempDataType == VOID_TYPE && voidValid == 0){
        fprintf(stderr, "storage size of \'%s\' isn’t known\n", ID->semantic_value.identifierSemanticValue.identifierName);
        exit(0);
    }

    if(ID->semantic_value.identifierSemanticValue.kind == NORMAL_ID){} //No need to change
    else if(ID->semantic_value.identifierSemanticValue.kind == ARRAY_ID){
        if(typeDescStruct->kind == SCALAR_TYPE_DESCRIPTOR){
            //fprintf(stderr, "Extend SCALAR_TYPE to ARRAY_TYPE\n");
            typeDescStruct->properties.arrayProperties.dimension = 0;
        }
        else if(typeDescStruct->kind == ARRAY_TYPE_DESCRIPTOR){}
        else{
            fprintf(stderr, "Error in extendTypeDescriptor2\n");
            exit(0);
        }
        AST_NODE *dimInfo = ID->child;
        while(dimInfo != NULL){
            if(dimInfo == ID->child && dimInfo->nodeType == NUL_NODE){//first dim can be null
                typeDescStruct->properties.arrayProperties.sizeInEachDimension[typeDescStruct->properties.arrayProperties.dimension++] \
                = -1;
                dimInfo = dimInfo->rightSibling;
                continue;
            }
            dimInfo = NodeFolding(dimInfo);
            //fprintf(stderr, "isConstEval: %d\n", isConstEval);
            //TODO: rewrite isConstEval
            if(dimInfo->nodeType != CONST_VALUE_NODE){
                printError(DIM_INFO_NOT_INT, ID);
            }
            else if(dimInfo->dataType != INT_TYPE){
                printError(DIM_INFO_NOT_INT, ID);
            }
            else if(dimInfo->dataType == INT_TYPE){
                int iValue = dimInfo->semantic_value.const1->const_u.intval;
                //fprintf(stderr, "isConstEval = 1, iValue: %d\n", iValue);
                if(iValue < 0){
                    printError(DIM_INFO_LESS_ZERO, ID);
                }
                typeDescStruct->properties.arrayProperties.sizeInEachDimension[typeDescStruct->properties.arrayProperties.dimension++] \
                = iValue;
            }
            else{
                fprintf(stderr, "Error when calling isConstEval()\n");
                exit(0);
            }
            
            dimInfo = dimInfo->rightSibling;
        }
        typeDescStruct->properties.arrayProperties.elementType = tempDataType;
        typeDescStruct->kind = ARRAY_TYPE_DESCRIPTOR;
    }
    else if(ID->semantic_value.identifierSemanticValue.kind == WITH_INIT_ID){
        if(typeDescStruct->kind != SCALAR_TYPE_DESCRIPTOR){
            printError(ASSIGN_TO_ARRAY, ID);
        }
        AST_NODE *child = NodeFolding(ID->child);
        //fprintf(stderr, "isConstEval: %d\n", isConstEval);
        if(LocalOrGlobalDecl == 0){ //global decl
            if(child->nodeType != CONST_VALUE_NODE){
                printError(GLOBAL_INIT_NOT_CONST, ID);
            }
        }
    }
    else{
        fprintf(stderr, "Error in extendTypeDescriptor3\n");
        //fprintf(stderr, "kind: %d\n", ID->semantic_value.identifierSemanticValue.kind);
        exit(0);
    }
    return typeDescStruct;
}

AST_NODE* NodeFolding(AST_NODE *Node){
    if(Node->nodeType == EXPR_NODE)
        return ExprNodeFolding(Node);
    else if(Node->nodeType == CONST_VALUE_NODE){
        switch (Node->semantic_value.const1->const_type)
        {
        case INTEGERC:
            Node->dataType = INT_TYPE;
            break;
        case FLOATC:
            Node->dataType = FLOAT_TYPE;
            break;
        case STRINGC:
            Node->dataType = CONST_STRING_TYPE;
            break;
        default:
            break;
        }
        return Node;
    }
    else if(Node->nodeType == STMT_NODE && Node->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT){
        checkFunctionCall(Node);
        Node->dataType = checkType(Node->child);
    }
    else if(Node->nodeType == IDENTIFIER_NODE){
        Node->dataType = checkType(Node);
    }
    else{
        Node->dataType = NONE_TYPE;
    }
    return Node;
}

float handleUnaryFloatFolding(float a, UNARY_OPERATOR op){
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
        return 0;
        break;
    case BINARY_OP_OR:
        //handle float | error
        return 0;
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

DATA_TYPE checkType(AST_NODE *Node){
    if(Node->nodeType == CONST_VALUE_NODE){
        if(Node->semantic_value.const1->const_type == INTEGERC)
            return INT_TYPE;
        else if(Node->semantic_value.const1->const_type == FLOATC)
            return FLOAT_TYPE;
        else{
           //handle error 
           perror("string in wrong place 755");
            exit(0);
        }
    }
    else if(Node->nodeType == STMT_NODE){
        if(Node->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT){
            return checkType(Node->child);
        }
        else{
            //handle error
            perror("string in wrong place");
            exit(0);
        }
    }
    else if(Node->nodeType == IDENTIFIER_NODE){
        SymbolTableEntry *symbol = getSymbol(Node);
        if(symbol == NULL){
            printError(NOT_DECLARED_IN_THIS_SCOPE, Node);
            return NONE_TYPE;
        } 
        Node->semantic_value.identifierSemanticValue.symbolTableEntry = symbol;
        SymbolAttribute *attribute = symbol->attribute;
        if(attribute->attributeKind == VARIABLE_ATTRIBUTE || attribute->attributeKind == TYPE_ATTRIBUTE){
            if(attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR){
                return attribute->attr.typeDescriptor->properties.dataType;
            }
            else{
                checkArrayDim(Node);
                return attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
            }
        }
        else if(attribute->attributeKind == FUNCTION_SIGNATURE){
            return attribute->attr.functionSignature->returnType;
        }
    }
    perror("wrong check");
    exit(0);
}

int isRelopExpr(BINARY_OPERATOR op){
    switch (op)
    {
    case BINARY_OP_ADD:
    case BINARY_OP_SUB:
    case BINARY_OP_MUL:
    case BINARY_OP_DIV:
        return 0;
        break;
    case BINARY_OP_EQ:
    case BINARY_OP_GE:
    case BINARY_OP_LE:
    case BINARY_OP_NE:
    case BINARY_OP_GT:
    case BINARY_OP_LT:
    case BINARY_OP_AND:
    case BINARY_OP_OR:
    default:
        return 1;
    }
}

AST_NODE* ExprNodeFolding(AST_NODE* Node){
    if(Node->nodeType != EXPR_NODE)
        return NULL;
    EXPRSemanticValue *expr = &Node->semantic_value.exprSemanticValue;    
    if(expr->kind == BINARY_OPERATION){
        BINARY_OPERATOR op = expr->op.binaryOp;
        AST_NODE *l = NodeFolding(Node->child), *r = NodeFolding(Node->child->rightSibling);
        if(r->dataType == NONE_TYPE || l->dataType == NONE_TYPE){
            Node->dataType = NONE_TYPE;
            return Node;
        }
        if(r->nodeType == CONST_VALUE_NODE && l->nodeType == CONST_VALUE_NODE){
            CON_Type *c1 = l->semantic_value.const1, *c2 = r->semantic_value.const1, *c = (CON_Type *)malloc(sizeof(CON_Type));
            if(c1->const_type == INTEGERC && c2->const_type == INTEGERC){
                c->const_type = INTEGERC;
                Node->dataType = INT_TYPE;
                c->const_u.intval = handleBinaryIntFolding(c1->const_u.intval, c2->const_u.intval, op);
            }
            else if(c1->const_type == FLOATC && c2->const_type == FLOATC){
                if(isRelopExpr(op)){
                    c->const_type = INTEGERC;
                    Node->dataType = INT_TYPE;
                    c->const_u.intval = handleBinaryFloatFolding(c1->const_u.fval, c2->const_u.fval, op);
                    if(op == BINARY_OP_ADD || op == BINARY_OP_OR){
                        printError(INVALID_BINARY, Node);
                    }
                }
                else{
                    c->const_type = FLOATC;
                    Node->dataType = FLOAT_TYPE;
                    c->const_u.fval = handleBinaryFloatFolding(c1->const_u.fval, c2->const_u.fval, op);
                }
            }
            else if(c1->const_type == FLOATC && c2->const_type == INTEGERC){
                if(isRelopExpr(op)){
                    c->const_type = INTEGERC;
                    Node->dataType = INT_TYPE;
                    c->const_u.intval = handleBinaryFloatFolding(c1->const_u.fval, (float)c2->const_u.intval, op);
                    if(op == BINARY_OP_ADD || op == BINARY_OP_OR){
                        printError(INVALID_BINARY, Node);
                    }
                }
                else{
                    c->const_type = FLOATC;
                    Node->dataType = FLOAT_TYPE;
                    c->const_u.fval = handleBinaryFloatFolding(c1->const_u.fval, (float)c2->const_u.intval, op);
                }
            }
            else if(c1->const_type == INTEGERC && c2->const_type == FLOATC){
                if(isRelopExpr(op)){
                    c->const_type = INTEGERC;
                    Node->dataType = INT_TYPE;
                    c->const_u.intval = handleBinaryFloatFolding((float)c1->const_u.intval, c2->const_u.fval, op);
                    if(op == BINARY_OP_ADD || op == BINARY_OP_OR){
                        printError(INVALID_BINARY, Node);
                    }
                }
                else{
                    c->const_type = FLOATC;
                    Node->dataType = FLOAT_TYPE;
                    c->const_u.fval = handleBinaryFloatFolding((float)c1->const_u.intval, c2->const_u.fval, op);
                }
            }
            else{
                //handle string in expr error
                Node->dataType = NONE_TYPE;
            }
            Node->nodeType = CONST_VALUE_NODE;
            Node->semantic_value.const1 = c;
            return Node;
        }
        else{
            if(r->dataType == CONST_STRING_TYPE || l->dataType == CONST_STRING_TYPE){
                Node->dataType = NONE_TYPE;
            }
            else if(isRelopExpr(op)){
                Node->dataType = INT_TYPE;
                if((op == BINARY_OP_ADD || op == BINARY_OP_OR) && (r->dataType == FLOAT_TYPE || l->dataType == FLOAT_TYPE)){
                    printError(INVALID_BINARY, Node);
                }
            }
            else if(r->dataType == FLOAT_TYPE || l->dataType == FLOAT_TYPE){
                Node->dataType = FLOAT_TYPE;
            }
            else{
                Node->dataType = INT_TYPE;
            }
        }
        return Node;
    }
    else{
        AST_NODE *child = NodeFolding(Node->child);
        if(child->nodeType == NONE_TYPE){
            Node->dataType = NONE_TYPE;
            return Node;
        }
        if(child->nodeType == CONST_VALUE_NODE){
            CON_Type *c = child->semantic_value.const1, *c2 = (CON_Type *)malloc(sizeof(CON_Type));
            if(c->const_type == INTEGERC){
                c2->const_type = INTEGERC;
                Node->dataType = INT_TYPE;
                c2->const_u.intval = handleUnaryIntFolding(c->const_u.intval, expr->op.unaryOp);
            }
            else if(c->const_type == FLOATC){
                c2->const_type = FLOATC;
                Node->dataType = FLOAT_TYPE;
                c2->const_u.fval = handleUnaryFloatFolding(c->const_u.fval, expr->op.unaryOp);
            }
            else{
                Node->dataType = NONE_TYPE;
            }
            Node->nodeType = CONST_VALUE_NODE;
            Node->semantic_value.const1 = c2;
        }
        else{
            if(child->dataType == CONST_STRING_TYPE){
                Node->dataType = NONE_TYPE;
            }
            else if(child->dataType == INT_TYPE){
                Node->dataType = INT_TYPE;
            }
            else{
                Node->dataType = FLOAT_TYPE;
            }
        }
        return Node;
    }
    return NULL;
}

SymbolTableEntry* getSymbol(AST_NODE* Node){
    if(Node->nodeType != IDENTIFIER_NODE)
        return NULL;
    if(Node->semantic_value.identifierSemanticValue.symbolTableEntry == NULL){
        Node->semantic_value.identifierSemanticValue.symbolTableEntry = retrieveSymbol(Node->semantic_value.identifierSemanticValue.identifierName);
    }
    return Node->semantic_value.identifierSemanticValue.symbolTableEntry;
}
