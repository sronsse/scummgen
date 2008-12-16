%{
#include "util/Log.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"
#include "Function.hpp"
#include "Statement.hpp"
#include <sstream>
using namespace std;

extern int yylineno;

int yylex(void);
void yyerror(vector<Declaration *> &declarations, vector<Function *> &functions, string s);

// Vectors collecting nodes during parsing so that in case of a parsing error, we can still free memory
vector<Declaration *> declarationCollector;
vector<Expression *> expressionCollector;
vector<Statement *> statementCollector;
vector<vector<Declaration *> > declarationListCollector;
vector<vector<Expression *> > expressionListCollector;
vector<vector<Statement *> > statementListCollector;
vector<string> assemblyTokens;

// For more information in case of a parsing error
#define YYERROR_VERBOSE
%}

// Used types : a number, a string, or a generic pointer which needs casting
%union
{
#define STRING_LENGTH 512
    int number;
	char string[STRING_LENGTH];
};

// Tokens declaration
%token <string> T_STRING
%token T_CONST
%token T_VAR
%token T_FUNCTION
%token T_INLINE
%token T_THREAD
%token T_IF
%token T_ELSE
%token T_SWITCH
%token T_CASE
%token T_DEFAULT
%token T_FOR
%token T_WHILE
%token T_CONTINUE
%token T_BREAK
%token T_RETURN
%token T_ASSEMBLY
%token <number> T_NUMBER
%token <string> T_IDENTIFIER

// Priority of operators
%left '='
%left T_GE T_LE T_EQ T_NE T_LAND T_LOR '>' '<'
%left '+' '-'
%left '&' '|'
%left '*' '/'
%nonassoc T_UMINUS
%nonassoc T_NOT
%nonassoc T_INC T_DEC

// Inputs to yyparse
%parse-param {vector<Declaration *> &declarations}
%parse-param {vector<Function *> &functions}

// Starting grammar rule
%start file

%%

arg:
	T_VAR T_IDENTIFIER
	{
		Declaration *declaration = new Declaration(DECLARATION_VAR, $2);
		declarationCollector.push_back(declaration);
	}
	;

args:
	args ',' arg
	{
		Declaration *declaration = declarationCollector.back();
		declarationListCollector.back().push_back(declaration);
		declarationCollector.pop_back();
	}
	| arg
	{
		vector<Declaration *> v;
		Declaration *declaration = declarationCollector.back();
		v.push_back(declaration);
		declarationCollector.pop_back();
		declarationListCollector.push_back(v);
	}
	| /* nothing */
	{
		vector<Declaration *> v;
		declarationListCollector.push_back(v);
	}
	;

assemblyTokens:
	assemblyTokens T_IDENTIFIER
	{
		assemblyTokens.push_back($2);
	}
	| assemblyTokens T_NUMBER
	{
		ostringstream oss;
		oss << $2;
		assemblyTokens.push_back(oss.str());
	}
	| assemblyTokens T_STRING
	{
		assemblyTokens.push_back($2);
	}
	| /* nothing */
	;

blockStatement:
	'{' declarations statements '}'
	{
		BlockStatement *blockStatement = new BlockStatement();
		for (int i = 0; i < declarationListCollector.back().size(); i++)
			blockStatement->addDeclaration(declarationListCollector.back()[i]);
		declarationListCollector.pop_back();
		for (int i = 0; i < statementListCollector.back().size(); i++)
			blockStatement->addStatement(statementListCollector.back()[i]);
		statementListCollector.pop_back();
		statementCollector.push_back(blockStatement);
	}

callExpression:
	T_IDENTIFIER '(' parameters ')'
	{
		CallExpression *callExpression = new CallExpression($1);
		for (int i = 0; i < expressionListCollector.back().size(); i++)
			callExpression->addParameter(expressionListCollector.back()[i]);
		expressionListCollector.pop_back();
		expressionCollector.push_back(callExpression);
	}
	;

caseStatement:
	T_CASE expression ':' statements
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		CaseStatement *caseStatement = new CaseStatement(expression);
		for (int i = 0; i < statementListCollector.back().size(); i++)
			caseStatement->addStatement(statementListCollector.back()[i]);
		statementListCollector.pop_back();
		statementCollector.push_back(caseStatement);
	}
	| T_DEFAULT ':' statements
	{
		CaseStatement *defaultStatement = new CaseStatement();
		for (int i = 0; i < statementListCollector.back().size(); i++)
			defaultStatement->addStatement(statementListCollector.back()[i]);
		statementListCollector.pop_back();
		statementCollector.push_back(defaultStatement);
	}
	;

caseStatements:
	caseStatements caseStatement
	{
		CaseStatement *caseStatement = (CaseStatement *)statementCollector.back();
		statementListCollector.back().push_back(caseStatement);
		statementCollector.pop_back();
	}
	| caseStatement
	{
		vector<Statement *> v;
		CaseStatement *caseStatement = (CaseStatement *)statementCollector.back();
		v.push_back(caseStatement);
		statementCollector.pop_back();
		statementListCollector.push_back(v);
	}
	;

