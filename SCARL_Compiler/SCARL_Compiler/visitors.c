
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "visitors.h"
#include "scarlnodestack.h"
#include "y.tab.h"

extern struct ast_node_stack *node_stack;
extern char *lastTokenText;
extern struct ast_node_stack *ident_stack;

const int print_productions = 0;

//this stack is used in this file only to handle the evaluation
//of expressions
//struct ast_node_stack *node_stack = NULL;

void init_visitor_func_parsing_constructs() {
	//node_stack = create_node_stack(50);
}

//perhaps change the visitor functions to

//struct ast_node *visitor_func(int argc, ...);

void print_current_state() {
	printf("Current state:\n");
	printf("Node stack\n");
	print_node_stack(node_stack);
	printf("\nIdentifier stack:\n");
	print_node_stack(ident_stack);
	printf("\n\n");
}

void NON_TERMINAL_PROGRAM_func(int argc, ...) {
	if (print_productions) if (print_productions) printf("Match production  NON_TERMINAL_PROGRAM\n");

	struct ast_node *program_node = create_node(NULL, NON_TERMINAL_PROGRAM);
	struct ast_node *statement_list_node = ast_node_stack_pop(node_stack);
	add_child(program_node, statement_list_node);
	ast_node_stack_push(node_stack, program_node);
}

void NON_TERMINAL_STATEMENT_LIST_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_STATEMENT_LIST\n");

	if (argc == 1) {
		//create node and add the 1 expression on the node stack to it
		struct ast_node *statement_list_node = create_node(NULL, NON_TERMINAL_STATEMENT_LIST);
		struct ast_node *statement_node = ast_node_stack_pop(node_stack);
		add_child(statement_list_node, statement_node);
		ast_node_stack_push(node_stack, statement_list_node);
	}
	else if (argc == 2) {
		struct ast_node *statement_list_node = ast_node_stack_pop(node_stack);
		struct ast_node *statement_node = ast_node_stack_pop(node_stack);
		add_child_front(statement_list_node, statement_node);
		ast_node_stack_push(node_stack, statement_list_node);
	}
}
void NON_TERMINAL_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_STATEMENT\n");

	struct ast_node *statement_node = create_node(NULL, NON_TERMINAL_STATEMENT);
	struct ast_node *statement_child_node = ast_node_stack_pop(node_stack);
	add_child(statement_node, statement_child_node);
	ast_node_stack_push(node_stack, statement_node);
}

void NON_TERMINAL_BLOCK_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_BLOCK_STATEMENT\n");

	struct ast_node *block_statement = create_node(NULL, NON_TERMINAL_BLOCK_STATEMENT);
	struct ast_node *statement_list_node = ast_node_stack_pop(node_stack);
	add_child(block_statement, statement_list_node);
	ast_node_stack_push(node_stack, block_statement);
}

void NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL\n");
	
	
	if (argc == 1) {
		//create node and add the 1 expression on the node stack to it
		struct ast_node *statement_list_node = create_node(NULL, NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL);
		struct ast_node *statement_block_level_node = ast_node_stack_pop(node_stack);
		add_child(statement_list_node, statement_block_level_node);
		ast_node_stack_push(node_stack, statement_list_node);
	}
	else if (argc == 2) {
		struct ast_node *statement_list_node = ast_node_stack_pop(node_stack);
		struct ast_node *statement_block_level_node = ast_node_stack_pop(node_stack);
		add_child_front(statement_list_node, statement_block_level_node);
		ast_node_stack_push(node_stack, statement_list_node);
	}

}

void NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_STATEMENT_BLOCK_LEVEL\n");

	struct ast_node *statement_block_level_node = create_node(NULL, NON_TERMINAL_STATEMENT_BLOCK_LEVEL);
	struct ast_node *statement_node = ast_node_stack_pop(node_stack);
	add_child(statement_block_level_node, statement_node);
	ast_node_stack_push(node_stack, statement_block_level_node);
}

void NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT\n");

	//constrct a device declarator statement node and push it to the node stack

	//struct ast_node *semicolon_node = ast_node_stack_pop(node_stack);  -- semicolon not placed on stack
	struct ast_node *ident_node = ast_node_stack_pop(ident_stack);
	struct ast_node *device_type_node = ast_node_stack_pop(node_stack);

	//construct the subtree to represent the statement
	struct ast_node *device_decl_statement_node = create_node(NULL, NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT);
	add_child(device_decl_statement_node, device_type_node);
	add_child(device_decl_statement_node, ident_node);

	//add the subtree to the node stack
	ast_node_stack_push(node_stack, device_decl_statement_node);
}


void NON_TERMINAL_PRIMITIVE_DECLARATOR_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_PRIMITIVE_DECLARATOR\n");

	//identifier and primitive type are on top of the stack

	struct ast_node *ident_node = ast_node_stack_pop(ident_stack);
	struct ast_node *primitive_type_node = ast_node_stack_pop(node_stack);

	//parent node to hold the type and identifier
	struct ast_node *primitive_decl_node = create_node(NULL, NON_TERMINAL_PRIMITIVE_DECLARATOR);
	add_child(primitive_decl_node, primitive_type_node);
	add_child(primitive_decl_node, ident_node);

	ast_node_stack_push(node_stack, primitive_decl_node);
}

void NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT\n");

	struct ast_node *expression_node = ast_node_stack_pop(node_stack);
	struct ast_node *primitive_declarator_node = ast_node_stack_pop(node_stack);

	struct ast_node *primitive_definition_statement_node = create_node(NULL, NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT);
	add_child(primitive_definition_statement_node, primitive_declarator_node);
	add_child(primitive_definition_statement_node, expression_node);
	ast_node_stack_push(node_stack, primitive_definition_statement_node);
}

void NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT\n");

	struct ast_node *block_statement_node = ast_node_stack_pop(node_stack);
	struct ast_node *formal_parameter_list_node = ast_node_stack_pop(node_stack);
	struct ast_node *primitive_declarator_node = ast_node_stack_pop(node_stack);

	struct ast_node *function_definition_statement_node = create_node(NULL, NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT);
	add_child(function_definition_statement_node, primitive_declarator_node);
	add_child(function_definition_statement_node, formal_parameter_list_node);
	add_child(function_definition_statement_node, block_statement_node);
	ast_node_stack_push(node_stack, function_definition_statement_node);
}


void NON_TERMINAL_VARIABLE_SET_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_VARIABLE_SET_STATEMENT\n");

	struct ast_node *ident_node = ast_node_stack_pop(ident_stack);
	struct ast_node *expression_node = ast_node_stack_pop(node_stack);

	struct ast_node *variable_set_statement_node = create_node(NULL, NON_TERMINAL_VARIABLE_SET_STATEMENT);
	add_child(variable_set_statement_node, ident_node);
	add_child(variable_set_statement_node, expression_node);
	ast_node_stack_push(node_stack, variable_set_statement_node);
}

void NON_TERMINAL_FUNCTION_INVOCATION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_FUNCTION_INVOCATION\n");

	struct ast_node *ident_node = ast_node_stack_pop(ident_stack);
	struct ast_node *param_list_node = ast_node_stack_pop(node_stack);

	struct ast_node *function_invocation_node = create_node(NULL, NON_TERMINAL_FUNCTION_INVOCATION);
	add_child(function_invocation_node, ident_node);
	add_child(function_invocation_node, param_list_node);
	ast_node_stack_push(node_stack, function_invocation_node);
}

void NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT\n");

	struct ast_node *function_invocation_node = ast_node_stack_pop(node_stack);
	struct ast_node *function_invocation_statement_node = create_node(NULL, NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT);
	add_child(function_invocation_statement_node, function_invocation_node);
	ast_node_stack_push(node_stack, function_invocation_statement_node);
}

