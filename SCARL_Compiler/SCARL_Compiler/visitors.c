
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> 

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

struct ast_node * NON_TERMINAL_PROGRAM_func(int argc, ...) {
	if (print_productions) if (print_productions) printf("Match production  NON_TERMINAL_PROGRAM\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *statement_list_node = va_arg(arguments, struct ast_node*);
	statement_list_node->type_flag = NON_TERMINAL_PROGRAM;
	ast_node_stack_push(node_stack, statement_list_node); //push the complete AST onto the node stack

	va_end(arguments);

	return NULL;
}

struct ast_node * NON_TERMINAL_STATEMENT_LIST_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_STATEMENT_LIST\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 1) {
		//create the parameter list and add the argument to it
		struct ast_node *statement_list_node = create_node(NULL, NON_TERMINAL_STATEMENT_LIST);
		struct ast_node *statement_node = va_arg(arguments, struct ast_node*);
		add_child(statement_list_node, statement_node);
		va_end(arguments);
		return statement_list_node;
	}
	else if (argc == 2) {
		//add to existing statement list
		struct ast_node *statement_list_node = va_arg(arguments, struct ast_node*);
		struct ast_node *statement_node = va_arg(arguments, struct ast_node*);
		add_child_front(statement_list_node, statement_node);
		va_end(arguments);
		return statement_list_node;
	}
	else {
		va_end(arguments);
	}

	return NULL;
}

struct ast_node * NON_TERMINAL_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_STATEMENT\n");

	struct ast_node *statement_node = create_node(NULL, NON_TERMINAL_STATEMENT);
	struct ast_node *statement_child_node = ast_node_stack_pop(node_stack);
	add_child(statement_node, statement_child_node);
	ast_node_stack_push(node_stack, statement_node);

	return NULL;
}

struct ast_node * NON_TERMINAL_BLOCK_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_BLOCK_STATEMENT\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *statement_list_node = va_arg(arguments, struct ast_node*);
	statement_list_node->type_flag = NON_TERMINAL_BLOCK_STATEMENT;

	va_end(arguments);
	return statement_list_node;
}

struct ast_node * NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 1) {
		//create the parameter list and add the argument to it
		struct ast_node *statement_list_node = create_node(NULL, NON_TERMINAL_STATEMENT_LIST_BLOCK_LEVEL);
		struct ast_node *statement_node = va_arg(arguments, struct ast_node*);
		add_child(statement_list_node, statement_node);
		va_end(arguments);
		return statement_list_node;
	}
	else if (argc == 2) {
		//add to existing statement list
		struct ast_node *statement_list_node = va_arg(arguments, struct ast_node*);
		struct ast_node *statement_node = va_arg(arguments, struct ast_node*);
		add_child_front(statement_list_node, statement_node);
		va_end(arguments);
		return statement_list_node;
	}
	else {
		va_end(arguments);
	}
	return NULL;
}

struct ast_node * NON_TERMINAL_STATEMENT_BLOCK_LEVEL_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_STATEMENT_BLOCK_LEVEL\n");

	//all pass upwards as per the grammar
	return NULL;
}

struct ast_node * NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT\n");

	//construct a device declarator statement node and push it to the node stack

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *device_type_node = va_arg(arguments, struct ast_node*);
	struct ast_node *ident_node = va_arg(arguments, struct ast_node*);

	//construct the subtree to represent the statement
	struct ast_node *device_decl_statement_node = create_node(NULL, NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT);
	add_child(device_decl_statement_node, device_type_node);
	add_child(device_decl_statement_node, ident_node);

	va_end(arguments);
	return device_decl_statement_node;
}


struct ast_node * NON_TERMINAL_PRIMITIVE_DECLARATOR_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_PRIMITIVE_DECLARATOR\n");

	//identifier and primitive type are on top of the stack

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *primitive_type_node = va_arg(arguments, struct ast_node*);
	struct ast_node *ident_node = va_arg(arguments, struct ast_node*);

	//parent node to hold the type and identifier
	struct ast_node *primitive_decl_node = create_node(NULL, NON_TERMINAL_PRIMITIVE_DECLARATOR);
	add_child(primitive_decl_node, primitive_type_node);
	add_child(primitive_decl_node, ident_node);

	va_end(arguments);
	return primitive_decl_node;
}

