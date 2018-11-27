
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scarl_semantic_analysis.h"

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

int types_are_correct(struct ast_node *ast) {
	printf("TODO: static type checking (types_are_correct in scarl_semantic_analysis.c)\n");
	
	return 1;
}