
#include <stdlib.h>
#include <stdio.h>

#include "scarlnodestack.h"

struct ast_node_stack *create_node_stack(unsigned capacity) {
	struct ast_node_stack *stk = (struct ast_node_stack*)malloc(sizeof(struct ast_node_stack));
	stk->stack_space = (struct ast_node**)malloc(sizeof(struct ast_node*) * capacity);
	//initialize the top of the stack
	stk->top = 0;
	stk->stack_space[stk->top] = NULL;
	stk->capacity = capacity;
	return stk;
}

inline int ast_node_stack_is_empty(struct ast_node_stack *stk) {
	return (stk->top == 0 && stk->stack_space[stk->top] == NULL);
}

const char *get_node_str(struct ast_node *nod) {
	if (nod->type_flag >= NON_TERMINAL_PROGRAM && nod->type_flag <= NON_TERMINAL_DEVICE_TYPE) {
		return get_non_terminal_mnemonic(nod->type_flag);
	}
	else {
		return get_terminal_mnemonic(nod->type_flag);
	}
}

void ast_node_stack_push(struct ast_node_stack *stk, struct ast_node *nod) {
	if (ast_node_stack_is_empty(stk)) {
		stk->stack_space[stk->top] = nod;
	}
	else {
		if (stk->top + 1 >= stk->capacity) {
			unsigned new_capacity = stk->capacity * 2;
			struct ast_node **new_stack_space = (struct ast_node**)malloc(sizeof(struct ast_node*) * new_capacity);
			//copy over the old stack contents
			for (unsigned i = 0; i < stk->capacity; i++) {
				new_stack_space[i] = stk->stack_space[i];
			}
			//we don't need the old stack anymore
			free(stk->stack_space);
			stk->capacity = new_capacity;
			stk->stack_space = new_stack_space;
		}
		//add to the top of the stack and increment the stack pointer
		//to point to the top element
		stk->top++;
		stk->stack_space[stk->top] = nod;

		//printf("\nPushed %s\n", get_node_str(nod));
	}
}

struct ast_node *ast_node_stack_pop(struct ast_node_stack *stk) {
	if (!ast_node_stack_is_empty(stk)) {
		struct ast_node *top_node = stk->stack_space[stk->top];
		
		if (stk->top > 0) {
			stk->top--;
		}
		else {
			stk->stack_space[stk->top] = NULL;
		}
		
		//printf("\nPopped %s\n", get_node_str(top_node));
		
		return top_node;
	}
	else {
		return NULL;
	}
}

struct ast_node *ast_node_stack_peek(struct ast_node_stack *stk) {
	return stk->stack_space[stk->top];
}

void print_node_stack(struct ast_node_stack *stk) {
	//we are going to print it out from the top down
	if (!ast_node_stack_is_empty(stk)) {
		for (int i = stk->top; i >= 0; i--) {
			int type = stk->stack_space[i]->type_flag;
			if (type >= NON_TERMINAL_PROGRAM && type <= NON_TERMINAL_DEVICE_TYPE) {
				printf("| %s |\n", get_non_terminal_mnemonic(type));
			}
			else {
				//must be a terminal
				if (type == IDENTIFIER) {
					printf("| %s |  <-- \"%s\"\n", get_terminal_mnemonic(type), stk->stack_space[i]->str_value);
				}
				else {
					printf("| %s |\n", get_terminal_mnemonic(type));
				}
			}
		}
		printf("------------\n");
	}
	else {
		printf("<empty stack>\n");
	}

}