struct ast_node * NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *primitive_declarator_node = va_arg(arguments, struct ast_node*);
	struct ast_node *expression_node = va_arg(arguments, struct ast_node*);

	struct ast_node *primitive_definition_statement_node = create_node(NULL, NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT);
	add_child(primitive_definition_statement_node, primitive_declarator_node);
	add_child(primitive_definition_statement_node, expression_node);

	va_end(arguments);
	return primitive_definition_statement_node;
}

struct ast_node * NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *primitive_declarator_node = va_arg(arguments, struct ast_node*);
	struct ast_node *formal_parameter_list_node = va_arg(arguments, struct ast_node*);
	struct ast_node *block_statement_node = va_arg(arguments, struct ast_node*);

	struct ast_node *function_definition_statement_node = create_node(NULL, NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT);
	add_child(function_definition_statement_node, primitive_declarator_node);
	add_child(function_definition_statement_node, formal_parameter_list_node);
	add_child(function_definition_statement_node, block_statement_node);
	va_end(arguments);
	return function_definition_statement_node;
}


struct ast_node * NON_TERMINAL_VARIABLE_SET_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_VARIABLE_SET_STATEMENT\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *ident_node = va_arg(arguments, struct ast_node*);
	struct ast_node *expression_node = va_arg(arguments, struct ast_node*);

	struct ast_node *variable_set_statement_node = create_node(NULL, NON_TERMINAL_VARIABLE_SET_STATEMENT);
	add_child(variable_set_statement_node, ident_node);
	add_child(variable_set_statement_node, expression_node);
	va_end(arguments);
	return variable_set_statement_node;
}

struct ast_node * NON_TERMINAL_RETURN_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production NON_TERMINAL_RETURN_STATEMENT\n");

	va_list arguments;
	va_start(arguments, argc);

	// We expect an expression node only but mark it as a return statement 
	struct ast_node *expression_node = va_arg(arguments, struct ast_node*);

	struct ast_node *return_statement_node = create_node(NULL, NON_TERMINAL_RETURN_STATEMENT);
	add_child(return_statement_node, expression_node);
	va_end(arguments);

	return return_statement_node;
}

struct ast_node * NON_TERMINAL_FUNCTION_INVOCATION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_FUNCTION_INVOCATION\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *ident_node = va_arg(arguments, struct ast_node*);
	struct ast_node *param_list_node = va_arg(arguments, struct ast_node*);

	struct ast_node *function_invocation_node = create_node(NULL, NON_TERMINAL_FUNCTION_INVOCATION);
	add_child(function_invocation_node, ident_node);
	add_child(function_invocation_node, param_list_node);
	
	va_end(arguments);
	return function_invocation_node;
}

struct ast_node * NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *function_invocation_node = va_arg(arguments, struct ast_node*);
	struct ast_node *function_invocation_statement_node = create_node(NULL, NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT);
	add_child(function_invocation_statement_node, function_invocation_node);
	
	va_end(arguments);
	return function_invocation_statement_node;
}

struct ast_node * NON_TERMINAL_IF_BLOCK_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_IF_BLOCK_STATEMENT\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 2) {
		//if without else
		struct ast_node *expression_node = va_arg(arguments, struct ast_node*);
		struct ast_node *block_statement_node = va_arg(arguments, struct ast_node*);

		struct ast_node *if_block_statement_node = create_node(NULL, NON_TERMINAL_IF_BLOCK_STATEMENT);
		add_child(if_block_statement_node, expression_node);
		add_child(if_block_statement_node, block_statement_node);
		va_end(arguments);
		return if_block_statement_node;
	}
	else if (argc == 3) {
		//if with else
		struct ast_node *expression_node = va_arg(arguments, struct ast_node*);
		struct ast_node *if_part_block_statement_node = va_arg(arguments, struct ast_node*);
		struct ast_node *else_part_block_statement_node = va_arg(arguments, struct ast_node*);
		

		struct ast_node *if_block_statement_node = create_node(NULL, NON_TERMINAL_IF_BLOCK_STATEMENT);
		add_child(if_block_statement_node, expression_node);
		add_child(if_block_statement_node, if_part_block_statement_node);
		add_child(if_block_statement_node, else_part_block_statement_node);
		va_end(arguments);
		return if_block_statement_node;
	}
	return NULL;
}

