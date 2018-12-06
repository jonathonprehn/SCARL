
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scarl_type.h"
#include "scarl_semantic_analysis.h"

extern unsigned lineNumber;

extern char *lastTokenText;

int has_correct_main_method(struct ast_node *ast) {

	struct ast_node *global_node = ast->leftmostChild;
	
	while (global_node != NULL) {
		if (global_node->type_flag == NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT) {
			//does it have the signature for the main method?
			struct ast_node *prim_decl = global_node->leftmostChild;
			struct ast_node *formal_params = prim_decl->nextSibling;

			if (prim_decl->leftmostChild->int_value == VOID &&
				strcmp(prim_decl->leftmostChild->nextSibling->str_value, "main") == 0 &&
				formal_params->leftmostChild == NULL
				) {
				return 1; //we have the main method somewhere (found it)
			}
		}
		global_node = global_node->nextSibling;
	}
	//else
	return 0;
}

int types_are_correct(struct scarl_symbol_table *st, struct ast_node *ast) {
	
	struct ast_node *the_node = ast->leftmostChild;

	while (the_node != NULL) {
		switch (the_node->type_flag) {
			case NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT:
			{
				int ident_type = the_node->leftmostChild->leftmostChild->int_value;
				struct ast_node *expr_node = the_node->leftmostChild->nextSibling;
				int expr_infer_type = get_expression_type(st, expr_node);
				if (ident_type != expr_infer_type) {
					fprintf(stderr, "Incorrect type near \'%s\' on line %i\n", lastTokenText, lineNumber);
					return 0; //the types do not match up
				}
			}
			break;
			case NON_TERMINAL_FUNCTION_INVOCATION:
			{
				char *ident = the_node->leftmostChild->str_value;
				struct ast_node *param_list_node = the_node->leftmostChild->nextSibling;
				//get the types and see if there is an existing function
				//that also uses those parameters
				int paramCount = 0;
				struct ast_node *param_node = param_list_node->leftmostChild;
				while (param_node != NULL) {
					paramCount++;
					param_node = param_node->nextSibling;
				}
				
				int *derivedParamList = NULL;
				if (paramCount > 0) {
					derivedParamList = (int*)malloc(sizeof(int) * paramCount);
					param_node = param_list_node->leftmostChild;
					int i = 0;
					while (param_node != NULL) {
						derivedParamList[i] = get_expression_type(st, param_node);
						param_node = param_node->nextSibling;
						i++;
					}
				}
				struct scarl_symbol_table_entry *function_entry = lookup(st, ident, derivedParamList, paramCount);
				if (function_entry == NULL) {
					fprintf(stderr, "Incorrect type near \'%s\' on line %i\n", lastTokenText, lineNumber);
					return 0; //invalid
				}
				
			}
			break;
			case NON_TERMINAL_VARIABLE_SET_STATEMENT:
			{
				char *ident = the_node->leftmostChild->str_value;
				struct ast_node *expr_node = the_node->leftmostChild->nextSibling;
				struct scarl_symbol_table_entry *the_variable_entry = lookup(st, ident, NULL, 0);
				int expr_infer_type = get_expression_type(st, expr_node);
				if (the_variable_entry->type_flag != expr_infer_type) {
					fprintf(stderr, "Incorrect type near \'%s\' on line %i\n", lastTokenText, lineNumber);
					return 0; //the types do not match up
				}
			}
			break;
			case NON_TERMINAL_WHILE_BLOCK_STATEMENT:
			{
				struct ast_node *expr_node = the_node->leftmostChild;
				int expr_infer_type = get_expression_type(st, expr_node);
				if (expr_infer_type != BOOL) {
					//it needs to be a bool type
					fprintf(stderr, "Incorrect type near \'%s\' on line %i\n", lastTokenText, lineNumber);
					return 0;
				}
			}
			break;
			case NON_TERMINAL_IF_BLOCK_STATEMENT:
			{
				struct ast_node *expr_node = the_node->leftmostChild;
				int expr_infer_type = get_expression_type(st, expr_node);
				if (expr_infer_type != BOOL) {
					//it needs to be a bool type
					fprintf(stderr, "Incorrect type near \'%s\' on line %i\n", lastTokenText, lineNumber);
					return 0;
				}
			}
			break;
			case NON_TERMINAL_BLOCK_STATEMENT:
			{
				int res = types_are_correct(the_node->symbol_table_value, the_node);
				if (res == 0) {
					return 0;
				}
			}
			break;
			default:
			{
				int res = types_are_correct(st, the_node);
				if (res == 0) {
					return 0;
				}
			}
		}

		the_node = the_node->nextSibling;
	}
	return 1;
}