
#include <stdlib.h>
#include <stdio.h>

#include "scarlast.h"
#include "scarlnodestack.h"

const char *non_terminals_mnemonic[] = {
	"NON_TERMINAL_PROGRAM",
	"NON_TERMINAL_STATEMENT_LIST",
	"NON_TERMINAL_STATEMENT",
	"NON_TERMINAL_BLOCK_STATEMENT",
	"NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL",
	"NON_TERMINAL_STATEMENT_BLOCK_LEVEL",
	"NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT",
	"NON_TERMINAL_PRIMITIVE_DECLARATOR",
	"NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT",
	"NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT",
	"NON_TERMINAL_VARIABLE_SET_STATEMENT",
	"NON_TERMINAL_FUNCTION_INVOCATION",
	"NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT",
	"NON_TERMINAL_IF_BLOCK_STATEMENT",
	"NON_TERMINAL_WHILE_BLOCK_STATEMENT",
	"NON_TERMINAL_FORMAL_PARAMETER_LIST",
	"NON_TERMINAL_PARAMETER_LIST",
	"NON_TERMINAL_EXPRESSION",
	"NON_TERMINAL_LOGICAL_EXPRESSION",
	"NON_TERMINAL_LOGICAL_AND_EXPRESSION",
	"NON_TERMINAL_EQUALITY_EXPRESSION",
	"NON_TERMINAL_RELATIONAL_EXPRESSION",
	"NON_TERMINAL_BOOL_EXPRESSION",
	"NON_TERMINAL_ARITHMETIC_EXPRESSION",
	"NON_TERMINAL_ARITHMETIC_FACTOR",
	"NON_TERMINAL_ARITHMETIC_UNARY",
	"NON_TERMINAL_UNIT",
	"NON_TERMINAL_INTEGER_VALUE",
	"NON_TERMINAL_BOOL_VALUE",
	"NON_TERMINAL_PRIMITIVE_TYPE",
	"NON_TERMINAL_DEVICE_TYPE"
};

const char *scarl_terminals_mnemonic[] = {
	"IDENTIFIER",
	"PLUS",
	"MINUS",
	"STAR",
	"SLASH",
	"BANG",
	"BOOL",
	"INT",
	"CHAR",
	"POINTER",
	"VOID",
	"LPAREN",
	"RPAREN",
	"GTR",
	"LESS",
	"GTR_EQ",
	"LESS_EQ",
	"DBL_EQ",
	"EQ",
	"NOT_EQ",
	"OR",
	"AND",
	"COMMA",
	"SEMICOLON",
	"IF",
	"ELSE",
	"WHILE",
	"LBRACE",
	"RBRACE",
	"DECIMAL",
	"OCTAL",
	"HEX",
	"BINARY",
	"LIGHT_ACTUATOR",
	"SERVO_ACTUATOR",
	"SOUND_SENSOR",
	"LIGHT_SENSOR",
	"DISTANCE_SENSOR",
	"TEMPERATURE_SENSOR",
	"TRUE",
	"FALSE"
};
const char *get_non_terminal_mnemonic(int non_terminal_type) {
	return non_terminals_mnemonic[non_terminal_type-NON_TERMINAL_OFFSET_VAL-1];
}

const char *get_terminal_mnemonic(int terminal_type) {
	return scarl_terminals_mnemonic[terminal_type-IDENTIFIER];
}

struct ast_node * create_node(struct ast_node *parent, int type_flag)
{
	struct ast_node *nod = (struct ast_node*)malloc(sizeof(struct ast_node));
	nod->leftmostChild = NULL;
	nod->nextSibling = NULL;
	nod->parent = NULL;
	nod->type_flag = type_flag;
	nod->int_value = 0;
	nod->str_value = NULL;
	return nod;
}

void destroy_node(struct ast_node * nod)
{
	//first destroy all children
	struct ast_node *next = nod->leftmostChild;

	while (next != NULL) {
		struct ast_node *next_after = next->nextSibling;
		destroy_node(next); //recursive delete
		next = next_after;
	}
	//now destroy the self
	//do not destroy the parent
	if (nod->str_value != NULL) {
		free(nod->str_value);
	}
	free(next);
}