struct ast_node * NON_TERMINAL_WHILE_BLOCK_STATEMENT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_WHILE_BLOCK_STATEMENT\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *expression_node = va_arg(arguments, struct ast_node*);
	struct ast_node *block_statement_node = va_arg(arguments, struct ast_node*);

	struct ast_node *while_block = create_node(NULL, NON_TERMINAL_WHILE_BLOCK_STATEMENT);
	add_child(while_block, expression_node);
	add_child(while_block, block_statement_node);

	va_end(arguments);
	return while_block;
}

struct ast_node * NON_TERMINAL_FORMAL_PARAMETER_LIST_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_FORMAL_PARAMETER_LIST\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 0) {
		//empty parameter list
		va_end(arguments);
		return create_node(NULL, NON_TERMINAL_FORMAL_PARAMETER_LIST);
	}
	else if (argc == 1) {
		//we need to build the parameter list
		struct ast_node *param_list_node = create_node(NULL, NON_TERMINAL_FORMAL_PARAMETER_LIST);
		//add the single expression to the list
		add_child(param_list_node, va_arg(arguments, struct ast_node*));
		va_end(arguments);
		return param_list_node;
	}
	else {
		//we presume that there is an existing parameter list node and we add to it
		struct ast_node *existing_param_list = va_arg(arguments, struct ast_node*);
		add_child_front(existing_param_list, va_arg(arguments, struct ast_node*));
		va_end(arguments);
		return existing_param_list;
	}
}

struct ast_node * NON_TERMINAL_PARAMETER_LIST_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_PARAMETER_LIST\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 0) {
		//empty parameter list
		va_end(arguments);
		return create_node(NULL, NON_TERMINAL_PARAMETER_LIST);
	} else if (argc == 1) {
		//we need to build the parameter list
		struct ast_node *param_list_node = create_node(NULL, NON_TERMINAL_PARAMETER_LIST);
		//add the single expression to the list
		add_child(param_list_node, va_arg(arguments, struct ast_node*));
		va_end(arguments);
		return param_list_node;
	} else {
		//we presume that there is an existing parameter list node and we add to it
		struct ast_node *existing_param_list = va_arg(arguments, struct ast_node*);
		add_child_front(existing_param_list, va_arg(arguments, struct ast_node*));
		va_end(arguments);
		return existing_param_list;
	}
}

struct ast_node * NON_TERMINAL_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_EXPRESSION\n");

	//pass through
	return NULL;
}

struct ast_node * NON_TERMINAL_LOGICAL_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_LOGICAL_EXPRESSION\n");
	//same deal as the equality expression

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 3) {
		struct ast_node *lhs, *operand, *rhs;
		lhs = va_arg(arguments, struct ast_node *);
		operand = va_arg(arguments, struct ast_node *);
		rhs = va_arg(arguments, struct ast_node *);
		add_child(operand, lhs);
		add_child(operand, rhs);
		va_end(arguments);
		return operand;
	}
	else {
		struct ast_node *pass = va_arg(arguments, struct ast_node*);
		va_end(arguments);
		return pass;
	}
}


struct ast_node * NON_TERMINAL_LOGICAL_AND_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_LOGICAL_AND_EXPRESSION\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 3) {
		struct ast_node *lhs, *operand, *rhs;
		lhs = va_arg(arguments, struct ast_node *);
		operand = va_arg(arguments, struct ast_node *);
		rhs = va_arg(arguments, struct ast_node *);
		add_child(operand, lhs);
		add_child(operand, rhs);
		va_end(arguments);
		return operand;
	}
	else {
		struct ast_node *pass = va_arg(arguments, struct ast_node*);
		va_end(arguments);
		return pass;
	}
}
struct ast_node * NON_TERMINAL_EQUALITY_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_EQUALITY_EXPRESSION\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 3) {
		struct ast_node *lhs, *operand, *rhs;
		lhs = va_arg(arguments, struct ast_node *);
		operand = va_arg(arguments, struct ast_node *);
		rhs = va_arg(arguments, struct ast_node *);
		add_child(operand, lhs);
		add_child(operand, rhs);
		va_end(arguments);
		return operand;
	}
	else {
		struct ast_node *pass = va_arg(arguments, struct ast_node*);
		va_end(arguments);
		return pass;
	}
}

