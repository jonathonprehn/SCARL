
%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scarlast.h"
#include "visitors.h"
#include "scarl_symboltable.h"

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

//the symbol table for tracking program constructs. type checking. This is the parent
//symbol table - the global symbol table
extern struct scarl_symbol_table *symbol_table;

extern struct scarl_symbol_table *current_symbol_table;

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
	NON_TERMINAL_PROGRAM_func(1, $1); //this pushes the program onto the node stack
} 

statement_list : statement {
	$$ = NON_TERMINAL_STATEMENT_LIST_func(1, $1);
}
				 
statement_list : statement statement_list {
	//add the statement to the existing statement list
	$$ = NON_TERMINAL_STATEMENT_LIST_func(2, $2, $1);
}		 

statement : device_declarator_statement {
	$$ = $1; //pass through
}
			
statement :	primitive_definition_statement {
	$$ = $1; //pass through
}
			
statement: function_definition_statement {
	$$ = $1; //pass through
}

block_statement : LBRACE statement_list_block_level RBRACE {
	struct ast_node *block_statement_node = NON_TERMINAL_BLOCK_STATEMENT_func(1, $2); //converts the type to a block statement
	//closing out this scope
	block_statement_node->symbol_table_value = current_symbol_table;
	
	//frame size should be correctly calculated for the child symbol table
	current_symbol_table->parentTable->frameSize += current_symbol_table->frameSize;

	current_symbol_table = current_symbol_table->parentTable; //bring it back up a level
	$$ = block_statement_node;
}

statement_list_block_level : statement_block_level {
	//create the statement list node and add the statement to it
	$$ = NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(1, $1);
}
						    
statement_list_block_level : statement_block_level statement_list_block_level {
	//add the statement to the existing statement list
	$$ = NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(2, $2, $1);
}

statement_block_level : primitive_definition_statement { 
	$$ = $1; //pass through
}
						
statement_block_level : block_statement {
	$$ = $1; //pass through
}
						
statement_block_level : variable_set_statement {
	$$ = $1; //pass through
}
						
statement_block_level : function_invocation_statement {
	$$ = $1; //pass through
}
						
statement_block_level : if_block_statement {
	$$ = $1; //pass through
}

statement_block_level : while_block_statement {
	$$ = $1; //pass through
}

device_declarator_statement : device_type IDENTIFIER SEMICOLON {
	struct ast_node *device_declarator_node = NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func(2, $1, TERMINAL_IDENTIFIER_func(0));
	int device_type = 0;
	char *ident = NULL;
	struct ast_node *cur_node = device_declarator_node->leftmostChild;
	device_type = cur_node->int_value;
	cur_node = cur_node->nextSibling;
	ident = _strdup(cur_node->str_value);
	
	if (lookup(current_symbol_table, ident, NULL, 0) == NULL) {
		declare_symbol_table_entry(
				current_symbol_table, 
				create_symbol_table_entry(
					ident,
					device_type,
					NULL,
					0,
					NULL
				));
	} else {
		fprintf(stderr, "Duplicate identifiers \'%s\' (near line %i)\n", ident, lineNumber);
		exit(0);
	}

	$$ = device_declarator_node;
}

primitive_declarator : primitive_type IDENTIFIER {
	$$ = NON_TERMINAL_PRIMITIVE_DECLARATOR_func(2, $1, TERMINAL_IDENTIFIER_func(0));
}

primitive_definition_statement : primitive_declarator EQ expression SEMICOLON {
	struct ast_node *prim_def_node = NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func(2, $1, $3);
		
	struct ast_node *prim_decl_node = prim_def_node->leftmostChild;
	struct ast_node *prim_info_node = prim_decl_node->leftmostChild;
	int ident_type = prim_info_node->int_value;
	char *ident = _strdup(prim_info_node->nextSibling->str_value);
	
	//add this identifier to the symbol table

	if (lookup(current_symbol_table, ident, NULL, 0) == NULL) {
		declare_symbol_table_entry(
				current_symbol_table, 
				create_symbol_table_entry(
					ident,
					ident_type,
					NULL,
					0,
					NULL
				));
	} else {
		fprintf(stderr, "Duplicate identifiers \'%s\' (near line %i)\n", ident, lineNumber);
		exit(0);
	}

	prim_info_node = prim_decl_node->nextSibling;
	//now the prim_info_node is pointing to the expression that
	//this declarator is initially set to

	//TO DO: expression assignment to definition code
	

	$$ = prim_def_node;
}