void NON_TERMINAL_IF_BLOCK_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_IF_BLOCK_STATEMENT\n");
	if (argc == 2) {
		//if without else
		struct ast_node *block_statement_node = ast_node_stack_pop(node_stack);
		struct ast_node *expression_node = ast_node_stack_pop(node_stack);

		struct ast_node *if_block_statement_node = create_node(NULL, NON_TERMINAL_IF_BLOCK_STATEMENT);
		add_child(if_block_statement_node, expression_node);
		add_child(if_block_statement_node, block_statement_node);
		ast_node_stack_push(node_stack, if_block_statement_node);
	}
	else if (argc == 3) {
		//if with else
		struct ast_node *else_part_block_statement_node = ast_node_stack_pop(node_stack);
		struct ast_node *if_part_block_statement_node = ast_node_stack_pop(node_stack);
		struct ast_node *expression_node = ast_node_stack_pop(node_stack);

		struct ast_node *if_block_statement_node = create_node(NULL, NON_TERMINAL_IF_BLOCK_STATEMENT);
		add_child(if_block_statement_node, expression_node);
		add_child(if_block_statement_node, if_part_block_statement_node);
		add_child(if_block_statement_node, else_part_block_statement_node);
		ast_node_stack_push(node_stack, if_block_statement_node);
	}
}

void NON_TERMINAL_WHILE_BLOCK_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_WHILE_BLOCK_STATEMENT\n");

	struct ast_node *block_statement_node = ast_node_stack_pop(node_stack);
	struct ast_node *expression_node = ast_node_stack_pop(node_stack);

	struct ast_node *while_block_statement_node = create_node(NULL, NON_TERMINAL_WHILE_BLOCK_STATEMENT);
	add_child(while_block_statement_node, expression_node);
	add_child(while_block_statement_node, block_statement_node);
	ast_node_stack_push(node_stack, while_block_statement_node);
}

void NON_TERMINAL_FORMAL_PARAMETER_LIST_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_FORMAL_PARAMETER_LIST\n");

	if (argc == 0) {
		struct ast_node *param_list_node = create_node(NULL, NON_TERMINAL_FORMAL_PARAMETER_LIST);
		ast_node_stack_push(node_stack, param_list_node);
	}
	else if (argc == 1) {
		struct ast_node *param_list_node = create_node(NULL, NON_TERMINAL_FORMAL_PARAMETER_LIST);
		struct ast_node *primitive_decl_node = ast_node_stack_pop(node_stack);
		add_child_front(param_list_node, primitive_decl_node);
		ast_node_stack_push(node_stack, param_list_node);
	}
	else if (argc == 2) {
		struct ast_node *param_list_node = ast_node_stack_pop(node_stack);
		struct ast_node *primitive_decl_node = ast_node_stack_pop(node_stack);
		add_child_front(param_list_node, primitive_decl_node);
		ast_node_stack_push(node_stack, param_list_node);
	}
}

void NON_TERMINAL_PARAMETER_LIST_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_PARAMETER_LIST\n");

	if (argc == 0) {
		struct ast_node *param_list_node = create_node(NULL, NON_TERMINAL_PARAMETER_LIST);
		ast_node_stack_push(node_stack, param_list_node);
	}
	else if (argc == 1) {
		struct ast_node *param_list_node = create_node(NULL, NON_TERMINAL_PARAMETER_LIST);
		struct ast_node *expression_node = ast_node_stack_pop(node_stack);
		add_child_front(param_list_node, expression_node); //TO DO : Add to front
		ast_node_stack_push(node_stack, param_list_node);
	}
	else if (argc == 2) {
		struct ast_node *param_list_node = ast_node_stack_pop(node_stack);
		struct ast_node *expression_node = ast_node_stack_pop(node_stack);
		add_child_front(param_list_node, expression_node); //TO DO : Add to front
		ast_node_stack_push(node_stack, param_list_node);
	}
}