void add_child(struct ast_node * nod, struct ast_node * child)
{
	if (nod->leftmostChild == NULL) {
		nod->leftmostChild = child;
		child->parent = nod;
	}
	else {
		struct ast_node *next = nod->leftmostChild;
		while (next->nextSibling != NULL) {
			next = next->nextSibling;
		}
		next->nextSibling = child;
		child->parent = nod;
	}
}

void add_child_front(struct ast_node * nod, struct ast_node * child)
{
	if (nod->leftmostChild == NULL) {
		nod->leftmostChild = child;
		child->parent = nod;
	}
	else {
		struct ast_node *first = nod->leftmostChild;
		child->nextSibling = first;
		child->parent = nod;
		nod->leftmostChild = child;
	}
}

#define SCARL_NON_TERMINAL_VISITOR_FUNC_TABLE_SIZE 0x20
#define SCARL_TERMINAL_VISITOR_FUNC_TABLE_SIZE 43
#define SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL 257 
#include "visitors.h"

ast_node_visitor_func non_terminal_visitor_func_table[SCARL_NON_TERMINAL_VISITOR_FUNC_TABLE_SIZE];
ast_node_visitor_func terminal_visitor_func_table[SCARL_TERMINAL_VISITOR_FUNC_TABLE_SIZE];