struct ast_node * NON_TERMINAL_RELATIONAL_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_RELATIONAL_EXPRESSION\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 3) {
		struct ast_node *lhs, *operand, *rhs;
		lhs = va_arg(arguments, struct ast_node *);
		operand = va_arg(arguments, struct ast_node *);
		rhs = va_arg(arguments, struct ast_node *);
		add_child(operand, lhs);
		add_child(operand, rhs);
		va_end(arguments);
		return operand;
	}
	else {
		struct ast_node *pass = va_arg(arguments, struct ast_node*);
		va_end(arguments);
		return pass;
	}
}

struct ast_node * NON_TERMINAL_BOOL_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_BOOL_EXPRESSION\n");
	//add all children at the end of the expression to the front
	//this is likely a BANG

	va_list arguments;
	va_start(arguments, argc);
	struct ast_node *parent_node = va_arg(arguments, struct ast_node *);
	int i = 1;
	while (i < argc) {
		add_child(parent_node, va_arg(arguments, struct ast_node *));
		i++;
	}
	va_end(arguments);

	return parent_node;
}

struct ast_node * NON_TERMINAL_ARITHMETIC_EXPRESSION_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_ARITHMETIC_EXPRESSION\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 3) {
		struct ast_node *lhs, *operand, *rhs;
		lhs = va_arg(arguments, struct ast_node *);
		operand = va_arg(arguments, struct ast_node *);
		rhs = va_arg(arguments, struct ast_node *);
		add_child(operand, lhs);
		add_child(operand, rhs);
		va_end(arguments);
		return operand;
	}
	else {
		struct ast_node *pass = va_arg(arguments, struct ast_node*);
		va_end(arguments);
		return pass;
	}

}



struct ast_node * NON_TERMINAL_ARITHMETIC_FACTOR_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_ARITHMETIC_FACTOR\n");

	va_list arguments;
	va_start(arguments, argc);

	if (argc == 3) {
		struct ast_node *lhs, *operand, *rhs;
		lhs = va_arg(arguments, struct ast_node *);
		operand = va_arg(arguments, struct ast_node *);
		rhs = va_arg(arguments, struct ast_node *);
		add_child(operand, lhs);
		add_child(operand, rhs);
		va_end(arguments);
		return operand;
	}
	else {
		struct ast_node *pass = va_arg(arguments, struct ast_node*);
		va_end(arguments);
		return pass;
	}
}


struct ast_node * NON_TERMINAL_ARITHMETIC_UNARY_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_ARITHMETIC_UNARY\n");

	//add all children at the end of the expression to the front
	//this is likely a minus with a child expression, saying to
	//flip the sign of the child expression

	va_list arguments;
	va_start(arguments, argc);
	struct ast_node *parent_node = va_arg(arguments, struct ast_node *);
	int i = 1;
	while (i < argc) {
		add_child(parent_node, va_arg(arguments, struct ast_node *));
		i++;
	}
	va_end(arguments);

	return parent_node;
}


struct ast_node * NON_TERMINAL_UNIT_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_UNIT\n");
	
	//the grammar action simply passes this one upwards
	return NULL;
}

struct ast_node * NON_TERMINAL_INTEGER_VALUE_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_INTEGER_VALUE\n");
	
	//the grammar passes this function upwards
	return NULL;
}

struct ast_node * NON_TERMINAL_BOOL_VALUE_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_BOOL_VALUE\n");

	va_list ap;
	va_start(ap, argc);
	
	struct ast_node *terminal_node = create_node(NULL, NON_TERMINAL_BOOL_VALUE);
	terminal_node->int_value = va_arg(ap, int);
	va_end(ap);
	
	return terminal_node;
}

struct ast_node * NON_TERMINAL_PRIMITIVE_TYPE_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_PRIMITIVE_TYPE\n");

	va_list ap;
	va_start(ap, argc);

	struct ast_node *primitive_type_node = create_node(NULL, NON_TERMINAL_PRIMITIVE_TYPE);
	primitive_type_node->int_value = va_arg(ap, int);
	va_end(ap);
	return primitive_type_node;
}

