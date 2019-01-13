#ifndef __SCARL_AST_H__
#define __SCARL_AST_H__

#include "y.tab.h"
#include "scarl_symboltable.h"

struct ast_node;

//each terminal and non-terminal
//gets its own flag so we can
//distinguish between the types
#define NON_TERMINAL_OFFSET_VAL						0x300
#define NON_TERMINAL_PROGRAM						0x301
#define NON_TERMINAL_STATEMENT_LIST					0x302
#define NON_TERMINAL_STATEMENT						0x303
#define NON_TERMINAL_BLOCK_STATEMENT				0x304
#define NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL		0x305
#define NON_TERMINAL_STATEMENT_BLOCK_LEVEL			0x306
#define NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT	0x307
#define NON_TERMINAL_PRIMITIVE_DECLARATOR			0x308
#define NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT	0x309
#define NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT	0x30A
#define NON_TERMINAL_VARIABLE_SET_STATEMENT			0x30B
#define NON_TERMINAL_FUNCTION_INVOCATION			0x30C
#define NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT	0x30D
#define NON_TERMINAL_IF_BLOCK_STATEMENT				0x30E
#define NON_TERMINAL_WHILE_BLOCK_STATEMENT			0x30F
#define NON_TERMINAL_FORMAL_PARAMETER_LIST			0x310
#define NON_TERMINAL_PARAMETER_LIST					0x311
#define NON_TERMINAL_EXPRESSION						0x312
#define NON_TERMINAL_LOGICAL_EXPRESSION				0x313
#define NON_TERMINAL_LOGICAL_AND_EXPRESSION			0x314
#define NON_TERMINAL_EQUALITY_EXPRESSION			0x315
#define NON_TERMINAL_RELATIONAL_EXPRESSION			0x316
#define NON_TERMINAL_BOOL_EXPRESSION				0x317
#define NON_TERMINAL_ARITHMETIC_EXPRESSION			0x318
#define NON_TERMINAL_ARITHMETIC_FACTOR				0x319
#define NON_TERMINAL_ARITHMETIC_UNARY				0x31A
#define NON_TERMINAL_UNIT							0x31B
#define NON_TERMINAL_INTEGER_VALUE					0x31C
#define NON_TERMINAL_BOOL_VALUE						0x31D
#define NON_TERMINAL_PRIMITIVE_TYPE					0x31E
#define NON_TERMINAL_DEVICE_TYPE					0x31F
#define NON_TERMINAL_RETURN_STATEMENT				0x320
//we have y.tab.h for the terminals


const char *get_non_terminal_mnemonic(int non_terminal_type);

const char *get_terminal_mnemonic(terminal_type);

struct ast_node {
	struct ast_node *parent; //root's parent is NULL
	struct ast_node *nextSibling;
	struct ast_node *leftmostChild; //the first child. This child will have a list of its nextSibling
	int type_flag;
	//need to be able to accomodate all cases
	//likely will have more fields than a node
	//will use at any point in time

	int int_value; //depends on the context
	char *str_value;
	struct scarl_symbol_table *symbol_table_value;
	int register1;
	int register2;
	int label;
};

typedef struct ast_node*(*ast_node_visitor_func)(int argc, char **argv);

struct ast_node *create_node(struct ast_node *parent, int type_flag);

//and all of its children
void destroy_node(struct ast_node *nod);

//pay attention to the structure of the nodes

void add_child(struct ast_node *nod, struct ast_node *child);

void add_child_front(struct ast_node *nod, struct ast_node *child);

void init_visitor_func_table();

void print_ast(struct ast_node *tree);

#endif