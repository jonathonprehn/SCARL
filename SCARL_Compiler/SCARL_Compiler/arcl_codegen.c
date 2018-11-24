
#include <stdio.h>
#include <string.h>

#include "arcl_codegen.h"
#include "function_labels.h"

//the in use table
int arcl_registers[ARCL_REGISTER_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
//the table of register symbols
char *arcl_registers_symbols[ARCL_REGISTER_COUNT] = {
	"R0", "R1",
	"R2", "R3",
	"R4", "R5",
	"R6", "R7"
};

//allocate a 1 byte register
int allocate_register()
{
	int i = 0;
	while (i < ARCL_REGISTER_COUNT) {
		if (arcl_registers[i] == 0) {
			arcl_registers[i] = 1;
			return i;
		}
		i++;
	}
	return NO_REGISTER; //could not find a register
} 

void free_register(int reg)
{
	arcl_registers[reg] = 0;
}

char * register_str(int reg)
{
	return arcl_registers_symbols[reg];
}

int generate_label() {
	static int label_count = 0;
	int lbl = label_count;
	label_count++;
	return lbl;
}

//allocates a new string on the heap so be sure to remove
//it when you are done with it
char *label_str(int label) {
	char str[10];
	sprintf_s(str, 10, ".L%i", label);
	return _strdup(str);
}

//global scope code generation (static memory is the working space)
void generate_arcl_code(FILE * output, struct scarl_symbol_table * symbol_table, struct ast_node * ast)
{
	//post order traversal of all the nodes
	//left-right-center
	
	switch (ast->type_flag) {
		case NON_TERMINAL_PROGRAM: 
		{
			//contains a list of statements at the global
			//level:
			//device declarator, primitive definition, function definition
			struct ast_node *cur_node = ast->leftmostChild;
			//goo goo
			while (cur_node != NULL) {
				generate_arcl_code(output, symbol_table, cur_node);
				cur_node = cur_node->nextSibling;
			}
		}
		break;
		case NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT:
		{
			//define a procedure with the same
			//name as the identifier with the param
			//types appended to it
		
			char *proc_label = get_procedure_label(ast);
			struct ast_node *block_statement = ast->leftmostChild->nextSibling->nextSibling;
			struct scarl_symbol_table *func_symbol_table = block_statement->symbol_table_value;
			if (func_symbol_table == NULL) {
				fprintf("FATAL ERROR: Symbol table for function %s was not correctly passed down\n", ast->leftmostChild->leftmostChild->nextSibling->str_value);
				exit(1);
			}
			//code gen
			fprintf(output, "PROC %s\n", proc_label);
			generate_statements_in_block(output, func_symbol_table, block_statement);
			fprintf(output, "RET\n"); //to end the function
		}
		break;
		case NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT:
		{
			fprintf(output, "TODO: Generate primitive definition statement in global scope\n");
		}
		break;
		case NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT:
		{
			fprintf(output, "TODO: Generate device declaration statement in global scope\n");
		}
		break;
	}
}

void generate_arcl_arithmetic_expression(FILE * output, struct scarl_symbol_table * symbol_table, struct ast_node * ast)
{
	//we expect some kind of operation
	switch (ast->type_flag) {
	case BINARY: {
		fprintf(output, "PUSHL %i\n", ast->int_value);
	}
		break;
	case HEX: {
		fprintf(output, "PUSHL %i\n", ast->int_value);
	}
		break;
	case OCTAL: {
		fprintf(output, "PUSHL %i\n", ast->int_value);
	}
		break;
	case DECIMAL: {
		fprintf(output, "PUSHL %i\n", ast->int_value);
	}
		break;
	case IDENTIFIER: {
		struct scarl_symbol_table_entry *ident_entry = lookup(symbol_table, ast->str_value, NULL, 0);
		//the entry should have the memory location
		//of this object
		
		//TO DO: locate this identifier in memory
		int memOffset = 0;
		
		int r = allocate_register;
		fprintf(output, "LOADF %s %i\n", register_str(r), memOffset);
		ast->register1 = r;
	}
		break; 
	case PLUS: {
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);
		//now add these two values together
		fprintf(output, "ADD"); //it is expected that these
								//values are on the stack
	}
		break;
	case MINUS: {
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);
		//now add these two values together
		fprintf(output, "SUB"); //it is expected that these
								//values are on the stack
	}
		break;
	case STAR: {
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);
		//now add these two values together
		fprintf(output, "MULT"); //it is expected that these
								//values are on the stack
	}
		break;
	case SLASH: {
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);
		//now add these two values together
		fprintf(output, "DIV"); //it is expected that these
								//values are on the stack
	}
		break;
	}
}

void generate_arcl_if_statement(FILE * output, struct scarl_symbol_table * symbol_table, struct ast_node * ast)
{

}

void generate_arcl_while_statement(FILE * output, struct scarl_symbol_table * symbol_table, struct ast_node * ast)
{

}

void generate_arcl_primitive_definition_statement(FILE * output, struct scarl_symbol_table * symbol_table, struct ast_node * ast)
{

}

void generate_arcl_function_statement(FILE * output, struct scarl_symbol_table * symbol_table, struct ast_node * ast)
{
	//do I really need this?
}

//local scope code generation (we are in stack frames)
void generate_statements_in_block(FILE * output, struct scarl_symbol_table * symbol_table, struct ast_node * ast)
{
	//we have the block statement node
	//and we also have the symbol table for this block in hand

	struct ast_node *cur_block_statement = ast->leftmostChild;
	while (cur_block_statement != NULL) {
		switch (cur_block_statement->type_flag) {
			case NON_TERMINAL_BLOCK_STATEMENT:
			{
				//TO DO: setup memory management
				generate_statements_in_block(output, cur_block_statement->symbol_table_value, cur_block_statement);
			}
			break;
			case NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT:
			{

			}
			break;
			case NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT:
			{

			}
			break;
			case NON_TERMINAL_VARIABLE_SET_STATEMENT:
			{

			}
			break;
			case NON_TERMINAL_IF_BLOCK_STATEMENT:
			{

			}
			break;
			case NON_TERMINAL_WHILE_BLOCK_STATEMENT:
			{

			}
			break;
		}
		cur_block_statement = cur_block_statement->nextSibling;
	}
}
