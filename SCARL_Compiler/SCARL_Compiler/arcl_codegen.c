
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
char *frr = "FRR";

// TODO: Return statements must be implemented!

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
	printf("No registers left. check your code\n");
	return NO_REGISTER; //could not find a register
} 

void free_register(int reg)
{
	arcl_registers[reg] = 0;
}

char * register_str(int reg)
{
	if (reg == ARCL_FRR_REGISTER) {
		return frr;
	}
	else {
		return arcl_registers_symbols[reg];
	}
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
	char *str = (char*)malloc(sizeof(char)*10);
	sprintf_s(str, 10, "_L%i", label);
	return str;
}


//lazy programming with a global
//to keep track of temporary frame offset for stacking variables
//when generating a function call related to the current frame
int additionalFrameOffset = 0;


void pass_to_expression_generator_handler(FILE *output, struct scarl_symbol_table *symbol_table, struct ast_node *expr, int primitiveType) {
	//we know that this is the global scope
	//store in global ("static") storage
	if (primitiveType == INT) {
		generate_arcl_arithmetic_expression(output, symbol_table, expr);
	}
	else if (primitiveType == BOOL) {
		generate_arcl_bool_expression(output, symbol_table, expr);
	}
	else if (primitiveType == CHAR) {
		fprintf(output, "!! Char types are not supported yet !!\n");
	}
	else if (primitiveType == POINTER) {
		fprintf(output, "!! Pointer types are not supported yet !!\n");
	}
	else {
		fprintf(output, "!! Invalid primitive type (how did that happen?): %i !!\n", primitiveType);
	//	print_ast(expr);
	//	printf("\n\n");
	}
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
				fprintf(stderr, "FATAL ERROR: Symbol table for function %s was not correctly passed down\n", ast->leftmostChild->leftmostChild->nextSibling->str_value);
				exit(1);
			}

			struct scarl_symbol_table_entry *function_entry = NULL;

			//code gen
			fprintf(output, "PROC %s\n", proc_label);

			// Special behavior for procedure main
			// this is the only procedure that is responsible for 
			// setting up its own frame since it
			// does not have a callee to do that for it
			char *ident_name = ast->leftmostChild->leftmostChild->nextSibling->str_value;
			if (strcmp(ident_name, "main") == 0) {
				// get main function entry
				function_entry = lookup(symbol_table, ident_name, NULL, 0);
				// set up own stack frame as the main procedure
				fprintf(output, "FRAMEU %i\n", function_entry->functionSt->frameSize);
			}
			generate_statements_in_block(output, func_symbol_table, block_statement);
			if (strcmp(ident_name, "main") == 0) {
				// unstack own frame as main procedure
				fprintf(output, "FRAMEO %i\n", function_entry->functionSt->frameSize);
			}
			fprintf(output, "RET\n"); //to end the function
		}
		break;
		case NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT:
		{
			//first we evaluate the expression to store as the primitive
			struct ast_node *prim_decl = ast->leftmostChild;
			struct ast_node *expr = prim_decl->nextSibling;
			int type = prim_decl->leftmostChild->int_value;
			struct scarl_symbol_table_entry *prim_entry = lookup(symbol_table, prim_decl->leftmostChild->nextSibling->str_value, NULL, 0);

			pass_to_expression_generator_handler(output, symbol_table, expr, type);

			//we know this was in global scope

			//the result of the expression is in the expression's register 1
			//store result into static storage. frameOffset is its location in static memory in this context
			fprintf(output, "STORR %s %i\n", register_str(expr->register1), prim_entry->frameOffset);
			free_register(expr->register1); //no longer need this register
		}
		break;
		case NON_TERMINAL_DEVICE_DECLARATOR_STATEMENT:
		{
			struct ast_node *device_type = ast->leftmostChild;
			struct ast_node *ident = device_type->nextSibling;
			fprintf(output, "@@@%i?%s@@@\n", device_type->int_value, ident->str_value);
		}
		break;
	}
}