void init_visitor_func_table() {
	non_terminal_visitor_func_table[NON_TERMINAL_PROGRAM-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_PROGRAM_func;
	non_terminal_visitor_func_table[NON_TERMINAL_STATEMENT_LIST-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_STATEMENT_LIST_func;
	non_terminal_visitor_func_table[NON_TERMINAL_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_BLOCK_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_BLOCK_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func;
	non_terminal_visitor_func_table[NON_TERMINAL_STATEMENT_BLOCK_LEVEL-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func;
	non_terminal_visitor_func_table[NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_PRIMITIVE_DECLARATOR-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_PRIMITIVE_DECLARATOR_func;
	non_terminal_visitor_func_table[NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_VARIABLE_SET_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_VARIABLE_SET_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_FUNCTION_INVOCATION-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_FUNCTION_INVOCATION_func;
	non_terminal_visitor_func_table[NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_IF_BLOCK_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_IF_BLOCK_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_WHILE_BLOCK_STATEMENT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_WHILE_BLOCK_STATEMENT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_FORMAL_PARAMETER_LIST-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_FORMAL_PARAMETER_LIST_func;
	non_terminal_visitor_func_table[NON_TERMINAL_PARAMETER_LIST-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_PARAMETER_LIST_func;
	non_terminal_visitor_func_table[NON_TERMINAL_EXPRESSION-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_EXPRESSION_func;
	non_terminal_visitor_func_table[NON_TERMINAL_LOGICAL_EXPRESSION-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_LOGICAL_EXPRESSION_func;
	non_terminal_visitor_func_table[NON_TERMINAL_LOGICAL_AND_EXPRESSION-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_LOGICAL_AND_EXPRESSION_func;
	non_terminal_visitor_func_table[NON_TERMINAL_EQUALITY_EXPRESSION-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_EQUALITY_EXPRESSION_func;
	non_terminal_visitor_func_table[NON_TERMINAL_RELATIONAL_EXPRESSION-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_RELATIONAL_EXPRESSION_func;
	non_terminal_visitor_func_table[NON_TERMINAL_BOOL_EXPRESSION-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_BOOL_EXPRESSION_func;
	non_terminal_visitor_func_table[NON_TERMINAL_ARITHMETIC_EXPRESSION-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_ARITHMETIC_EXPRESSION_func;
	non_terminal_visitor_func_table[NON_TERMINAL_ARITHMETIC_FACTOR-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_ARITHMETIC_FACTOR_func;
	non_terminal_visitor_func_table[NON_TERMINAL_ARITHMETIC_UNARY-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_ARITHMETIC_UNARY_func;
	non_terminal_visitor_func_table[NON_TERMINAL_UNIT-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_UNIT_func;
	non_terminal_visitor_func_table[NON_TERMINAL_INTEGER_VALUE-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_INTEGER_VALUE_func;
	non_terminal_visitor_func_table[NON_TERMINAL_BOOL_VALUE-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_BOOL_VALUE_func;
	non_terminal_visitor_func_table[NON_TERMINAL_PRIMITIVE_TYPE-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_PRIMITIVE_TYPE_func;
	non_terminal_visitor_func_table[NON_TERMINAL_DEVICE_TYPE-NON_TERMINAL_OFFSET_VAL] = NON_TERMINAL_DEVICE_TYPE_func;

	terminal_visitor_func_table[IDENTIFIER - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_IDENTIFIER_func;
	terminal_visitor_func_table[PLUS - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_PLUS_func;
	terminal_visitor_func_table[MINUS - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_MINUS_func;
	terminal_visitor_func_table[STAR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_STAR_func;
	terminal_visitor_func_table[SLASH - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_SLASH_func;
	terminal_visitor_func_table[BANG - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_BANG_func;
	terminal_visitor_func_table[BOOL - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_BOOL_func;
	terminal_visitor_func_table[INT - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_INT_func;
	terminal_visitor_func_table[CHAR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_CHAR_func;
	terminal_visitor_func_table[POINTER - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_POINTER_func;
	terminal_visitor_func_table[VOID - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_VOID_func;
	terminal_visitor_func_table[LPAREN - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_LPAREN_func;
	terminal_visitor_func_table[RPAREN - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_RPAREN_func;
	terminal_visitor_func_table[GTR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_GTR_func;
	terminal_visitor_func_table[LESS - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_LESS_func;
	terminal_visitor_func_table[GTR_EQ - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_GTR_EQ_func;
	terminal_visitor_func_table[LESS_EQ - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_LESS_EQ_func;
	terminal_visitor_func_table[DBL_EQ - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_DBL_EQ_func;
	terminal_visitor_func_table[EQ - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_EQ_func;
	terminal_visitor_func_table[NOT_EQ - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_NOT_EQ_func;
	terminal_visitor_func_table[OR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_OR_func;
	terminal_visitor_func_table[AND - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_AND_func;
	terminal_visitor_func_table[COMMA - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_COMMA_func;
	terminal_visitor_func_table[SEMICOLON - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_SEMICOLON_func;
	terminal_visitor_func_table[IF - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_IF_func;
	terminal_visitor_func_table[ELSE - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_ELSE_func;
	terminal_visitor_func_table[WHILE - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_WHILE_func;
	terminal_visitor_func_table[LBRACE - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_LBRACE_func;
	terminal_visitor_func_table[RBRACE - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_RBRACE_func;
	terminal_visitor_func_table[DECIMAL - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_DECIMAL_func;
	terminal_visitor_func_table[OCTAL - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_OCTAL_func;
	terminal_visitor_func_table[HEX - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_HEX_func;
	terminal_visitor_func_table[BINARY - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_BINARY_func;
	terminal_visitor_func_table[LIGHT_ACTUATOR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_LIGHT_ACTUATOR_func;
	terminal_visitor_func_table[SERVO_ACTUATOR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_SERVO_ACTUATOR_func;
	terminal_visitor_func_table[SOUND_SENSOR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_SOUND_SENSOR_func;
	terminal_visitor_func_table[LIGHT_SENSOR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_LIGHT_SENSOR_func;
	terminal_visitor_func_table[DISTANCE_SENSOR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_DISTANCE_SENSOR_func;
	terminal_visitor_func_table[TEMPERATURE_SENSOR - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_TEMPERATURE_SENSOR_func;
	terminal_visitor_func_table[TRUE - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_TRUE_func;
	terminal_visitor_func_table[FALSE - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL] = TERMINAL_FALSE_func;

}

/*
Do not need this function

void call_visitor_func(int type_flag, int argc, char **argv)
{
	if (type_flag >= NON_TERMINAL_PROGRAM && type_flag <= NON_TERMINAL_DEVICE_TYPE) {
		(*non_terminal_visitor_func_table[type_flag - NON_TERMINAL_OFFSET_VAL])(argc, argv);
	}
	else {
		//must be a terminal
		(*terminal_visitor_func_table[type_flag - SCARL_TERMINAL_FUNC_TABLE_OFFSET_VAL])(argc, argv);
	}
}
*/

void print_ast_r(int level, struct ast_node *subtree);

void print_ast_r(int level, struct ast_node *subtree) {
	printf("%2i ", level);
	for (int i = 0; i < level; i++) {
		printf("--");
	}
	printf("%s\n", get_node_str(subtree));

	struct ast_node *next = subtree->leftmostChild;
	while (next != NULL) {
		print_ast_r(level + 1, next);
		next = next->nextSibling;
	}
}

void print_ast(struct ast_node *tree) {
	print_ast_r(0, tree);
}