function_definition_statement : primitive_declarator LPAREN formal_parameter_list RPAREN block_statement {
	struct ast_node *function_def_node = NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func(3, $1, $3, $5);

	struct ast_node *prim_decl_node = function_def_node->leftmostChild;
	struct ast_node *info_node = prim_decl_node->leftmostChild;
	int return_type = info_node->int_value;
	char *ident = _strdup(info_node->nextSibling->str_value);
	info_node = prim_decl_node->nextSibling; //now we are pointing to the formal parameter list
	
	int parameterCounter = 0;
	int *paramListConstruct = NULL;
	formal_parameter_node_to_parameter_list(info_node, &parameterCounter, &paramListConstruct);

	//add this identifier to the symbol table

	if (lookup(current_symbol_table, ident, paramListConstruct, parameterCounter) == NULL) {
		declare_symbol_table_entry(
				current_symbol_table, 
				create_symbol_table_entry(
					ident,
					return_type,
					paramListConstruct,
					parameterCounter,
					info_node->nextSibling->symbol_table_value
				));
	} else {
		fprintf(stderr, "Duplicate function definition \'%s\' (near line %i)\n", ident, lineNumber);
		exit(0);
	}

	$$ = function_def_node;
}

variable_set_statement : IDENTIFIER EQ expression SEMICOLON {
	$$ = NON_TERMINAL_VARIABLE_SET_STATEMENT_func(2, TERMINAL_IDENTIFIER_func(0), $3);
}

function_invocation : IDENTIFIER LPAREN parameter_list RPAREN {
	$$ = NON_TERMINAL_FUNCTION_INVOCATION_func(2, TERMINAL_IDENTIFIER_func(0), $3);
}

function_invocation_statement : function_invocation SEMICOLON {
	$$ = NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func(1, $1);
}

if_block_statement : IF LPAREN expression RPAREN block_statement {
	$$ = NON_TERMINAL_IF_BLOCK_STATEMENT_func(2, $3, $5);
}

if_block_statement : IF LPAREN expression RPAREN block_statement ELSE block_statement { 
	$$ = NON_TERMINAL_IF_BLOCK_STATEMENT_func(3, $3, $5, $7);
}

while_block_statement : WHILE LPAREN expression RPAREN block_statement { 
	//expression and block statement
	$$ = NON_TERMINAL_WHILE_BLOCK_STATEMENT_func(2, $3, $5);
}

formal_parameter_list :     {
	//empty formal parameter list
	$$ = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(0);
}
						
formal_parameter_list : primitive_declarator { 
	$$ = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(1, $1);
} 
						
formal_parameter_list : primitive_declarator COMMA formal_parameter_list { 
	$$ = NON_TERMINAL_FORMAL_PARAMETER_LIST_func(2, $3, $1);
}

parameter_list :      { 
	//empty parameter list
	$$ = NON_TERMINAL_PARAMETER_LIST_func(0);
}

parameter_list : expression { 
	$$ = NON_TERMINAL_PARAMETER_LIST_func(1, $1);
}

parameter_list : expression COMMA parameter_list { 
	$$ = NON_TERMINAL_PARAMETER_LIST_func(2, $3, $1); //add to existing parameter list
}

expression : logical_expression { 
	$$ = $1;
}

logical_expression : logical_and_expression { 
	$$ = $1;
}
					 
logical_expression : logical_expression OR logical_and_expression {
	//     logical_expression && logical_and_expression
	//     logical_expression should be on the LEFT
	//     logical_and_expression should be on the RIGHT
	//     OR should be the parent node
	$$ = NON_TERMINAL_LOGICAL_EXPRESSION_func(3, $1, TERMINAL_OR_func(0), $3);
}

logical_and_expression : equality_expression { 
	$$ = $1; //pass through
} 