void generate_arcl_arithmetic_expression(FILE * output, struct scarl_symbol_table * symbol_table, struct ast_node * ast)
{
	//we expect some kind of operation
	switch (ast->type_flag) {
	case BINARY: 
	{
		int r = allocate_register();
		fprintf(output, "LOADL %s %i\n", register_str(r), ast->int_value);
		ast->register1 = r;
	}
		break;
	case HEX: 
	{
		int r = allocate_register();
		fprintf(output, "LOADL %s %i\n", register_str(r), ast->int_value);
		ast->register1 = r;
	}
		break;
	case OCTAL: 
	{
		int r = allocate_register();
		fprintf(output, "LOADL %s %i\n", register_str(r), ast->int_value);
		ast->register1 = r;
	}
		break;
	case DECIMAL: 
	{
		int r = allocate_register();
		fprintf(output, "LOADL %s %i\n", register_str(r), ast->int_value);
		ast->register1 = r;
	}
		break;
	case IDENTIFIER: 
	{
		struct scarl_symbol_table_entry *ident_entry = lookup(symbol_table, ast->str_value, NULL, 0);
		//the entry should have the memory location
		//of this object
		
		//TO DO: locate this identifier in memory

		/*
			Considerations:
			- on an activation record or in global memory?
		*/

		int memOffset = 0;
		int r = allocate_register();
	
		if (ident_entry == NULL) {
			printf("Could not find identifier %s\n", ast->str_value);
		}

		if (ident_entry->st == NULL) {
			printf("No symbol table on the symbol table entry (%s)\n", ast->str_value);
		}

		if (ident_entry->st->parentTable == NULL) {
			//this is the root table. it is in global memory
			memOffset = ident_entry->frameOffset;
			fprintf(output, "LOADR %s %i\n", register_str(r), memOffset);
		}
		else {
			//this is in the stack frame
			memOffset = ident_entry->frameOffset; 
			fprintf(output, "LOADF %s %i\n", register_str(r), memOffset+additionalFrameOffset);
		}
		ast->register1 = r;
	}
		break; 
	case PLUS: 
	{
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);
		//now add these two values together
		fprintf(output, "ADD %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		//left hand side is no longer needed
		free_register(lhs->register1);
		ast->register1 = rhs->register1; //result stored in this register
	}
		break;
	case MINUS: 
	{
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);
		//now add these two values together
		fprintf(output, "SUB %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		//left hand side is no longer needed
		free_register(lhs->register1);
		ast->register1 = rhs->register1; //result stored in this register
	}
		break;
	case STAR: 
	{
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);
		//now add these two values together
		fprintf(output, "MULT %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		//left hand side is no longer needed
		free_register(lhs->register1);
		ast->register1 = rhs->register1; //result stored in this register
	}
	break;
	case SLASH: 
	{
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);
		//now add these two values together
		fprintf(output, "DIV %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		//left hand side is no longer needed
		free_register(lhs->register1);
		ast->register1 = rhs->register1; //result stored in this register
	}
	break;
	case NON_TERMINAL_FUNCTION_INVOCATION:
	{
		generate_arcl_function_invocation(output, symbol_table, ast);
		//we expect that this function has returned something
		//it should be in the FRR register. Save the result to a register
		int r = allocate_register();
		fprintf(output, "MOV %s %s\n", register_str(ARCL_FRR_REGISTER), register_str(r));
		ast->register1 = r;
	}
	break;
	}
}