void NON_TERMINAL_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_EXPRESSION\n");

	//the only possibility is for there to be a logical expression on the node stack

	struct ast_node *logical_expression_node = ast_node_stack_pop(node_stack);
	struct ast_node *expression_node = create_node(NULL, NON_TERMINAL_EXPRESSION);
	add_child(expression_node, logical_expression_node);
	ast_node_stack_push(node_stack, expression_node);
}

void NON_TERMINAL_LOGICAL_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_LOGICAL_EXPRESSION\n");
	//same deal as the equality expression

	if (argc == 3) {
		struct ast_node *or_operator_node = ast_node_stack_pop(node_stack);
		struct ast_node *logical_and_expression_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *logical_expression_lhs_node = ast_node_stack_pop(node_stack);

		struct ast_node *parent_logical_expression = create_node(NULL, NON_TERMINAL_LOGICAL_EXPRESSION);
		add_child(parent_logical_expression, logical_expression_lhs_node);
		add_child(parent_logical_expression, or_operator_node);
		add_child(parent_logical_expression, logical_and_expression_rhs_node);
		ast_node_stack_push(node_stack, parent_logical_expression);
	}
	else {
		struct ast_node *logical_and_expression_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *logical_expression_node = create_node(NULL, NON_TERMINAL_LOGICAL_EXPRESSION);
		add_child(logical_expression_node, logical_and_expression_rhs_node);
		ast_node_stack_push(node_stack, logical_expression_node);
	}
}


void NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_LOGICAL_AND_EXPRESSION\n");

	if (argc == 3) {
		struct ast_node *and_operator_node = ast_node_stack_pop(node_stack);
		struct ast_node *equality_expression_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *logical_and_expression_lhs_node = ast_node_stack_pop(node_stack);

		struct ast_node *parent_logical_and_expression = create_node(NULL, NON_TERMINAL_LOGICAL_AND_EXPRESSION);
		add_child(parent_logical_and_expression, logical_and_expression_lhs_node);
		add_child(parent_logical_and_expression, and_operator_node);
		add_child(parent_logical_and_expression, equality_expression_rhs_node);
		ast_node_stack_push(node_stack, parent_logical_and_expression);
	}
	else {
		struct ast_node *equality_expression_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *logical_and_expression_node = create_node(NULL, NON_TERMINAL_LOGICAL_AND_EXPRESSION);
		add_child(logical_and_expression_node, equality_expression_rhs_node);
		ast_node_stack_push(node_stack, logical_and_expression_node);
	}
}
void NON_TERMINAL_EQUALITY_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_EQUALITY_EXPRESSION\n");

	if (argc == 3) {
		struct ast_node *equality_operator = ast_node_stack_pop(node_stack);
		struct ast_node *relational_expression_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *equality_expression_lhs_node = ast_node_stack_pop(node_stack);

		struct ast_node *parent_equality_expression_node = create_node(NULL, NON_TERMINAL_EQUALITY_EXPRESSION);
		add_child(parent_equality_expression_node, equality_expression_lhs_node);
		add_child(parent_equality_expression_node, equality_operator);
		add_child(parent_equality_expression_node, relational_expression_rhs_node);
		ast_node_stack_push(node_stack, parent_equality_expression_node);
	}
	else {
		struct ast_node *relational_expression_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *equality_expression_node = create_node(NULL, NON_TERMINAL_EQUALITY_EXPRESSION);
		add_child(equality_expression_node, relational_expression_rhs_node);
		ast_node_stack_push(node_stack, equality_expression_node);
	}
}