logical_and_expression : logical_and_expression AND equality_expression { 
	//     logical_and_expression && equality_expression
	//     logical_and_expression should be on the LEFT
	//     equality_expression should be on the RIGHT
	//     AND should be the parent node
	$$ = NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(3, $1, TERMINAL_AND_func(0), $3);

} 

equality_expression : relational_expression { 
	$$ = $1; //pass through
}

equality_expression : equality_expression DBL_EQ relational_expression { 
	//     equality_expression == relational_expression
	//     equality_expression should be on the LEFT
	//     relational_expression should be on the RIGHT
	//     NOT_EQ should be the parent node
	$$ = NON_TERMINAL_EQUALITY_EXPRESSION_func(3, $1, TERMINAL_DBL_EQ_func(0), $3);
}
					  
equality_expression : equality_expression NOT_EQ relational_expression { 
	//     equality_expression != relational_expression
	//     equality_expression should be on the LEFT
	//     relational_expression should be on the RIGHT
	//     NOT_EQ should be the parent node
	$$ = NON_TERMINAL_EQUALITY_EXPRESSION_func(3, $1, TERMINAL_NOT_EQ_func(0), $3);
}

relational_expression : bool_expression { 
	$$ = $1; //pass through
}

relational_expression : relational_expression GTR bool_expression { 
	//     relational_expression > bool_expression
	//     relational_expression should be on the LEFT
	//     bool_expression should be on the RIGHT
	//     GTR should be the parent node
	$$ = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, $1, TERMINAL_GTR_func(0), $3);
}
						
relational_expression : relational_expression LESS bool_expression { 
	//     relational_expression < bool_expression
	//     relational_expression should be on the LEFT
	//     bool_expression should be on the RIGHT
	//     LESS should be the parent node
	$$ = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, $1, TERMINAL_LESS_func(0), $3);
}
						
relational_expression : relational_expression GTR_EQ bool_expression { 
	//     relational_expression >= bool_expression
	//     relational_expression should be on the LEFT
	//     bool_expression should be on the RIGHT
	//     GTR_EQ should be the parent node
	$$ = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, $1, TERMINAL_GTR_EQ_func(0), $3);
}
						
relational_expression : relational_expression LESS_EQ bool_expression { 
	//     relational_expression <= bool_expression
	//     relational_expression should be on the LEFT
	//     bool_expression should be on the RIGHT
	//     LESS_EQ should be the parent node
	$$ = NON_TERMINAL_RELATIONAL_EXPRESSION_func(3, $1, TERMINAL_LESS_EQ_func(0), $3);
}

bool_expression : arithmetic_expression { 
	$$ = $1; //pass through
}

bool_expression : BANG arithmetic_expression { 
	$$ = NON_TERMINAL_BOOL_EXPRESSION_func(2, TERMINAL_BANG_func(0), $2);
}

arithmetic_expression : arithmetic_factor { 
	$$ = $1; //pass through
}

arithmetic_expression : arithmetic_expression PLUS arithmetic_factor { 
	//     arithmetic_expression - arithmetic_factor
	//     arithmetic_expression should be on the LEFT
	//     arithmetic_factor should be on the RIGHT
	//     MINUS should be the parent node
	$$ = NON_TERMINAL_ARITHMETIC_EXPRESSION_func(3, $1, TERMINAL_PLUS_func(0), $3);
}
						
arithmetic_expression : arithmetic_expression MINUS arithmetic_factor { 
	//     arithmetic_expression - arithmetic_factor
	//     arithmetic_expression should be on the LEFT
	//     arithmetic_factor should be on the RIGHT
	//     MINUS should be the parent node
	$$ = NON_TERMINAL_ARITHMETIC_EXPRESSION_func(3, $1, TERMINAL_MINUS_func(0), $3);
}
						
arithmetic_factor : arithmetic_unary { 
	$$ = $1; //pass through
}
					
arithmetic_factor : arithmetic_factor STAR arithmetic_unary { 
	//     arithmetic_factor * arithmetic_unary
	//     arithmetic_factor should be on the LEFT
	//     arithmetic_unary should be on the RIGHT
	//     STAR should be the parent node
	$$ = NON_TERMINAL_ARITHMETIC_FACTOR_func(3, $1, TERMINAL_STAR_func(0), $3);
}
					
