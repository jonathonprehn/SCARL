/*
This file is part of the SCARL toolkit.
 
SCARL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
SCARL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with SCARL.  If not, see <https://www.gnu.org/licenses/>.
*/

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scarlast.h"
#include "y.tab.h"
#include "visitors.h"
#include "scarlnodestack.h"
#include "scarl_symboltable.h"
#include "arcl_codegen.h"
#include "memory_layout.h"
#include "scarl_semantic_analysis.h"

unsigned lineNumber = 0;

char *lastTokenText = NULL;

FILE *codeFile = NULL;

struct ast_node *syntax_tree;

//this is the stack of nodes to be used when constructing the program
//to hold on to our terminals in node form to be used for the construction of
//larger subtrees, until we create a full program tree
struct ast_node_stack *node_stack;

struct ast_node_stack *ident_stack;

//for type checking and tracking program constructs
struct scarl_symbol_table *symbol_table;

struct scarl_symbol_table *current_symbol_table;

void setLastTokenText(char *txt) {
	if (lastTokenText != NULL) {
		free(lastTokenText);
		lastTokenText = NULL;
	}
	lastTokenText = _strdup(txt);
}

%}

letter [a-zA-Z]
digit [0-9]
nonzero_digit [1-9]
binary_digit [01]
octal_digit [0-7]
hex_digit [0-9a-fA-F]

%%

"//".*   { /*Ignore everything for the rest of this line */ }
[ \t]+	{ /* Do nothing for whitespace */ }
[\n]	{ /*Count lines for debug*/ lineNumber++; }
{letter}({letter}|{digit}|".")*	  { 
	//can set up a binary search later
	setLastTokenText(yytext);

	if (strcmp(yytext, "LightActuator") == 0)
	{
		return LIGHT_ACTUATOR;
	}
	else if (strcmp(yytext, "ServoActuator") == 0)
	{
		return SERVO_ACTUATOR; 
	}
	else if (strcmp(yytext, "SoundSensor") == 0)
	{
		return SOUND_SENSOR; 
	}
	else if (strcmp(yytext, "LightSensor") == 0)
	{
		return LIGHT_SENSOR; 
	}
	else if (strcmp(yytext, "DistanceSensor") == 0)
	{
		return DISTANCE_SENSOR; 
	}
	else if (strcmp(yytext, "TemperatureSensor") == 0)
	{
		return TEMPERATURE_SENSOR; 
	}
	else if (strcmp(yytext, "true") == 0)
	{
		return TRUE; 
	}
	else if (strcmp(yytext, "false") == 0)
	{ 
		return FALSE; 
	}
	else if (strcmp(yytext, "bool") == 0)
	{
		return BOOL; 
	}
	else if (strcmp(yytext, "int") == 0)
	{ 
		return INT; 
	} 
	else if (strcmp(yytext, "char") == 0)
	{
		return CHAR; 
	}
	else if (strcmp(yytext, "pointer") == 0)
	{
		return POINTER; 
	}
	else if (strcmp(yytext, "if") == 0)
	{
		return IF; 
	}
	else if (strcmp(yytext, "else") == 0)
	{
		return ELSE; 
	}
	else if (strcmp(yytext, "pointer") == 0)
	{
		return POINTER; 
	}
	else if (strcmp(yytext, "while") == 0)
	{
		return WHILE; 
	}
	else if (strcmp(yytext, "void") == 0)
	{
		return VOID; 
	}
	else if (strcmp(yytext, "return") == 0) 
	{
		return RETURN;
	}
	else if (strcmp(yytext, "platform") == 0) {
		fprintf(stderr, "Cannot use \"platform\" as an identifier. Use something else\n");
		exit(0);
		return 0;
	}
	else
	{ 
		//identifiers get their own stack 
		//this is the only node creation in this file because
		//of the need to preserve the identifer text
		struct ast_node *ident_node = create_node(NULL, IDENTIFIER);
		ident_node->str_value = _strdup(yytext);
		ast_node_stack_push(ident_stack, ident_node);
		return IDENTIFIER;
	} 
}
{nonzero_digit}{digit}*		{ 
	setLastTokenText(yytext);
	return DECIMAL;  
}
("0"){octal_digit}+			{
	setLastTokenText(yytext);
	return OCTAL;
}
("0")("x"|"X"){hex_digit}+	{
	setLastTokenText(yytext);
	return HEX;
}
("0b"){binary_digit}+		{
	setLastTokenText(yytext);
	return BINARY;
}
"0" {/* Weird "just 0" case */
	setLastTokenText(yytext); 
	return DECIMAL; 
}
"+"		{ 
	setLastTokenText(yytext); 
	return PLUS; 
}
"-"		{ 
	setLastTokenText(yytext);
	return MINUS; 
}
"*"		{ 
	setLastTokenText(yytext); 
	return STAR; 
} 
"/"		{ 
	setLastTokenText(yytext); 
	return SLASH; 
}
"!"		{ 
	setLastTokenText(yytext);
	return BANG; 
}
"("		{ 
	setLastTokenText(yytext); 
	return LPAREN; 
}
")"		{ 
	setLastTokenText(yytext); 
	return RPAREN;
} 
">"		{ 
	setLastTokenText(yytext); 
	return GTR; 
}
"<"		{ 
	setLastTokenText(yytext); 
	return LESS; 
}
">="	{ 
	setLastTokenText(yytext); 
	return GTR_EQ; 
}
"<="	{ 
	setLastTokenText(yytext); 
	return LESS_EQ; 
}
"=="	{ 
	setLastTokenText(yytext); 
	return DBL_EQ; 
}
"="		{ 
	setLastTokenText(yytext); 
	return EQ; 
} 
"!="	{ 
	setLastTokenText(yytext); 
	return NOT_EQ; 
}
"||"	{ 
	setLastTokenText(yytext); 
	return OR; 
}
"&&"	{ 
	setLastTokenText(yytext); 
	return AND; 
}
","		{ 
	setLastTokenText(yytext); 
	return COMMA; 
}
";"		{ 
	setLastTokenText(yytext); 
	return SEMICOLON; 
}
"{"		{ 
	/* Scoping controls here with the curly braces */
	struct scarl_symbol_table *new_scope_table = create_symbol_table(NULL);
	add_symbol_table_child(current_symbol_table, new_scope_table);
	current_symbol_table = new_scope_table; //introducing a new scope

	setLastTokenText(yytext); 
	return LBRACE; 
}
"}"		{ 
	setLastTokenText(yytext); 
	return RBRACE; 
}
.       { setLastTokenText(yytext); fprintf(stderr, "unrecognized characters: \'%s\'\n", yytext); }