void NON_TERMINAL_RELATIONAL_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_RELATIONAL_EXPRESSION\n");

	if (argc == 3) {
		struct ast_node *relational_operator = ast_node_stack_pop(node_stack);
		struct ast_node *bool_expression_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *relational_expression_lhs_node = ast_node_stack_pop(node_stack);

		struct ast_node *parent_relational_expression_node = create_node(NULL, NON_TERMINAL_RELATIONAL_EXPRESSION);
		add_child(parent_relational_expression_node, relational_expression_lhs_node);
		add_child(parent_relational_expression_node, relational_operator);
		add_child(parent_relational_expression_node, bool_expression_rhs_node);
		ast_node_stack_push(node_stack, parent_relational_expression_node);
	}
	else {
		//assume to reduce to relational expression with only bool expression as the child
		struct ast_node *bool_expression_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *relational_expression = create_node(NULL, NON_TERMINAL_RELATIONAL_EXPRESSION);
		add_child(relational_expression, bool_expression_rhs_node);
		ast_node_stack_push(node_stack, relational_expression);
	}
}

void NON_TERMINAL_BOOL_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_BOOL_EXPRESSION\n");

	if (argc == 2) {
		struct ast_node *bang_node = ast_node_stack_pop(node_stack);
		struct ast_node *arithmetic_expression_node = ast_node_stack_pop(node_stack);
		struct ast_node *bool_expression_node = create_node(NULL, NON_TERMINAL_BOOL_EXPRESSION);
		add_child(bool_expression_node, bang_node);
		add_child(bool_expression_node, arithmetic_expression_node);
		ast_node_stack_push(node_stack, bool_expression_node);
	}
	else {
		struct ast_node *arithmetic_expression_node = ast_node_stack_pop(node_stack);
		struct ast_node *bool_expression_node = create_node(NULL, NON_TERMINAL_BOOL_EXPRESSION);
		add_child(bool_expression_node, arithmetic_expression_node);
		ast_node_stack_push(node_stack, bool_expression_node);
	}
	
}

void NON_TERMINAL_ARITHMETIC_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_ARITHMETIC_EXPRESSION\n");

	//is there an expression on the top to reduce with (and a PLUS or a MINUS)?
	if (argc == 3) {
		
		struct ast_node *expression_operator_node = ast_node_stack_pop(node_stack);
		struct ast_node *arithmetic_expression_lhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *arithmetic_factor_rhs_node = ast_node_stack_pop(node_stack);

		struct ast_node *parent_arithmetic_expression_node = create_node(NULL, NON_TERMINAL_ARITHMETIC_EXPRESSION);
		add_child(parent_arithmetic_expression_node, arithmetic_expression_lhs_node);
		add_child(parent_arithmetic_expression_node, expression_operator_node);
		add_child(parent_arithmetic_expression_node, arithmetic_factor_rhs_node);
		ast_node_stack_push(node_stack, parent_arithmetic_expression_node);
	}
	else {
		//just reduce so that the expression has a single factor
		struct ast_node *arithmetic_factor_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *arithmetic_expression_node = create_node(NULL, NON_TERMINAL_ARITHMETIC_EXPRESSION);
		add_child(arithmetic_expression_node, arithmetic_factor_rhs_node);
		ast_node_stack_push(node_stack, arithmetic_expression_node);
	}

}



void NON_TERMINAL_ARITHMETIC_FACTOR_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_ARITHMETIC_FACTOR\n");

	//is there a factor on the top to reduce with (and a STAR or a SLASH)?
	if (argc == 3) {
		
		struct ast_node *factor_operator_node = ast_node_stack_pop(node_stack);
		struct ast_node *arithmetic_unary_rhs_node = ast_node_stack_pop(node_stack);
		struct ast_node *arithmetic_factor_lhs_node = ast_node_stack_pop(node_stack);

		struct ast_node *arithmetic_factor_node = create_node(NULL, NON_TERMINAL_ARITHMETIC_FACTOR);
		add_child(arithmetic_factor_node, arithmetic_factor_lhs_node);
		add_child(arithmetic_factor_node, factor_operator_node);
		add_child(arithmetic_factor_node, arithmetic_unary_rhs_node);

		ast_node_stack_push(node_stack, arithmetic_factor_node);
	}
	else {
		struct ast_node *arithmetic_unary_rhs_node = ast_node_stack_pop(node_stack);
		//reduce only the arithmetic unary to a factor (not right conditions for the first case)
		struct ast_node *arithmetic_factor_node = create_node(NULL, NON_TERMINAL_ARITHMETIC_FACTOR);
		add_child(arithmetic_factor_node, arithmetic_unary_rhs_node);
		
		ast_node_stack_push(node_stack, arithmetic_factor_node);
	}
}


