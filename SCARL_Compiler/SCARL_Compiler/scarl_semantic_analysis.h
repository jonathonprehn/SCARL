#ifndef __SCARL_SEMANTIC_ANALYSIS_H__
#define __SCARL_SEMANTIC_ANALYSIS_H__

#include "scarlast.h"

//verify that the program has a main method with the
//correct signature
int has_correct_main_method(struct ast_node *ast);

int types_are_correct(struct scarl_symbol_table *st, struct ast_node *ast);

#endif