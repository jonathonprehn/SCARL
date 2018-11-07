
%{

#include <stdio.h>

#include "scarlast.h"
#include "visitors.h"

int yylex(void);
void yyerror(char *);

int yydebug = 1;

//for counting line numbers. Lines are incremented in scarl.l
extern unsigned lineNumber;
//handled in scarl.l. for hinting at where error occured
extern char *lastTokenText;

//for performing actions on the code file
//for the compiling unit, this is intermediatary code
extern FILE *codeFile;

//for building the tree that will be used for generating the code later on
extern struct ast_node *syntax_tree;

//the stack to be used when creating nonterminal sub-ASTs
extern struct ast_node_stack *node_stack;
extern struct ast_node_stack *ident_stack;
%}

%token IDENTIFIER PLUS MINUS STAR SLASH BANG 
%token BOOL INT CHAR POINTER VOID LPAREN RPAREN 
%token GTR LESS GTR_EQ LESS_EQ DBL_EQ EQ 
%token NOT_EQ OR AND COMMA SEMICOLON IF ELSE
%token WHILE LBRACE RBRACE DECIMAL OCTAL HEX
%token BINARY LIGHT_ACTUATOR SERVO_ACTUATOR
%token SOUND_SENSOR LIGHT_SENSOR DISTANCE_SENSOR
%token TEMPERATURE_SENSOR TRUE FALSE

%%

program : statement_list { 
	NON_TERMINAL_PROGRAM_func(1, NULL);
} 

statement_list : statement {
	NON_TERMINAL_STATEMENT_LIST_func(1, NULL);
}
				 
statement_list : statement statement_list {
	NON_TERMINAL_STATEMENT_LIST_func(2, NULL);
}		 

statement : device_declarator_statement {
	NON_TERMINAL_STATEMENT_func(1, NULL);
}
			
statement :	primitive_definition_statement {
	NON_TERMINAL_STATEMENT_func(1, NULL);
}
			
statement: function_definition_statement {
	NON_TERMINAL_STATEMENT_func(1, NULL);
}

block_statement : LBRACE statement_list_block_level RBRACE {
	//block statement with constructed statement list on top of it
	NON_TERMINAL_BLOCK_STATEMENT_func(1, NULL);
}

statement_list_block_level : statement_block_level {
	NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(1, NULL);
}
						    
statement_list_block_level : statement_block_level statement_list_block_level {
	NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(2, NULL);
}

statement_block_level : primitive_definition_statement { 
	NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(1, NULL);
}
						
statement_block_level : block_statement {
	NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(1, NULL);
}
						
statement_block_level : variable_set_statement {
	NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(1, NULL);
}
						
statement_block_level : function_invocation_statement {
	NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(1, NULL);
}
						
statement_block_level : if_block_statement {
	NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(1, NULL);
}

statement_block_level : while_block_statement {
	NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(1, NULL);
}

device_declarator_statement : device_type IDENTIFIER SEMICOLON {
	NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func(2, NULL);
}

primitive_declarator : primitive_type IDENTIFIER {
	NON_TERMINAL_PRIMITIVE_DECLARATOR_func(2, NULL);
}

primitive_definition_statement : primitive_declarator EQ expression SEMICOLON {
	NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func(2, NULL);
}

function_definition_statement : primitive_declarator LPAREN formal_parameter_list RPAREN block_statement {
	NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func(3, NULL);
}

variable_set_statement : IDENTIFIER EQ expression SEMICOLON {
	NON_TERMINAL_VARIABLE_SET_STATEMENT_func(2, NULL);
}

function_invocation : IDENTIFIER LPAREN parameter_list RPAREN {
	//ident stack has the identifier to use
	NON_TERMINAL_FUNCTION_INVOCATION_func(1, NULL);
}

function_invocation_statement : function_invocation SEMICOLON {
	NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func(1, NULL);
}

if_block_statement : IF LPAREN expression RPAREN block_statement {
	NON_TERMINAL_IF_BLOCK_STATEMENT_func(2, NULL);
}

if_block_statement : IF LPAREN expression RPAREN block_statement ELSE block_statement { 
	NON_TERMINAL_IF_BLOCK_STATEMENT_func(3, NULL);
}