void NON_TERMINAL_ARITHMETIC_UNARY_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_ARITHMETIC_UNARY\n");

	//should work for all situations as long as argc is correct
	
	struct ast_node *child_node = ast_node_stack_pop(node_stack);
	struct ast_node *arithmetic_unary_node = create_node(NULL, NON_TERMINAL_ARITHMETIC_UNARY);
	add_child(arithmetic_unary_node, child_node);
	if (argc == 2) {
		//include minus child
		add_child(arithmetic_unary_node, create_node(NULL, MINUS));
	}
	ast_node_stack_push(node_stack, arithmetic_unary_node);
	
}


void NON_TERMINAL_UNIT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_UNIT\n");
	//the child of this unit node denotes what kind of unit it is
	
	if (argc == 1) {
		//not an identifier unit
		struct ast_node *unit_child = ast_node_stack_pop(node_stack);
		struct ast_node *unit_node = create_node(NULL, NON_TERMINAL_UNIT);
		add_child(unit_node, unit_child);
		ast_node_stack_push(node_stack, unit_node);
	}
	else if (argc == 2) {
		//identifier unit
		struct ast_node *unit_child = ast_node_stack_pop(ident_stack);
		struct ast_node *unit_node = create_node(NULL, NON_TERMINAL_UNIT);
		add_child(unit_node, unit_child);
		ast_node_stack_push(node_stack, unit_node);
	}
}

void NON_TERMINAL_INTEGER_VALUE_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_INTEGER_VALUE\n");
	//expect an integer value node to be on top of the stack
	//make that node a child of a new integer value node
	//and push the integer value onto the stack
	
	//get integer value
	struct ast_node *child_val = ast_node_stack_pop(node_stack);

	struct ast_node *integer_val_node = create_node(NULL, NON_TERMINAL_INTEGER_VALUE);
	add_child(integer_val_node, child_val);
	ast_node_stack_push(node_stack, integer_val_node);
}
void NON_TERMINAL_BOOL_VALUE_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_BOOL_VALUE\n");
	//argc is the primitive type
	struct ast_node *terminal_node = create_node(NULL, NON_TERMINAL_BOOL_VALUE);
	terminal_node->int_value = argc;
	ast_node_stack_push(node_stack, terminal_node);
}

void NON_TERMINAL_PRIMITIVE_TYPE_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_PRIMITIVE_TYPE\n");

	//argc is the primitive type
	struct ast_node *primitive_type_node = create_node(NULL, NON_TERMINAL_PRIMITIVE_TYPE);
	primitive_type_node->int_value = argc;
	ast_node_stack_push(node_stack, primitive_type_node);
}

void NON_TERMINAL_DEVICE_TYPE_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_DEVICE_TYPE\n");

	//argc is the type of the device
	struct ast_node *device_type_node = create_node(NULL, NON_TERMINAL_DEVICE_TYPE);
	device_type_node->int_value = argc;
	ast_node_stack_push(node_stack, device_type_node);
}

void TERMINAL_IDENTIFIER_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_IDENTIFIER (%s)\n", argv[0]);
	struct ast_node *ident_node = create_node(NULL, IDENTIFIER);
	ident_node->str_value = _strdup(argv[0]);
	ast_node_stack_push(ident_stack, ident_node);
}

void TERMINAL_PLUS_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_PLUS\n");
	ast_node_stack_push(node_stack, create_node(NULL, PLUS));
}

void TERMINAL_MINUS_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_MINUS\n");
	ast_node_stack_push(node_stack, create_node(NULL, MINUS));
}

