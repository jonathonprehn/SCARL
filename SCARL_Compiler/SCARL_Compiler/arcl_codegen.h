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
	struct ast_node *ast);

void generate_arcl_if_statement(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast);

void generate_arcl_while_statement(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast);

void generate_arcl_primitive_definition_statement(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast);

void generate_arcl_function_statement(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast);

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