while_block_statement : WHILE LPAREN expression RPAREN block_statement { 
	NON_TERMINAL_WHILE_BLOCK_STATEMENT_func(2, NULL);
}

formal_parameter_list :     {
	NON_TERMINAL_FORMAL_PARAMETER_LIST_func(0, NULL);
}
						
formal_parameter_list : primitive_declarator { 
	NON_TERMINAL_FORMAL_PARAMETER_LIST_func(1, NULL);
} 
						
formal_parameter_list : primitive_declarator COMMA formal_parameter_list { 
	NON_TERMINAL_FORMAL_PARAMETER_LIST_func(2, NULL);
}

parameter_list :      { 
	NON_TERMINAL_PARAMETER_LIST_func(0, NULL);
}

parameter_list : expression { 
	NON_TERMINAL_PARAMETER_LIST_func(1, NULL);
}

parameter_list : expression COMMA parameter_list { 
	NON_TERMINAL_PARAMETER_LIST_func(2, NULL);
}

expression : logical_expression { 
	NON_TERMINAL_EXPRESSION_func(1, NULL);
}

logical_expression : logical_and_expression { 
	NON_TERMINAL_LOGICAL_EXPRESSION_func(1, NULL);
}
					 
logical_expression : logical_expression OR logical_and_expression {
	TERMINAL_OR_func(0, NULL);
	NON_TERMINAL_LOGICAL_EXPRESSION_func(3, NULL);
}

logical_and_expression : equality_expression { 
	NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(1, NULL);
} 

logical_and_expression : logical_and_expression AND equality_expression { 
	TERMINAL_AND_func(0, NULL);
	NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(3, NULL);
} 

equality_expression : relational_expression { 
	NON_TERMINAL_EQUALITY_EXPRESSION_func(1, NULL);
}

equality_expression : equality_expression DBL_EQ relational_expression { 
	TERMINAL_DBL_EQ_func(0, NULL);
	NON_TERMINAL_EQUALITY_EXPRESSION_func(3, NULL);
}
					  
equality_expression : equality_expression NOT_EQ relational_expression { 
	TERMINAL_NOT_EQ_func(0, NULL);
	NON_TERMINAL_EQUALITY_EXPRESSION_func(3, NULL);
}

relational_expression : bool_expression { 
	NON_TERMINAL_RELATIONAL_EXPRESSION_func(1, NULL);
}

relational_expression : relational_expression GTR bool_expression { 
	TERMINAL_GTR_func(1, NULL);
	NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, NULL);
}
						
relational_expression : relational_expression LESS bool_expression { 
	TERMINAL_LESS_func(1, NULL);
	NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, NULL);
}
						
relational_expression : relational_expression GTR_EQ bool_expression { 
	TERMINAL_GTR_EQ_func(1, NULL);
	NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, NULL);
}
						
relational_expression : relational_expression LESS_EQ bool_expression { 
	TERMINAL_LESS_EQ_func(1, NULL);
	NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, NULL);
}

bool_expression : arithmetic_expression { 
	NON_TERMINAL_BOOL_EXPRESSION_func(1, NULL);
}

bool_expression : BANG arithmetic_expression { 
	TERMINAL_BANG_func(0, NULL);
	NON_TERMINAL_BOOL_EXPRESSION_func(2, NULL);
}

arithmetic_expression : arithmetic_factor { 
	NON_TERMINAL_ARITHMETIC_EXPRESSION_func(1, NULL);
}

arithmetic_expression : arithmetic_expression PLUS arithmetic_factor { 
	TERMINAL_PLUS_func(0, NULL);
	NON_TERMINAL_ARITHMETIC_EXPRESSION_func(3, NULL);
}
						
arithmetic_expression : arithmetic_expression MINUS arithmetic_factor { 
	TERMINAL_MINUS_func(0, NULL);
	NON_TERMINAL_ARITHMETIC_EXPRESSION_func(3, NULL);
}
						
arithmetic_factor : arithmetic_unary { 
	//there should be an arithmetic unary on the stack already
	NON_TERMINAL_ARITHMETIC_FACTOR_func(1, NULL);
}
					
arithmetic_factor : arithmetic_factor STAR arithmetic_unary { 
	//there should be a factor on the stack already
	TERMINAL_STAR_func(0, NULL);
	NON_TERMINAL_ARITHMETIC_FACTOR_func(3, NULL);
}
					