void TERMINAL_STAR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_STAR\n");
	ast_node_stack_push(node_stack, create_node(NULL, STAR));
}

void TERMINAL_SLASH_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_SLASH\n");
	ast_node_stack_push(node_stack, create_node(NULL, SLASH));
}

void TERMINAL_BANG_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_BANG\n");
	ast_node_stack_push(node_stack, create_node(NULL, BANG));
}

void TERMINAL_BOOL_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_BOOL\n");
	ast_node_stack_push(node_stack, create_node(NULL, BOOL));
}

void TERMINAL_INT_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_INT\n");
	ast_node_stack_push(node_stack, create_node(NULL, INT));
}

void TERMINAL_CHAR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_CHAR\n");
	ast_node_stack_push(node_stack, create_node(NULL, CHAR));
}

void TERMINAL_POINTER_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_POINTER\n");
	ast_node_stack_push(node_stack, create_node(NULL, POINTER));
}
void TERMINAL_VOID_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_VOID\n");
	ast_node_stack_push(node_stack, create_node(NULL, VOID));
}

void TERMINAL_LPAREN_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LPAREN\n");
	ast_node_stack_push(node_stack, create_node(NULL, LPAREN));
}

void TERMINAL_RPAREN_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_RPAREN\n");
	ast_node_stack_push(node_stack, create_node(NULL, RPAREN));
}

void TERMINAL_GTR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_GTR\n");
	ast_node_stack_push(node_stack, create_node(NULL, GTR));
}

void TERMINAL_LESS_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LESS\n");
	ast_node_stack_push(node_stack, create_node(NULL, LESS));
}

void TERMINAL_GTR_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_GTR_EQ\n");
	ast_node_stack_push(node_stack, create_node(NULL, GTR_EQ));
}

void TERMINAL_LESS_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LESS_EQ\n");
	ast_node_stack_push(node_stack, create_node(NULL, LESS_EQ));
}

void TERMINAL_DBL_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_DBL_EQ\n");
	ast_node_stack_push(node_stack, create_node(NULL, DBL_EQ));
}

void TERMINAL_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_EQ\n");
	ast_node_stack_push(node_stack, create_node(NULL, EQ));
}

void TERMINAL_NOT_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_NOT_EQ\n");
	ast_node_stack_push(node_stack, create_node(NULL, NOT_EQ));
}

void TERMINAL_OR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_OR\n");
	ast_node_stack_push(node_stack, create_node(NULL, OR));
}

void TERMINAL_AND_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_AND\n");
	ast_node_stack_push(node_stack, create_node(NULL, AND));
}

void TERMINAL_COMMA_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_COMMA\n");
	ast_node_stack_push(node_stack, create_node(NULL, COMMA));
}

void TERMINAL_SEMICOLON_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_SEMICOLON\n");
	
	//statement terminator, not to be placed onto the stack
	
	//ast_node_stack_push(node_stack, create_node(NULL, SEMICOLON));
}

void TERMINAL_IF_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_IF\n");
	ast_node_stack_push(node_stack, create_node(NULL, IF));
}

void TERMINAL_ELSE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_ELSE\n");
	ast_node_stack_push(node_stack, create_node(NULL, ELSE));
}

void TERMINAL_WHILE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_WHILE\n");
	ast_node_stack_push(node_stack, create_node(NULL, WHILE));
}

void TERMINAL_LBRACE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LBRACE\n");
	ast_node_stack_push(node_stack, create_node(NULL, LBRACE));
}

void TERMINAL_RBRACE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_RBRACE\n");
	ast_node_stack_push(node_stack, create_node(NULL, RBRACE));
}

void TERMINAL_DECIMAL_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_DECIMAL\n");
	//evaluate the decimal and keep its string representation
	struct ast_node *decimal_node = create_node(NULL, DECIMAL);
	decimal_node->str_value = _strdup(argv[0]);
	decimal_node->int_value = atoi(argv[0]);
	//printf("The decimal val for %s is %i\n", argv[0], decimal_node->int_value);
	ast_node_stack_push(node_stack, decimal_node);
}