declaration:
	T_CONST T_IDENTIFIER '=' T_NUMBER ';'
	{
		Declaration *declaration = new Declaration(DECLARATION_CONST, $2, $4);
		declarationCollector.push_back(declaration);
	}
	| T_VAR T_IDENTIFIER '@' T_NUMBER ';'
	{
		Declaration *declaration = new Declaration(DECLARATION_VAR, $2, $4);
		declarationCollector.push_back(declaration);
	}
	| T_VAR T_IDENTIFIER ';'
	{
		Declaration *declaration = new Declaration(DECLARATION_VAR, $2);
		declarationCollector.push_back(declaration);
	}
	;

declarations:
	declarations declaration
	{
		Declaration *declaration = declarationCollector.back();
		declarationListCollector.back().push_back(declaration);
		declarationCollector.pop_back();
	}
	| /* nothing */
	{
		vector<Declaration *> v;
		declarationListCollector.push_back(v);
	}
	;

expression:
	T_IDENTIFIER
	{
		Expression *expression = new VariableExpression($1);
		expressionCollector.push_back(expression);
	}
	| T_NUMBER
	{
		Expression *expression = new ConstantExpression($1);
		expressionCollector.push_back(expression);
	}
	| T_STRING
	{
		Expression *expression = new StringExpression($1);
		expressionCollector.push_back(expression);
	}
	| T_IDENTIFIER '=' expression
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		AssignmentExpression *assignmentExpression = new AssignmentExpression(new VariableExpression($1), expression);
		expressionCollector.push_back(assignmentExpression);
	}
	| '(' expression ')'
	| '-' expression %prec T_UMINUS
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		expression = Expression::simplifyUnaryExpression(EXPRESSION_UMINUS, expression);
		expressionCollector.push_back(expression);
	}
	| '!' expression %prec T_NOT
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		expression = Expression::simplifyUnaryExpression(EXPRESSION_NOT, expression);
		expressionCollector.push_back(expression);
	}
	| expression '+' expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_ADD, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression '-' expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_SUB, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression '/' expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_DIV, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression '*' expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_MUL, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression '<' expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_LT, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression '>' expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_GT, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression '&' expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_BAND, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression '|' expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_BOR, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression T_LE expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_LE, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression T_GE expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_GE, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression T_NE expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_NE, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression T_EQ expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_EQ, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression T_LAND expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_LAND, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| expression T_LOR expression
	{
		Expression *expression2 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression1 = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *expression = Expression::simplifyBinaryExpression(EXPRESSION_LOR, expression1, expression2);
		expressionCollector.push_back(expression);
	}
	| T_INC T_IDENTIFIER
	{
		Expression *expression = new UnaryExpression(EXPRESSION_PREINC, new VariableExpression($2));
		expressionCollector.push_back(expression);
	}
	| T_IDENTIFIER T_INC
	{
		Expression *expression = new UnaryExpression(EXPRESSION_POSTINC, new VariableExpression($1));
		expressionCollector.push_back(expression);
	}
	| T_DEC T_IDENTIFIER
	{
		Expression *expression = new UnaryExpression(EXPRESSION_PREDEC, new VariableExpression($2));
		expressionCollector.push_back(expression);
	}
	| T_IDENTIFIER T_DEC
	{
		Expression *expression = new UnaryExpression(EXPRESSION_POSTDEC, new VariableExpression($1));
		expressionCollector.push_back(expression);
	}
	| callExpression
	;

file:
	file fileItem
	| /* nothing */
	;

fileItem:
	declaration
	{
		Declaration *declaration = declarationCollector.back();
		declarations.push_back(declaration);
		declarationCollector.pop_back();
	}
	| function
	;

function:
	T_FUNCTION T_IDENTIFIER '(' args ')' blockStatement
	{
		BlockStatement *blockStatement = (BlockStatement *)statementCollector.back();
		statementCollector.pop_back();
		Function *function = new Function(FUNCTION_NORMAL, $2, blockStatement);
		for (int i = 0; i < declarationListCollector.back().size(); i++)
			function->addArgument(declarationListCollector.back()[i]);
		declarationListCollector.pop_back();
		functions.push_back(function);
	}
	| T_INLINE T_FUNCTION T_IDENTIFIER '(' args ')' blockStatement
	{
		BlockStatement *blockStatement = (BlockStatement *)statementCollector.back();
		statementCollector.pop_back();
		Function *function = new Function(FUNCTION_INLINED, $3, blockStatement);
		for (int i = 0; i < declarationListCollector.back().size(); i++)
			function->addArgument(declarationListCollector.back()[i]);
		declarationListCollector.pop_back();
		functions.push_back(function);
	}
	| T_THREAD T_IDENTIFIER '(' args ')' blockStatement
	{
		BlockStatement *blockStatement = (BlockStatement *)statementCollector.back();
		statementCollector.pop_back();
		Function *function = new Function(FUNCTION_THREAD, $2, blockStatement);
		for (int i = 0; i < declarationListCollector.back().size(); i++)
			function->addArgument(declarationListCollector.back()[i]);
		declarationListCollector.pop_back();
		functions.push_back(function);
	}
	;

