
#include <stdlib.h>
#include <stdio.h>

#include "scarl_type.h"


//returns -1 if something in here has broken the rules
int get_expression_type(struct scarl_symbol_table *symbol_table, struct ast_node *expr) {
	//infer the type based on the subnodes and the types of the values
	//only

	//at the moment we are only supporting INT and BOOL 
	//but we can add more types down the road as we 
	//expand the capabilities of the language.

	//recursive
	//base case:

	if (expr->type_flag == NON_TERMINAL_BOOL_VALUE) {
		return BOOL;
	}
	else if (
		expr->type_flag == DECIMAL ||
		expr->type_flag == OCTAL ||
		expr->type_flag == HEX ||
		expr->type_flag == BINARY
		) {
		return INT;
	}
	else if (expr->type_flag == IDENTIFIER) {
		struct scarl_symbol_table_entry *ident_entry = lookup(symbol_table, expr->str_value, NULL, 0);
		if (ident_entry == NULL) {
			printf("Cannot find identifier \"%s\"\n", expr->str_value);
		}
		return ident_entry->type_flag;
	}
	else if (expr->type_flag == NON_TERMINAL_FUNCTION_INVOCATION) {
		//TO DO : lookup the function and see its type
		struct scarl_symbol_table_entry *entry = lookup_based_on_invocation_node(symbol_table, expr);
		return entry->type_flag;
	}
	else {
		if (expr->type_flag == PLUS ||
			expr->type_flag == MINUS ||
			expr->type_flag == STAR ||
			expr->type_flag == SLASH) {
			int lhs_type = get_expression_type(symbol_table, expr->leftmostChild);
			int rhs_type = get_expression_type(symbol_table, expr->leftmostChild->nextSibling);
			if (lhs_type == INT && rhs_type == INT) {
				return INT;
			}
			else {
				//someone messed up
				return -1;
			}
		}
		else if (
			expr->type_flag == LESS ||
			expr->type_flag == GTR ||
			expr->type_flag == LESS_EQ ||
			expr->type_flag == GTR_EQ
			) {
			int lhs_type = get_expression_type(symbol_table, expr->leftmostChild);
			int rhs_type = get_expression_type(symbol_table, expr->leftmostChild->nextSibling);
			if (lhs_type == INT && rhs_type == INT) {
				return BOOL;
			}
			else {
				//someone messed up
				return -1;
			}
		}
		else if (
			expr->type_flag == DBL_EQ ||
			expr->type_flag == NOT_EQ
			) {
			//sides can be any type, they just have to match
			int lhs_type = get_expression_type(symbol_table, expr->leftmostChild);
			int rhs_type = get_expression_type(symbol_table, expr->leftmostChild->nextSibling);
			if (lhs_type == rhs_type) {
				return lhs_type;
			}
			else {
				//someone messed up
				return -1;
			}
		}
		else if (
			expr->type_flag == AND ||
			expr->type_flag == OR
			) {
			int lhs_type = get_expression_type(symbol_table, expr->leftmostChild);
			int rhs_type = get_expression_type(symbol_table, expr->leftmostChild->nextSibling);
			if (lhs_type == BOOL && rhs_type == BOOL) {
				return BOOL;
			}
			else {
				//someone messed up
				return -1;
			}
		}
	}
	//unreachable statment down here
	return -1;
}