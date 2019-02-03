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