%%


int yyparse();

int isARCL(char *fileName) {
	//get last dot
	unsigned lastDotIndex = 0;
	unsigned i;
	for (i = 0; i < strlen(fileName); i++) {
		if (fileName[i] == '.') {
			lastDotIndex = i;
		}
	}

	//now start at the last dot and then
	//see if it ends in srl
	//recursive descent style 
	if (fileName[lastDotIndex+1] != '\0' && fileName[lastDotIndex+1] != 'r') {
		return 0;
	}

	if (fileName[lastDotIndex+2] != '\0' && fileName[lastDotIndex+2] != 'c') {
		return 0;
	}

	if (fileName[lastDotIndex+3] != '\0' && fileName[lastDotIndex+3] != 'l') {
		return 0;
	}

	//passed the test for seeing 
	return 1;
}

int hasCorrectExtension(char *fileName) {
	//get last dot
	unsigned lastDotIndex = 0;
	unsigned i;
	for (i = 0; i < strlen(fileName); i++) {
		if (fileName[i] == '.') {
			lastDotIndex = i;
		}
	}

	//now start at the last dot and then
	//see if it ends in srl
	//recursive descent style 
	if (fileName[lastDotIndex+1] != '\0' && fileName[lastDotIndex+1] != 's') {
		return 0;
	}

	if (fileName[lastDotIndex+2] != '\0' && fileName[lastDotIndex+2] != 'r') {
		return 0;
	}

	if (fileName[lastDotIndex+3] != '\0' && fileName[lastDotIndex+3] != 'l') {
		return 0;
	}

	//passed the test for seeing 
	return 1;
}

