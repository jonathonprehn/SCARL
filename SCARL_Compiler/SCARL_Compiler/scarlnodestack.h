#ifndef __SCARL_NODE_STACK_H__
#define __SCARL_NODE_STACK_H__

#include <stdlib.h>

#include "scarlast.h"

/* Just implementing a regular stack */

struct ast_node_stack {
	struct ast_node **stack_space;
	unsigned top;
	unsigned capacity;
};

struct ast_node_stack *create_node_stack(unsigned capacity);

inline int ast_node_stack_is_empty(struct ast_node_stack *stk);

void ast_node_stack_push(struct ast_node_stack *stk, struct ast_node *nod);

struct ast_node *ast_node_stack_pop(struct ast_node_stack *stk);

struct ast_node *ast_node_stack_peek(struct ast_node_stack *stk);

const char *get_node_str(struct ast_node *nod);

void print_node_stack(struct ast_node_stack *stk);

#endif