parameters:
	parameters ',' expression
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		expressionListCollector.back().push_back(expression);
	}
	| expression
	{
		vector<Expression *> v;
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		v.push_back(expression);
		expressionListCollector.push_back(v);
	}
	| /* nothing */
	{
		vector<Expression *> v;
		expressionListCollector.push_back(v);
	}
	;

statement:
	blockStatement
	| expression ';'
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		ExpressionStatement *expressionStatement = new ExpressionStatement(expression);
		statementCollector.push_back(expressionStatement);
	}
	| T_IF '(' expression ')' statement
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		Statement *statement = statementCollector.back();
		statementCollector.pop_back();
		IfStatement *ifStatement = new IfStatement(expression, statement);
		statementCollector.push_back(ifStatement);
	}
	| T_IF '(' expression ')' statement T_ELSE statement
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		Statement *elseStatement = statementCollector.back();
		statementCollector.pop_back();
		Statement *ifStatement = statementCollector.back();
		statementCollector.pop_back();
		IfElseStatement *ifElseStatement = new IfElseStatement(expression, ifStatement, elseStatement);
		statementCollector.push_back(ifElseStatement);
	}
	| T_SWITCH '(' expression ')' '{' caseStatements '}'
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		SwitchStatement *switchStatement = new SwitchStatement(expression);
		for (int i = 0; i < statementListCollector.back().size(); i++)
			switchStatement->addCaseStatement((CaseStatement *)statementListCollector.back()[i]);
		statementListCollector.pop_back();
		statementCollector.push_back(switchStatement);
	}
	| T_FOR '(' expression ';' expression ';' expression ')' statement
	{
		Expression *increaseExpression = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *conditionExpression = expressionCollector.back();
		expressionCollector.pop_back();
		Expression *initExpression = expressionCollector.back();
		expressionCollector.pop_back();
		Statement *statement = statementCollector.back();
		statementCollector.pop_back();
		ForStatement *forStatement = new ForStatement(initExpression, conditionExpression, increaseExpression, statement);
		statementCollector.push_back(forStatement);
	}
	| T_WHILE '(' expression ')' statement
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		Statement *statement = statementCollector.back();
		statementCollector.pop_back();
		WhileStatement *whileStatement = new WhileStatement(expression, statement);
		statementCollector.push_back(whileStatement);
	}
	| T_CONTINUE ';'
	{
		ContinueStatement *continueStatement = new ContinueStatement();
		statementCollector.push_back(continueStatement);
	}
	| T_BREAK ';'
	{
		BreakStatement *breakStatement = new BreakStatement();
		statementCollector.push_back(breakStatement);
	}
	| T_RETURN expression ';'
	{
		Expression *expression = expressionCollector.back();
		expressionCollector.pop_back();
		ReturnStatement *returnStatement = new ReturnStatement(expression);
		statementCollector.push_back(returnStatement);
	}
	| T_RETURN ';'
	{
		ReturnStatement *returnStatement = new ReturnStatement();
		statementCollector.push_back(returnStatement);
	}
	| T_ASSEMBLY '{' assemblyTokens '}'
	{
		AssemblyStatement *assemblyStatement = new AssemblyStatement();
		for (int i = 0; i < assemblyTokens.size(); i++)
			assemblyStatement->addToken(assemblyTokens[i]);
		assemblyTokens.clear();
		statementCollector.push_back(assemblyStatement);
	}
	;

statements:
	statements statement
	{
		Statement *statement = statementCollector.back();
		statementListCollector.back().push_back(statement);
		statementCollector.pop_back();
	}
	| /* nothing */
	{
		vector<Statement *> v;
		statementListCollector.push_back(v);
	}
	;

%%

void yyerror(vector<Declaration *> &declarations, vector<Function *> &functions, string s)
{
	// Clean nodes which would otherwise cause a memory leak
	for (int i = 0; i < declarationCollector.size(); i++)
		delete declarationCollector[i];
	for (int i = 0; i < expressionCollector.size(); i++)
		delete expressionCollector[i];
	for (int i = 0; i < statementCollector.size(); i++)
		delete statementCollector[i];
	for (int i = 0; i < declarationListCollector.size(); i++)
		for (int j = 0; j < declarationListCollector[i].size(); j++)
			delete declarationListCollector[i][j];
	for (int i = 0; i < expressionListCollector.size(); i++)
		for (int j = 0; j < expressionListCollector[i].size(); j++)
			delete expressionListCollector[i][j];
	for (int i = 0; i < statementListCollector.size(); i++)
		for (int j = 0; j < statementListCollector[i].size(); j++)
			delete statementListCollector[i][j];

	Log::getInstance().write(LOG_INFO, "Line %u: %s\n", yylineno, s.c_str());
}