struct ast_node * NON_TERMINAL_DEVICE_TYPE_func(int argc, ...) {
	if (print_productions) printf("Match production  NON_TERMINAL_DEVICE_TYPE\n");

	va_list ap;
	va_start(ap, argc);

	//argc is the type of the device
	struct ast_node *device_type_node = create_node(NULL, NON_TERMINAL_DEVICE_TYPE);
	device_type_node->int_value = va_arg(ap, int);
	va_end(ap);
	return device_type_node;
}

struct ast_node * TERMINAL_IDENTIFIER_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_IDENTIFIER ");
	//the most recent identifier to be recognized is on the stack
	//pop it off and return it as the identifier token
	struct ast_node *ident_node = ast_node_stack_pop(ident_stack);
	if (print_productions) printf("%s\n", ident_node->str_value);
	return ident_node;
}

struct ast_node * TERMINAL_PLUS_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_PLUS\n");
	return create_node(NULL, PLUS);
}

struct ast_node * TERMINAL_MINUS_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_MINUS\n");
	return create_node(NULL, MINUS);
}

struct ast_node * TERMINAL_STAR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_STAR\n");
	return create_node(NULL, STAR);
}

struct ast_node * TERMINAL_SLASH_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_SLASH\n");
	return create_node(NULL, SLASH);
}

struct ast_node * TERMINAL_BANG_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_BANG\n");
	return create_node(NULL, BANG);
}

struct ast_node * TERMINAL_BOOL_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_BOOL\n");
	return create_node(NULL, BOOL);
}

struct ast_node * TERMINAL_INT_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_INT\n");
	return create_node(NULL, INT);
}

struct ast_node * TERMINAL_CHAR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_CHAR\n");
	return create_node(NULL, CHAR);
}

struct ast_node * TERMINAL_POINTER_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_POINTER\n");
	return create_node(NULL, POINTER);
}

struct ast_node * TERMINAL_VOID_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_VOID\n");
	return create_node(NULL, VOID);
}

struct ast_node * TERMINAL_LPAREN_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LPAREN\n");
	return create_node(NULL, LPAREN);
}

struct ast_node * TERMINAL_RPAREN_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_RPAREN\n");
	return create_node(NULL, RPAREN);
}

struct ast_node * TERMINAL_GTR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_GTR\n");
	return create_node(NULL, GTR);
}

struct ast_node * TERMINAL_LESS_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LESS\n");
	return create_node(NULL, LESS);
}

struct ast_node * TERMINAL_GTR_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_GTR_EQ\n");
	return create_node(NULL, GTR_EQ);
}

struct ast_node * TERMINAL_LESS_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LESS_EQ\n");
	return create_node(NULL, LESS_EQ);
}

struct ast_node * TERMINAL_DBL_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_DBL_EQ\n");
	return create_node(NULL, DBL_EQ);
}

struct ast_node * TERMINAL_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_EQ\n");
	return create_node(NULL, EQ);
}

struct ast_node * TERMINAL_NOT_EQ_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_NOT_EQ\n");
	return create_node(NULL, NOT_EQ);
}

struct ast_node * TERMINAL_OR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_OR\n");
	return create_node(NULL, OR);
}

struct ast_node * TERMINAL_AND_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_AND\n");
	return create_node(NULL, AND);
}

struct ast_node * TERMINAL_COMMA_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_COMMA\n");
	return create_node(NULL, COMMA);
}

struct ast_node * TERMINAL_SEMICOLON_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_SEMICOLON\n");
	return create_node(NULL, SEMICOLON);
}

struct ast_node * TERMINAL_IF_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_IF\n");
	return create_node(NULL, IF);
}

struct ast_node * TERMINAL_ELSE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_ELSE\n");
	return create_node(NULL, ELSE);
}

struct ast_node * TERMINAL_WHILE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_WHILE\n");
	return create_node(NULL, WHILE);
}

struct ast_node * TERMINAL_LBRACE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LBRACE\n");
	return create_node(NULL, LBRACE);
}

