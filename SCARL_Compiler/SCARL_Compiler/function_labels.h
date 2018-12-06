#ifndef __SCARL_FUNCTION_LABELS_H__
#define __SCARL_FUNCTION_LABELS_H__

//utility header for the identifier names
//of procedures - used during code generation

#include "scarlast.h"

char *get_procedure_label(struct ast_node *func_node);

char *get_procedure_label_entry(struct scarl_symbol_table_entry *func_entry);

//the string from this function must be removed after use
char *generate_procedure_name_on_the_fly(char *ident, int *paramList, int paramCount);

#endif