arithmetic_factor : arithmetic_factor SLASH arithmetic_unary { 
	//there should be a factor on the stack already
	TERMINAL_SLASH_func(0, NULL);
	NON_TERMINAL_ARITHMETIC_FACTOR_func(3, NULL);
}
					
arithmetic_unary : unit { 
	NON_TERMINAL_ARITHMETIC_UNARY_func(1, NULL);
}

arithmetic_unary : MINUS arithmetic_unary { 
	NON_TERMINAL_ARITHMETIC_UNARY_func(2, NULL);
}
				   
arithmetic_unary : LPAREN arithmetic_expression RPAREN { 
	NON_TERMINAL_ARITHMETIC_UNARY_func(1, NULL); //expect an arithmetic expression on the stack
}
				    
unit : IDENTIFIER { 
	NON_TERMINAL_UNIT_func(2, NULL); //pop current node and add it to a unit node
}

unit : integer_value { 
	NON_TERMINAL_UNIT_func(1, NULL); //pop current node and add it to a unit node
}

unit : bool_value { 
	NON_TERMINAL_UNIT_func(1, NULL); //pop current node and add it to a unit node
}

unit : function_invocation { 
	NON_TERMINAL_UNIT_func(1, NULL); //pop current node and add it to a unit node
}

integer_value : DECIMAL { 
	char *str = lastTokenText;
	TERMINAL_DECIMAL_func(1, &str);
	NON_TERMINAL_INTEGER_VALUE_func(0, NULL);
} 

integer_value : OCTAL { 
	char *str = lastTokenText;
	TERMINAL_OCTAL_func(1, &str);
	NON_TERMINAL_INTEGER_VALUE_func(0, NULL);
}

integer_value : HEX { 
	char *str = lastTokenText;
	TERMINAL_HEX_func(1, &str);
	NON_TERMINAL_INTEGER_VALUE_func(0, NULL);
}

integer_value : BINARY { 
	char *str = lastTokenText;
	TERMINAL_BINARY_func(1, &str);
	NON_TERMINAL_INTEGER_VALUE_func(0, NULL);
}

bool_value : TRUE { 
	NON_TERMINAL_BOOL_VALUE_func(TRUE, NULL);
}

bool_value : FALSE { 
	NON_TERMINAL_BOOL_VALUE_func(FALSE, NULL);
}

primitive_type : BOOL {
	//argc is the primitive type
	NON_TERMINAL_PRIMITIVE_TYPE_func(BOOL, NULL);
}

primitive_type : INT { 
	//argc is the primitive type
	NON_TERMINAL_PRIMITIVE_TYPE_func(INT, NULL);
}

primitive_type : CHAR { 
	//argc is the primitive type
	NON_TERMINAL_PRIMITIVE_TYPE_func(CHAR, NULL);
}

primitive_type : POINTER { 
	//argc is the primitive type
	NON_TERMINAL_PRIMITIVE_TYPE_func(POINTER, NULL);
}

primitive_type : VOID  { 
	//argc is the primitive type
	NON_TERMINAL_PRIMITIVE_TYPE_func(VOID, NULL);
}

device_type : LIGHT_ACTUATOR { 
	NON_TERMINAL_DEVICE_TYPE_func(LIGHT_ACTUATOR, NULL);
}

device_type : SERVO_ACTUATOR { 
	NON_TERMINAL_DEVICE_TYPE_func(SERVO_ACTUATOR, NULL);
}

device_type : SOUND_SENSOR { 
	NON_TERMINAL_DEVICE_TYPE_func(SOUND_SENSOR, NULL);
}

device_type : LIGHT_SENSOR { 
	//argc is device type for this function
	NON_TERMINAL_DEVICE_TYPE_func(LIGHT_SENSOR, NULL);
}

device_type : DISTANCE_SENSOR {
	//argc is device type for this function
	NON_TERMINAL_DEVICE_TYPE_func(DISTANCE_SENSOR, NULL);
}

device_type : TEMPERATURE_SENSOR { 
	//argc is device type for this function
	NON_TERMINAL_DEVICE_TYPE_func(TEMPERATURE_SENSOR, NULL);
}

%%

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, lineNumber, lastTokenText);
}