void TERMINAL_OCTAL_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_OCTAL\n");
	//evaluate the octal and keep its string representation
	struct ast_node *octal_node = create_node(NULL, OCTAL);
	octal_node->str_value = _strdup(argv[0]);
	int octal_val = 0;
	int evali = strlen(argv[0]) - 1;
	int place_val = 1;
	while (evali > 0) {
		octal_val += ((argv[0][evali] - '0') * place_val);
		place_val *= 8;
		evali--;
	}
	//printf("The octal val for %s is %i\n", argv[0], octal_val);
	octal_node->int_value = octal_val;
	ast_node_stack_push(node_stack, octal_node);
}

void TERMINAL_HEX_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_HEX\n");
	struct ast_node *hex_node = create_node(NULL, HEX);
	hex_node->str_value = _strdup(argv[0]);
	int hex_val = 0;
	int evali = strlen(argv[0]) - 1;
	int place_val = 1;
	while (evali > 1) { //do not count the 0x
		char hex_char = argv[0][evali];
		int hex_char_value = 0;
		if (hex_char >= '0' && hex_char <= '9') {
			hex_char_value = hex_char - '0';
		}
		else if (hex_char >= 'a' && hex_char <= 'f') {
			hex_char_value = (hex_char - 'a') + 10;
		}
		else if (hex_char >= 'A' && hex_char <= 'F') {
			hex_char_value = (hex_char - 'A') + 10;
		}
		hex_val += (hex_char_value * place_val);
		place_val *= 16; //hex
		evali--;
	}
	//printf("The value for the hex %s is %i\n", argv[0], hex_val);
	hex_node->int_value = hex_val;
	ast_node_stack_push(node_stack, hex_node);
}

void TERMINAL_BINARY_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_BINARY\n");
	struct ast_node *binary_node = create_node(NULL, BINARY);
	binary_node->str_value = _strdup(argv[0]);
	int bin_val = 0;
	int evali = strlen(argv[0]) - 1;
	int place_val = 1;
	while (evali > 1) { //exclude 0b
		bin_val += ((argv[0][evali] - '0') * place_val);
		place_val *= 2;
		evali--;
	}
	//printf("The value of the binary %s is %i\n", argv[0], bin_val);
	binary_node->int_value = bin_val;
	ast_node_stack_push(node_stack, binary_node);
}

void TERMINAL_LIGHT_ACTUATOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LIGHT_ACTUATOR\n");
	ast_node_stack_push(node_stack, create_node(NULL, LIGHT_ACTUATOR));
}

void TERMINAL_SERVO_ACTUATOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_SERVO_ACTUATOR\n");
	ast_node_stack_push(node_stack, create_node(NULL, SERVO_ACTUATOR));
}

void TERMINAL_SOUND_SENSOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_SOUND_SENSOR\n");
	ast_node_stack_push(node_stack, create_node(NULL, SOUND_SENSOR));
}

void TERMINAL_LIGHT_SENSOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LIGHT_SENSOR\n");
	ast_node_stack_push(node_stack, create_node(NULL, LIGHT_SENSOR));
}

void TERMINAL_DISTANCE_SENSOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_DISTANCE_SENSOR\n");
	ast_node_stack_push(node_stack, create_node(NULL, DISTANCE_SENSOR));
}

void TERMINAL_TEMPERATURE_SENSOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_TEMPERATURE_SENSOR\n");
	ast_node_stack_push(node_stack, create_node(NULL, TEMPERATURE_SENSOR));
}

void TERMINAL_TRUE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_TRUE\n");
	ast_node_stack_push(node_stack, create_node(NULL, TRUE));
}

void TERMINAL_FALSE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_FALSE\n");
	ast_node_stack_push(node_stack, create_node(NULL, FALSE));
}