arithmetic_factor : arithmetic_factor SLASH arithmetic_unary { 
	//     arithmetic_factor / arithmetic_unary
	//     arithmetic_factor should be on the LEFT
	//     arithmetic_unary should be on the RIGHT
	//     SLASH should be the parent node
	$$ = NON_TERMINAL_ARITHMETIC_FACTOR_func(3, $1, TERMINAL_SLASH_func(0), $3);
}
					
arithmetic_unary : unit { 
	$$ = $1; //straight pass
}

arithmetic_unary : MINUS arithmetic_unary { 
	$$ = NON_TERMINAL_ARITHMETIC_UNARY_func(2, TERMINAL_MINUS_func(0), $2);
}
				   
arithmetic_unary : LPAREN arithmetic_expression RPAREN { 
	$$ = $2; //pass the arithmetic expression as an arithmetic unary
}
				    
unit : IDENTIFIER { 
	$$ = TERMINAL_IDENTIFIER_func(0); //receives identifier from ident_stack
}

unit : integer_value { 
	$$ = $1; //straight pass
}

unit : bool_value { 
	$$ = $1; //straight pass
}

unit : function_invocation { 
	$$ = $1; //straight pass
}

integer_value : DECIMAL { 
	NON_TERMINAL_INTEGER_VALUE_func(0); //for debug printing

	char *str = lastTokenText;
	$$ = TERMINAL_DECIMAL_func(1, str);
} 

integer_value : OCTAL { 
	NON_TERMINAL_INTEGER_VALUE_func(0); //for debug printing

	char *str = lastTokenText;
	$$ = TERMINAL_OCTAL_func(1, str);
}

integer_value : HEX { 
	NON_TERMINAL_INTEGER_VALUE_func(0); //for debug printing

	char *str = lastTokenText;
	$$ = TERMINAL_HEX_func(1, str);
}

integer_value : BINARY { 
	NON_TERMINAL_INTEGER_VALUE_func(0); //for debug printing

	char *str = lastTokenText;
	$$ = TERMINAL_BINARY_func(1, str);
}

bool_value : TRUE { 
	$$ = NON_TERMINAL_BOOL_VALUE_func(1, 1); // 1 being true
}

bool_value : FALSE { 
	$$ = NON_TERMINAL_BOOL_VALUE_func(1, 0); // 0 being false
}

primitive_type : BOOL {
	$$ = NON_TERMINAL_PRIMITIVE_TYPE_func(1, BOOL);
}

primitive_type : INT { 
	$$ = NON_TERMINAL_PRIMITIVE_TYPE_func(1, INT);
}

primitive_type : CHAR { 
	$$ = NON_TERMINAL_PRIMITIVE_TYPE_func(1, CHAR);
}

primitive_type : POINTER { 
	$$ = NON_TERMINAL_PRIMITIVE_TYPE_func(1, POINTER);
}

primitive_type : VOID  { 
	$$ = NON_TERMINAL_PRIMITIVE_TYPE_func(1, VOID);
}

device_type : LIGHT_ACTUATOR { 
	$$ = NON_TERMINAL_DEVICE_TYPE_func(1, LIGHT_ACTUATOR);
}

device_type : SERVO_ACTUATOR { 
	$$ = NON_TERMINAL_DEVICE_TYPE_func(1, SERVO_ACTUATOR);
}

device_type : SOUND_SENSOR { 
	$$ = NON_TERMINAL_DEVICE_TYPE_func(1, SOUND_SENSOR);
}

device_type : LIGHT_SENSOR { 
	$$ = NON_TERMINAL_DEVICE_TYPE_func(1, LIGHT_SENSOR);
}

device_type : DISTANCE_SENSOR {
	$$ = NON_TERMINAL_DEVICE_TYPE_func(1, DISTANCE_SENSOR);
}

device_type : TEMPERATURE_SENSOR { 
	$$ = NON_TERMINAL_DEVICE_TYPE_func(1, TEMPERATURE_SENSOR);
}

%%

void yyerror(char *s) {
	fprintf(stderr, "%s at line %i near \'%s\'\n", s, lineNumber, lastTokenText);
}