void generate_arcl_bool_expression(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast
) {
	switch(ast->type_flag) {
	case NON_TERMINAL_BOOL_VALUE:
	{
		//just load the value into a register
		int r = allocate_register();
		fprintf(output, "LOADL %s %i\n", register_str(r), ast->int_value);
		ast->register1 = r;
	}
	break;
	case NON_TERMINAL_FUNCTION_INVOCATION:
	{
		generate_arcl_function_invocation(output, symbol_table, ast);
		//we expect that this function has returned something
		//it should be in the FRR register. Save the result to a register
		int r = allocate_register();
		fprintf(output, "MOV %s %s\n", register_str(ARCL_FRR_REGISTER), register_str(r));
		ast->register1 = r;
	}
	break;
	case BANG:
	{
		//operation to flip boolean value
		//basically, if false set to true if true set to false

		int label1 = generate_label();
		int label2 = generate_label();

		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		struct ast_node *expr = ast->leftmostChild; //only 1 child that is a boolean expression
		generate_arcl_bool_expression(output, symbol_table, expr);
		int r = expr->register1;

		//temporary register to load a 0 into it
		int temp_zero = allocate_register();
		fprintf(output, "LOADL %s 0\n", register_str(temp_zero));
		fprintf(output, "CMP %s %s\n", register_str(r), register_str(temp_zero));
		fprintf(output, "JPE %s\n", label1_str); //if false
		fprintf(output, "LOADL %s 0\n", register_str(r)); //it is true, so load the register with false
		fprintf(output, "JMP %s\n", label2_str); //skip to end since we already set it
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //it is false so load it with true
		fprintf(output, "LABEL %s\n", label2_str);

		free_register(temp_zero);
		ast->register1 = r; //pass the register up

		free(label1_str);
		free(label2_str);
	}
	break;
	/*
		General form of boolean expressions with
		arithmetic expressions:

		calculate lhs
		calculate rhs
		cmp lhs rhs
		jump to label1 if true
		loadl register 0   ; false
		jmp label2
		label1
		loadl register 1   ; true
		label2

	*/
	
	case LESS:
	{
		
		//each side is an arithmetic expression
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		int label1 = generate_label();
		int label2 = generate_label();
		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		//generate code for the evaluation of the arithmetic expressions
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);

		fprintf(output, "CMP %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		free_register(lhs->register1);
		int r = rhs->register1; //reuse this register

		//this is where things are going to change a bit between comparators
		//jump to label1 if the comparator evaluates to true
		fprintf(output, "JPLS %s\n", label1_str);

		//setting it to true or false depending on the jump value

		fprintf(output, "LOADL %s 0\n", register_str(r)); //false
		fprintf(output, "JMP %s\n", label2_str);
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //true
		fprintf(output, "LABEL %s\n", label2_str);

		free(label1_str);
		free(label2_str);
		//result of boolean (sub)expression in the given register
		ast->register1 = r; 
	}
	break;
	case LESS_EQ:
	{
		//each side is an arithmetic expression
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		int label1 = generate_label();
		int label2 = generate_label();
		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		//generate code for the evaluation of the arithmetic expressions
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);

		fprintf(output, "CMP %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		free_register(lhs->register1);
		int r = rhs->register1; //reuse this register

		//this is where things are going to change a bit between comparators
		//jump to label1 if the comparator evaluates to true
		fprintf(output, "JPLE %s\n", label1_str);

		//setting it to true or false depending on the jump value

		fprintf(output, "LOADL %s 0\n", register_str(r)); //false
		fprintf(output, "JMP %s\n", label2_str);
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //true
		fprintf(output, "LABEL %s\n", label2_str);

		free(label1_str);
		free(label2_str);
		//result of boolean (sub)expression in the given register
		ast->register1 = r;
	}
	break;
	case GTR:
	{
		//each side is an arithmetic expression
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		int label1 = generate_label();
		int label2 = generate_label();
		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		//generate code for the evaluation of the arithmetic expressions
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);

		fprintf(output, "CMP %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		free_register(lhs->register1);
		int r = rhs->register1; //reuse this register

		//this is where things are going to change a bit between comparators
		//jump to label1 if the comparator evaluates to true
		fprintf(output, "JPGR %s\n", label1_str);

		//setting it to true or false depending on the jump value

		fprintf(output, "LOADL %s 0\n", register_str(r)); //false
		fprintf(output, "JMP %s\n", label2_str);
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //true
		fprintf(output, "LABEL %s\n", label2_str);

		free(label1_str);
		free(label2_str);
		//result of boolean (sub)expression in the given register
		ast->register1 = r;
	}
	break;
	case GTR_EQ:
	{
		//each side is an arithmetic expression
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		int label1 = generate_label();
		int label2 = generate_label();
		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		//generate code for the evaluation of the arithmetic expressions
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);

		fprintf(output, "CMP %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		free_register(lhs->register1);
		int r = rhs->register1; //reuse this register

		//this is where things are going to change a bit between comparators
		//jump to label1 if the comparator evaluates to true
		fprintf(output, "JPGE %s\n", label1_str);

		//setting it to true or false depending on the jump value

		fprintf(output, "LOADL %s 0\n", register_str(r)); //false
		fprintf(output, "JMP %s\n", label2_str);
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //true
		fprintf(output, "LABEL %s\n", label2_str);

		free(label1_str);
		free(label2_str);
		//result of boolean (sub)expression in the given register
		ast->register1 = r;
	}
	break;
	case DBL_EQ:
	{
		//each side is an arithmetic expression
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		int label1 = generate_label();
		int label2 = generate_label();
		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		//generate code for the evaluation of the arithmetic expressions
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);

		fprintf(output, "CMP %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		free_register(lhs->register1);
		int r = rhs->register1; //reuse this register

		//this is where things are going to change a bit between comparators
		//jump to label1 if the comparator evaluates to true
		fprintf(output, "JPE %s\n", label1_str);

		//setting it to true or false depending on the jump value

		fprintf(output, "LOADL %s 0\n", register_str(r)); //false
		fprintf(output, "JMP %s\n", label2_str);
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //true
		fprintf(output, "LABEL %s\n", label2_str);

		free(label1_str);
		free(label2_str);
		//result of boolean (sub)expression in the given register
		ast->register1 = r;
	}
	break;
	case NOT_EQ:
	{
		//each side is an arithmetic expression
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		int label1 = generate_label();
		int label2 = generate_label();
		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		//generate code for the evaluation of the arithmetic expressions
		generate_arcl_arithmetic_expression(output, symbol_table, lhs);
		generate_arcl_arithmetic_expression(output, symbol_table, rhs);

		fprintf(output, "CMP %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		free_register(lhs->register1);
		int r = rhs->register1; //reuse this register

		//this is where things are going to change a bit between comparators
		//jump to label1 if the comparator evaluates to true
		fprintf(output, "JPNE %s\n", label1_str);

		//setting it to true or false depending on the jump value

		fprintf(output, "LOADL %s 0\n", register_str(r)); //false
		fprintf(output, "JMP %s\n", label2_str);
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //true
		fprintf(output, "LABEL %s\n", label2_str);

		free(label1_str);
		free(label2_str);
		//result of boolean (sub)expression in the given register
		ast->register1 = r;
	}
	break;
	case AND:
	{
		//each side is a boolean expression
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		int label1 = generate_label();
		int label2 = generate_label();
		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		//generate the code for each of these expressions
		generate_arcl_bool_expression(output, symbol_table, lhs);
		generate_arcl_bool_expression(output, symbol_table, rhs);

		//AND operation similar to what was done in previous bool expressions

		fprintf(output, "CMP %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		free_register(lhs->register1);
		int r = rhs->register1; //reuse this register

		//this is where things are going to change a bit between comparators
		//jump to label1 if the comparator evaluates to true
		fprintf(output, "JAND %s\n", label1_str);

		//setting it to true or false depending on the jump value

		fprintf(output, "LOADL %s 0\n", register_str(r)); //false
		fprintf(output, "JMP %s\n", label2_str);
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //true
		fprintf(output, "LABEL %s\n", label2_str);

		free(label1_str);
		free(label2_str);
		//result of boolean (sub)expression in the given register
		ast->register1 = r;
	}
	break;
	case OR:
	{

		//each side is a boolean expression
		struct ast_node *lhs = ast->leftmostChild;
		struct ast_node *rhs = lhs->nextSibling;
		int label1 = generate_label();
		int label2 = generate_label();
		char *label1_str = label_str(label1);
		char *label2_str = label_str(label2);

		//generate the code for each of these expressions
		generate_arcl_bool_expression(output, symbol_table, lhs);
		generate_arcl_bool_expression(output, symbol_table, rhs);

		//AND operation similar to what was done in previous bool expressions

		fprintf(output, "CMP %s %s\n", register_str(lhs->register1), register_str(rhs->register1));
		free_register(lhs->register1);
		int r = rhs->register1; //reuse this register

		//this is where things are going to change a bit between comparators
		//jump to label1 if the comparator evaluates to true
		fprintf(output, "JOR %s\n", label1_str);

		//setting it to true or false depending on the jump value

		fprintf(output, "LOADL %s 0\n", register_str(r)); //false
		fprintf(output, "JMP %s\n", label2_str);
		fprintf(output, "LABEL %s\n", label1_str);
		fprintf(output, "LOADL %s 1\n", register_str(r)); //true
		fprintf(output, "LABEL %s\n", label2_str);

		free(label1_str);
		free(label2_str);
		//result of boolean (sub)expression in the given register
		ast->register1 = r;
	}
	break;
	case IDENTIFIER:
	{
		struct scarl_symbol_table_entry *ident_entry = lookup(symbol_table, ast->str_value, NULL, 0);
		//the entry should have the memory location
		//of this object

		/*
		Considerations:
		- on an activation record or in global memory?
		*/

		int memOffset = 0;
		int r = allocate_register();

		if (ident_entry == NULL) {
			printf("Could not find identifier %s\n", ast->str_value);
		}

		if (ident_entry->st == NULL) {
			printf("No symbol table on the symbol table entry (%s)\n", ast->str_value);
		}

		if (ident_entry->st->parentTable == NULL) {
			//this is the root table. it is in global memory
			memOffset = ident_entry->frameOffset;
			fprintf(output, "LOADR %s %i\n", register_str(r), memOffset);
		}
		else {
			//this is in the stack frame
			memOffset = ident_entry->frameOffset;
			fprintf(output, "LOADF %s %i\n", register_str(r), memOffset + additionalFrameOffset);
		}
		ast->register1 = r;
	}
	break;
	}
}

void generate_arcl_function_invocation(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast
) {
	//Big TO DO:
	//we are assuming that the types have already been checked and confirmed
	generate_arcl_register_save(output, symbol_table, ast);
	
	//set parameters 
	//to do this we need to evaluate all of the expressions as they are and then
	//set the parameters from the offsets from those expressions
	struct scarl_symbol_table_entry *function_entry = NULL;
	
	//now we have the characteristics of the function, can we find it?

	//we have the function invocation node (ast)
	function_entry = lookup_based_on_invocation_node(symbol_table, ast);

	if (function_entry == NULL) {
		printf("ERROR: cannot generate function call for the identifier for it (%s, see types) does not exist\n", ast->leftmostChild->str_value);
	}
	else if (strcmp(function_entry->ident, "wait") == 0) {
		//wait has special behavior
		//generate the parameter (this is a function invocation)
		struct ast_node *parameter_list_node = ast->leftmostChild->nextSibling;
		struct ast_node *cur_param = parameter_list_node->leftmostChild;

		//there is only one parameter for wait()
		generate_arcl_arithmetic_expression(output, symbol_table, cur_param);

		fprintf(output, "DELAY %s\n", register_str(cur_param->register1));
		free_register(cur_param->register1);
	}
	else {

		//setup parameters and frame
		if (function_entry->functionSt->frameSize > 0) {
			fprintf(output, "FRAMEU %i\n", function_entry->functionSt->frameSize);
		}
		// not necessary to move frame pointer if frame size is 0

		struct ast_node *parameter_list_node = ast->leftmostChild->nextSibling;
		//now evaluate the expressions for each one and then stack the
		//parameters in order
		struct ast_node *cur_param = parameter_list_node->leftmostChild;

		if (cur_param != NULL) {
			int param_index = 0;
			//this is the only time this global needs to be changed
			additionalFrameOffset = 8 + function_entry->functionSt->frameSize;
			while (cur_param != NULL) {
				//we need to propogate a frame offset here because the variables
				//in use in the parent stack frame are now farther away by
				//8 + functionTableSize
				pass_to_expression_generator_handler(
					output, 
					function_entry->functionSt,
					cur_param,
					function_entry->parameterList[param_index]
				);
				//store it on the function stack before calling
				int parameterOffsetVal = 0; //how to get this if it
				//it treated as a local variable in the symbol table
				//what is the original identifier for this parameter?
				//we got the identifiers of the parameters
				char *formal_parameter_identifier = function_entry->parameterIdentifiers[param_index];
				//lookup the formal parameter in the function scope and
				//then use that offset
				struct scarl_symbol_table_entry *formal_parameter_entry = lookup(function_entry->functionSt, formal_parameter_identifier, NULL, 0);
				if (formal_parameter_entry == NULL) {
					printf("ERROR in code generation - the formal parameter %s is not in the function scope\n", formal_parameter_identifier);
				}
				parameterOffsetVal = formal_parameter_entry->frameOffset;

				fprintf(output, "STORF %s %i\n", register_str(cur_param->register1), parameterOffsetVal);
				free_register(cur_param->register1);
				param_index++;
				cur_param = cur_param->nextSibling;
			}
			//make things back to normal after the parameters are stacked
			additionalFrameOffset = 0;
		}

		//transfer control. the parameters should be in the desired location now
		//we need to find out how to create the procedure label from just
		//the parameters and the function call
		if (function_entry->is_placeholder) {
			char *proc_label_fly = generate_procedure_name_on_the_fly(function_entry->ident, function_entry->parameterList, function_entry->parameters);
			fprintf(output, "CALL %s\n", proc_label_fly);
			free(proc_label_fly);
		}
		else {
			char *proc_label_to_call = get_procedure_label_entry(function_entry);
			if (proc_label_to_call == NULL) {
				fprintf(stderr, "No such defined function \'%s\'\n", function_entry->ident);
			}
			fprintf(output, "CALL %s\n", proc_label_to_call);
		}

		//unstack function frame
		if (function_entry->functionSt->frameSize > 0) {
			fprintf(output, "FRAMEO %i\n", function_entry->functionSt->frameSize);
		}
	}

	//restore
	generate_arcl_register_load(output, symbol_table, ast);
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
				generate_statements_in_block(output, cur_block_statement->symbol_table_value, cur_block_statement);
			}
			break;
			case NON_TERMINAL_FUNCTION_INVOCATION_STATEMENT:
			{
				//the only child is a function invocation
				generate_arcl_function_invocation(output, symbol_table, cur_block_statement->leftmostChild);
			}
			break;
			case NON_TERMINAL_PRIMITIVE_DEFINITION_STATEMENT:
			{
				//first we evaluate the expression to store as the primitive
				struct ast_node *prim_decl = cur_block_statement->leftmostChild;
				struct ast_node *expr = prim_decl->nextSibling;
				int type = prim_decl->leftmostChild->int_value;
				char *ident = prim_decl->leftmostChild->nextSibling->str_value;
				struct scarl_symbol_table_entry *prim_entry = lookup(symbol_table, ident, NULL, 0);

				pass_to_expression_generator_handler(output, symbol_table, expr, type);

				//the result of the expression is in the expression's register 1
				//store result into static storage. frameOffset is its location in static memory in this context
				fprintf(output, "STORF %s %i\n", register_str(expr->register1), prim_entry->frameOffset);
				free_register(expr->register1); //no longer need this register
			}
			break;
			case NON_TERMINAL_VARIABLE_SET_STATEMENT:
			{
				char *ident = cur_block_statement->leftmostChild->str_value;
				struct scarl_symbol_table_entry *entry = lookup(symbol_table, ident, NULL, 0);
				int type = entry->type_flag;
				struct ast_node *expr = cur_block_statement->leftmostChild->nextSibling;

				pass_to_expression_generator_handler(output, symbol_table, expr, type);
				//load the value of the expression into the spot of the variable
				
				//considerations: is it in global scope or local scope?
				if (entry->st->parentTable == NULL) {
					///global scope
					fprintf(output, "STORR %s %i\n", register_str(expr->register1), entry->frameOffset);
				}
				else {
					//local scope
					fprintf(output, "STORF %s %i\n", register_str(expr->register1), entry->frameOffset+additionalFrameOffset);
				}
				//no longer need this register
				free_register(expr->register1);
			}
			break;
			case NON_TERMINAL_IF_BLOCK_STATEMENT:
			{
				struct ast_node *expr_node = cur_block_statement->leftmostChild;
				struct ast_node *if_block = expr_node->nextSibling;
				struct ast_node *else_block = if_block->nextSibling;
				
				if (else_block == NULL) {
					//if without else
					generate_arcl_bool_expression(output, symbol_table, expr_node);
					int label1 = generate_label();
					char *label1_str = label_str(label1);

					//temporary register to load a 0 into it
					int temp_zero = allocate_register();
					fprintf(output, "LOADL %s 0\n", register_str(temp_zero));
					fprintf(output, "CMP %s %s\n", register_str(expr_node->register1), register_str(temp_zero)); //check to see if expression is true
					free_register(expr_node->register1);

					//if the value is false, jump, otherwise execute
					fprintf(output, "JPE %s\n", label1_str);
					//execute if true
					generate_statements_in_block(output, if_block->symbol_table_value, if_block);
					fprintf(output, "LABEL %s\n", label1_str); //place to jump to if false

					free_register(temp_zero);
					free(label1_str);
				}
				else {
					//if with else

					generate_arcl_bool_expression(output, symbol_table, expr_node);
					int label1 = generate_label();
					int label2 = generate_label();
					char *label1_str = label_str(label1);
					char *label2_str = label_str(label2);

					int temp_zero = allocate_register();
					fprintf(output, "LOADL %s 0\n", register_str(temp_zero));
					fprintf(output, "CMP %s %s\n", register_str(expr_node->register1), register_str(temp_zero)); //check to see if expression is true
					free_register(expr_node->register1);
					fprintf(output, "JPE %s\n", label1_str); //jump to false area if equal to false
					//otherwise execute true area
					generate_statements_in_block(output, if_block->symbol_table_value, if_block);
					fprintf(output, "JMP %s\n", label2_str);
					fprintf(output, "LABEL %s\n", label1_str);
					//false area here
					generate_statements_in_block(output, else_block->symbol_table_value, else_block);
					fprintf(output, "LABEL %s\n", label2_str); //where to skip to after true statements

					free_register(temp_zero);
					
					free(label1_str);
					free(label2_str);
				}
			}
			break;
			case NON_TERMINAL_WHILE_BLOCK_STATEMENT:
			{
				struct ast_node *expr_node = cur_block_statement->leftmostChild;
				struct ast_node *block_node = expr_node->nextSibling;
				
				int label1 = generate_label();
				int label2 = generate_label();
				char *label1_str = label_str(label1);
				char *label2_str = label_str(label2);
				
				fprintf(output, "LABEL %s\n", label1_str);
				generate_arcl_bool_expression(output, symbol_table, expr_node);
				//check to see if the expression is false
				int temp_zero = allocate_register();
				fprintf(output, "LOADL %s 0\n", register_str(temp_zero));
				fprintf(output, "CMP %s %s\n", register_str(expr_node->register1), register_str(temp_zero));
				free_register(expr_node->register1);
				//if false, skip to the end
				fprintf(output, "JPE %s\n", label2_str);
				//not false, the expression was true. Run the block
				generate_statements_in_block(output, block_node->symbol_table_value, block_node);
				//completed the block. evaluate the boolean expr again
				fprintf(output, "JMP %s\n", label1_str);
				//go here when the expression is true
				fprintf(output, "LABEL %s\n", label2_str);
				
				free_register(temp_zero);

				free(label1_str);
				free(label2_str);
			}
			break;
			case NON_TERMINAL_RETURN_STATEMENT:
			{
				//Copy the value in the expression register
				//to FRR and call a RET instruction to stop
				//the function where it stands

				//The type is the return type of the current function.
				//how do we know which function we are currently in?

				struct ast_node *expr_node = cur_block_statement->leftmostChild;

				//we expect that the parent of this block
				//eventually becomes a NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT
				struct ast_node *func_def_node = ast;
				while ((func_def_node = func_def_node->parent)->type_flag != NON_TERMINAL_FUNCTION_DEFINITION_STATEMENT) {
					//repeat until we find the function definition
				}
				//we found the function definition. the return type is 
				//based on the primitive declarator node
				int return_type = func_def_node->leftmostChild->leftmostChild->int_value;
				//printf("return type is %s\n", get_terminal_mnemonic(return_type));

				pass_to_expression_generator_handler(output, symbol_table, expr_node, return_type);
				// copy this return into the FRR register
				fprintf(output, "MOVE %s %s\n", register_str(expr_node->register1), register_str(ARCL_FRR_REGISTER));
				free_register(expr_node->register1);

				//TO DO - do not add this if it is the last statement in the block
				if (cur_block_statement->nextSibling != NULL) {
					fprintf(output, "RET\n");
				}
			}
			break;
		}
		cur_block_statement = cur_block_statement->nextSibling;
	}
}

//to be done before function invocation
void generate_arcl_register_save(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast
) {
	//save register state
	fprintf(output, "RSAVE\n");
}

//to be done after function invocation
void generate_arcl_register_load(
	FILE *output,
	struct scarl_symbol_table *symbol_table,
	struct ast_node *ast
) {
	//restore register state
	fprintf(output, "RLOAD\n");
}