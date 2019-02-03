/*
 *  This file is part of the SCARL toolkit.
 *  
 *  SCARL is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  SCARL is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with SCARL.  If not, see <https://www.gnu.org/licenses/>.
 */
 
 
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

const char *get_node_type_str(int type_flag);

void print_node_stack(struct ast_node_stack *stk);

#endif