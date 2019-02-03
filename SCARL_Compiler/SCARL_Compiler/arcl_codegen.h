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
 
 
 #ifndef __ARCL_CODE_GEN_H__
#define __ARCL_CODE_GEN_H__

#define ARCL_REGISTER_COUNT 8
#define NO_REGISTER -1
#define ARCL_FRR_REGISTER 100

#include <stdlib.h>
#include <stdio.h>

#include "scarlast.h"
#include "scarlnodestack.h"
#include "scarl_symboltable.h"

//registers for the machine
int allocate_register();

void free_register(int reg);

char *register_str(int reg);

int generate_label();

char *label_str(int label);

void generate_arcl_code(FILE *output, struct scarl_symbol_table *symbol_table, struct ast_node *abstract_syntax_tree);

//specialized statement generation
void generate_arcl_arithmetic_expression(
	FILE *output, 
	struct scarl_symbol_table *symbol_table, 
	struct ast_node *ast);

void generate_arcl_bool_expression(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast
);

void generate_statements_in_block(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast);

void generate_arcl_function_invocation(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast);

void generate_arcl_register_save(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast);

void generate_arcl_register_load(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast);


#endif