struct ast_node * TERMINAL_RBRACE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_RBRACE\n");
	return create_node(NULL, RBRACE);
}

struct ast_node * TERMINAL_DECIMAL_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_DECIMAL\n");
	//evaluate the decimal and keep its string representation
	
	va_list arguments;
	va_start(arguments, argc);
	
	struct ast_node *decimal_node = create_node(NULL, DECIMAL);
	char *dec_str = va_arg(arguments, char*);
	decimal_node->str_value = _strdup(dec_str);
	decimal_node->int_value = atoi(dec_str);
	//printf("The decimal val for %s is %i\n", argv[0], decimal_node->int_value);
	
	va_end(arguments);
	return decimal_node;
}

struct ast_node * TERMINAL_OCTAL_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_OCTAL\n");
	//evaluate the octal and keep its string representation
	
	va_list arguments;
	va_start(arguments, argc);
	
	struct ast_node *octal_node = create_node(NULL, OCTAL);
	char *oct_str = va_arg(arguments, char*);
	octal_node->str_value = _strdup(oct_str);
	int octal_val = 0;
	int evali = strlen(oct_str) - 1;
	int place_val = 1;
	while (evali > 0) {
		octal_val += ((oct_str[evali] - '0') * place_val);
		place_val *= 8;
		evali--;
	}
	//printf("The octal val for %s is %i\n", argv[0], octal_val);
	octal_node->int_value = octal_val;
	
	va_end(arguments);
	return octal_node;
}

struct ast_node * TERMINAL_HEX_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_HEX\n");
	
	va_list arguments;
	va_start(arguments, argc);
	struct ast_node *hex_node = create_node(NULL, HEX);
	char *hex_str = va_arg(arguments, char*);
	hex_node->str_value = _strdup(hex_str);
	int hex_val = 0;
	int evali = strlen(hex_str) - 1;
	int place_val = 1;
	while (evali > 1) { //do not count the 0x
		char hex_char = hex_str[evali];
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
	
	va_end(arguments);
	return hex_node;
}

struct ast_node * TERMINAL_BINARY_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_BINARY\n");

	va_list arguments;
	va_start(arguments, argc);

	struct ast_node *binary_node = create_node(NULL, BINARY);
	char *bin_str = va_arg(arguments, char*);
	binary_node->str_value = _strdup(bin_str);
	int bin_val = 0;
	int evali = strlen(bin_str) - 1;
	int place_val = 1;
	while (evali > 1) { //exclude 0b
		bin_val += ((bin_str[evali] - '0') * place_val);
		place_val *= 2;
		evali--;
	}
	//printf("The value of the binary %s is %i\n", argv[0], bin_val);
	binary_node->int_value = bin_val;

	va_end(arguments);
	return binary_node;
}

struct ast_node * TERMINAL_LIGHT_ACTUATOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LIGHT_ACTUATOR\n");
	return create_node(NULL, LIGHT_ACTUATOR);
}

struct ast_node * TERMINAL_SERVO_ACTUATOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_SERVO_ACTUATOR\n");
	return create_node(NULL, SERVO_ACTUATOR);
}

struct ast_node * TERMINAL_SOUND_SENSOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_SOUND_SENSOR\n");
	return create_node(NULL, SOUND_SENSOR);
}

struct ast_node * TERMINAL_LIGHT_SENSOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_LIGHT_SENSOR\n");
	return create_node(NULL, LIGHT_SENSOR);
}

struct ast_node * TERMINAL_DISTANCE_SENSOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_DISTANCE_SENSOR\n");
	return create_node(NULL, DISTANCE_SENSOR);
}

struct ast_node * TERMINAL_TEMPERATURE_SENSOR_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_TEMPERATURE_SENSOR\n");
	return create_node(NULL, TEMPERATURE_SENSOR);
}

struct ast_node * TERMINAL_TRUE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_TRUE\n");
	return create_node(NULL, TRUE);
}

struct ast_node * TERMINAL_FALSE_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_FALSE\n");
	return create_node(NULL, FALSE);
}

struct ast_node * TERMINAL_RETURN_func(int argc, ...) {
	if (print_productions) printf("Recognized token  TERMINAL_RETURN\n");
	return create_node(NULL, RETURN);
}
