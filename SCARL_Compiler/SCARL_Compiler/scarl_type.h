#ifndef __SCARL_TYPE_H__
#define __SCARL_TYPE_H__

#include "scarlast.h"

//infer the expression type from the node for the
//purpose of statically checking the type of the expression
//in our semantic analysis stage. Can also be used when
//trying to match the signature of a function call 
//(use on the function parameters)
int get_expression_type(struct scarl_symbol_table *symbol_table, struct ast_node *expr);

#endif