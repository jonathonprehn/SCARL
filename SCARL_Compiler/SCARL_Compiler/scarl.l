
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scarlast.h"
#include "y.tab.h"
#include "visitors.h"
#include "scarlnodestack.h"

unsigned lineNumber = 0;

char *lastTokenText = NULL;

FILE *codeFile = NULL;

struct ast_node *syntax_tree;

//this is the stack of nodes to be used when constructing the program
//to hold on to our terminals in node form to be used for the construction of
//larger subtrees, until we create a full program tree
struct ast_node_stack *node_stack;

struct ast_node_stack *ident_stack;

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
	else if (strcmp(yytext, "SoundSensor") == 0)
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
	char *outputFileName = "code.rc";

	//processing options that may have been passed
	if (argc >= 4) {
		int currentOption = 3;
		while(currentOption < argc) {
			if (strcmp(argv[currentOption], "-o") == 0) {
				//output
				outputFileName = _strdup(argv[currentOption+1]);
				//this option had a parameter
				currentOption++; //so increment once
			}

			//scan for next option
			currentOption++;
		}
	}

	//setting parse input stream to input file
	extern FILE *yyin;
	int fileError;
	fileError = fopen_s(&yyin, argv[1], "r");
	if (fileError != 0) {
		fprintf(stderr, "Error opening source code file %s\n", argv[1]);
		return 1;
	}

	//now we can create the output file
	extern FILE *codeFile;
	fileError = fopen_s(&codeFile, outputFileName, "w");
	if (fileError != 0) {
		fprintf(stderr, "Error opening output code file %s\n", outputFileName);
		return 1;
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

	init_visitor_func_parsing_constructs(); //visitor.h specific

	if (!yyparse()) {
		//hey it parsed according to the grammar correctly
		//say nothing like a real compiler
	}
	else {
		fprintf(stderr, "\nFailed to parse. Check your file.\n");
	}
	
	struct ast_node *should_be_program_node = ast_node_stack_pop(node_stack);
	if (should_be_program_node->type_flag != NON_TERMINAL_PROGRAM) {
		fprintf(stderr, "Fatal application code error: Did not reduce to the program node!");
		return 1;
	}

	//we have the abstract syntax tree!!!!!!!!
	syntax_tree = should_be_program_node;

	//print what we have
	printf("Node stack is\n\n");
	print_node_stack(node_stack);
	printf("Identifier stack is \n\n");
	print_node_stack(ident_stack);

	printf("\nAbstract Syntax Tree:\n");
	print_ast(syntax_tree);

	//now we can process the AST here

	
	

	fclose(codeFile);
	fclose(yyin);
	return 0;
}