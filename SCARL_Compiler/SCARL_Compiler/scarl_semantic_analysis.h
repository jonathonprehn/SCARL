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
 
 
 #ifndef __SCARL_SEMANTIC_ANALYSIS_H__
#define __SCARL_SEMANTIC_ANALYSIS_H__

#include "scarlast.h"

//verify that the program has a main method with the
//correct signature
int has_correct_main_method(struct ast_node *ast);

int types_are_correct(struct scarl_symbol_table *st, struct ast_node *ast);

#endif