//wait has special behavior
void add_wait_function_to_symbol_table(struct scarl_symbol_table *symbol_table) {
	char *wait_str = "wait";
	int *paramList = (int*)malloc(sizeof(int));
	paramList[0] = INT;
	struct scarl_symbol_table_entry *wait_entry = create_symbol_table_entry(_strdup(wait_str), VOID, paramList, 1, NULL);

	declare_symbol_table_entry(symbol_table, wait_entry);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "scarlcompile fileName [options]\n");
		return 1;
	}
	if (!hasCorrectExtension(argv[1])) {
		fprintf(stderr, "Must supply a .srl file (you specified %s).\n", argv[1]);
		return 1;
	}

	//figuring out the output file name
	char *outputFileName = "code.rcl";
	int createdTemporarySourceFile = 0;

	//setting parse input stream to input file
	extern FILE *yyin;
	int fileError;

	//1 source file case
	if (argc > 2) {
		//first we need to see if there is an output field
		int outputoptionIndex = -1;
		for (int i = 0; i < argc; i++) {
			if (strcmp("-o", argv[i]) == 0) {
				outputoptionIndex = i;
			}
		}	
		char *givenName = argv[outputoptionIndex+1];
		if (isARCL(givenName)) {
			outputFileName = _strdup(givenName);
		}
		else {
			fprintf(stderr, "Invalid output file (.rcl)\n");
			return 2;
		}

		//we potentially have a bunch of source files. create a temporary file
		if (argc > 4) {
			//we have more than 1 source file so we need to
			//create a tempory source file and concat each
			//of the source files into it
			FILE *temp_src = NULL;
			fileError = fopen_s(&temp_src, "temp", "w");

			for (int j = 1; j < outputoptionIndex; j++) {
				FILE *this_src = NULL;
				fileError = fopen_s(&this_src, argv[j], "r");
				int c = 0;
				c = fgetc(this_src);
				while(!feof(this_src)) {
					fprintf(temp_src, "%c", ((char)c));
					c = fgetc(this_src);
				}
				fclose(this_src);
			}

			fclose(temp_src);
			fileError = fopen_s(&yyin, "temp", "r");
			createdTemporarySourceFile = 1;
		}
		else {
			fileError = fopen_s(&yyin, argv[1], "r");
			if (fileError != 0) {
				fprintf(stderr, "Error opening source code file %s\n", argv[1]);
				return 1;
			}
		}
	}
	else {
		fileError = fopen_s(&yyin, argv[1], "r");
		if (fileError != 0) {
			fprintf(stderr, "Error opening source code file %s\n", argv[1]);
			return 1;
		}
	}

	//set variables for compilation
	lineNumber = 1;

	//syntax tree root initialization
	extern struct ast_node *syntax_tree;
	syntax_tree = NULL;
	extern struct ast_node_stack *node_stack;
	node_stack = create_node_stack(100);
	extern struct ast_node_stack *ident_stack;
	ident_stack = create_node_stack(100);
	extern struct scarl_symbol_table *symbol_table;
	symbol_table = create_symbol_table(NULL);
	extern struct scarl_symbol_table *current_symbol_table;
	current_symbol_table = symbol_table; // for scope tracking

	init_visitor_func_parsing_constructs(); //visitor.h specific


	//add special behavior in before parsing, like the wait() function
	add_wait_function_to_symbol_table(symbol_table);

	if (!yyparse()) {
		//hey it parsed according to the grammar correctly
		//say nothing like a real compiler
	}
	else {
		fprintf(stderr, "\nFailed to parse. Check your file.\n");
		return 1; //error
	}
	
	struct ast_node *should_be_program_node = ast_node_stack_pop(node_stack);
	if (should_be_program_node->type_flag != NON_TERMINAL_PROGRAM) {
		fprintf(stderr, "Fatal application code error: Did not reduce to the program node!");
		return 1;
	}

	//we have the abstract syntax tree!!!!!!!!
	syntax_tree = should_be_program_node;

	//now we can process the AST here
	//you can check the types while the tree is being built
	//symbol tables are built while tree is parsed too

	if (!has_correct_main_method(syntax_tree)) {
		fprintf(stderr, "No main() method or main() method has incorrect signature (must have no formal parameters and its return type must be void)\n");
		return 1;
	}
	
	if (!types_are_correct(symbol_table, syntax_tree)) {
		fprintf(stderr, "Incompatible types (see above)\n");
		return 1;
	}
	
	
	//process symbol tables here
	calculate_frame_sizes(symbol_table);
	calculate_frame_offsets(symbol_table);

	//end of processing before code generation here

	//print what we have
	
	int print_verbose_output = 0;

	if(print_verbose_output) {
		printf("Node stack is\n\n");
		print_node_stack(node_stack);
		printf("Identifier stack is \n\n");
		print_node_stack(ident_stack);

		printf("\nAbstract Syntax Tree:\n");
		print_ast(syntax_tree);

		printf("\nSymbol Table:\n");
		print_symbol_table(symbol_table);
	}

	//now we can create the output file
	extern FILE *codeFile;
	fileError = fopen_s(&codeFile, outputFileName, "w");
	if (fileError != 0) {
		fprintf(stderr, "Error opening output code file %s\n", outputFileName);
		return 1;
	}

	//now we can traverse the tree in post order and generate the code
	generate_arcl_code(codeFile, symbol_table, syntax_tree);

	fclose(codeFile);
	fclose(yyin);

	if (createdTemporarySourceFile) {
		remove("temp");
	}
	return 0;
}