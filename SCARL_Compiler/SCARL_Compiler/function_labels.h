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