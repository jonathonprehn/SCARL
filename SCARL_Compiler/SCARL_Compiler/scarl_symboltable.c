
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scarl_symboltable.h"
#include "scarlast.h"
#include "scarlnodestack.h"
#include "scarl_type.h"

/*
	struct scarl_symbol_table_entry {
		char *ident;
		int type_flag;
		int *parameterList;
		int parameters;
		struct scarl_symbol_table *st;
		struct scarl_symbol_table *functionSt;
		struct scarl_symbol_table_entry *nextEntry;
	};

	struct scarl_symbol_table {
		struct scarl_symbol_table_entry *entries;
		struct scarl_symbol_table *parentTable;
		struct scarl_symbol_table *firstChildSt;
		struct scarl_symbol_table *nextSiblingSt;
	};
*/

struct scarl_symbol_table *create_symbol_table(struct scarl_symbol_table *parent_table) {
	struct scarl_symbol_table *st = (struct scarl_symbol_table*)malloc(sizeof(struct scarl_symbol_table));
	static int symbol_table_id;
	symbol_table_id++;
	st->tableId = symbol_table_id;
	st->entries = NULL;
	st->parentTable = parent_table;
	st->firstChildSt = NULL;
	st->nextSiblingSt = NULL;
	st->frameSize = 0;
	return st;
}

struct scarl_symbol_table_entry *create_symbol_table_entry(
	char *ident,
	int type_flag,
	int *parameterList,
	int parameterCount,
	struct scarl_symbol_table *symbol_table
) {
	struct scarl_symbol_table_entry *entry = (struct scarl_symbol_table_entry*)malloc(sizeof(struct scarl_symbol_table_entry));
	entry->ident = ident;
	entry->type_flag = type_flag;
	entry->parameterList = parameterList;
	entry->parameters = parameterCount;
	entry->functionSt = symbol_table;
	entry->st = NULL; //we have not been added into a symbol table yet
	entry->nextEntry = NULL;
	entry->frameOffset = 0;
	entry->memSize = get_type_size(type_flag);
	entry->parameterIdentifiers = NULL;
	entry->is_placeholder = 0;
	return entry;
}

void add_symbol_table_child(
	struct scarl_symbol_table *parent_table, 
	struct scarl_symbol_table *child_table) {
	if (parent_table->firstChildSt == NULL) {
		parent_table->firstChildSt = child_table;
		child_table->parentTable = parent_table;
	}
	else {
		//printf("adding to child\n");
		struct scarl_symbol_table *cur_st = parent_table->firstChildSt;
		while (cur_st->nextSiblingSt != NULL) {
			cur_st = cur_st->nextSiblingSt;
		}
		//printf("added child table\n");
		cur_st->nextSiblingSt = child_table;
		child_table->parentTable = parent_table;
		//incremement frame size based on this child's table size
	}
}

int get_type_size(int type) {
	switch (type) {
	default:
		return 1; //assuming everything is 1 value
	}
}

//utility function
int cmp_param_list(int *paramList1, int *paramList2, int paramCount) {
	for (int i = 0; i < paramCount; i++) {
		if (paramList1[i] != paramList2[i]) {
			return 0;
		}
	}
	//is equivalent 
	return 1;
}


int entry_matches_signature(
	struct scarl_symbol_table_entry *entry, 
	char *ident, 
	int paramCount, 
	int *paramList) {
	if (paramCount == 0) {
		return strcmp(entry->ident, ident) == 0 && entry->parameters == paramCount;
	}
	else {
		return strcmp(entry->ident, ident) == 0 &&
			entry->parameters == paramCount &&
			cmp_param_list(entry->parameterList, paramList, paramCount);
	}
	return 0; //no match
}

//if the entry violates any language rules, then it returns an error code,
//otherwise it returns a 0
int declare_symbol_table_entry(
	//the table to add this entry to
	struct scarl_symbol_table *st,
	//the entry to add
	struct scarl_symbol_table_entry *entry
) {
	struct scarl_symbol_table_entry *cur = st->entries;
	if (cur == NULL) {
		st->entries = entry;
		entry->st = st;
	} 
	else {
		while (cur->nextEntry != NULL) {
			cur = cur->nextEntry;
		}
		cur->nextEntry = entry;
		entry->st = st;
	}
	return 1;
}


//this is good for when you are trying to find a variable
//that may have been declared in a more general scope
struct scarl_symbol_table_entry *lookup(
	//the symbol table that is the scope to search from
	struct scarl_symbol_table *st,
	//the string identifier of the symbol to find
	char *ident,
	//the parameter signature of the symbol - part of its definition
	int *paramList,
	//number of parameters. Should be 0 if paramList is NULL. Vice versa.
	int paramCount
) {
	struct scarl_symbol_table_entry *next = st->entries;
	//find it
	while (next != NULL) {
		int match = entry_matches_signature(next, ident, paramCount, paramList);
		if (match) {
			return next;
		}
		else {
			next = next->nextEntry;
		}
	}
	//could not find it
	//is there a parent table?
	if (st->parentTable != NULL) {
		//recursive find
		return lookup(st->parentTable, ident, paramList, paramCount);
	}
	else {
		//no parent table, nowhere to go, we did not find it
		return NULL;
	}
}

//does not search parent tables. This is good for declaration of local variables
struct scarl_symbol_table_entry *lookup_in_scope(
	//the symbol table that is the scope to search from
	struct scarl_symbol_table *st,
	//the string identifier of the symbol to find
	char *ident,
	//the parameter signature of the symbol - part of its definition
	int *paramList,
	//number of parameters. Should be 0 if paramList is NULL. Vice versa.
	int paramCount
) {
	struct scarl_symbol_table_entry *next = st->entries;
	//find it
	while (next != NULL) {
		int match = entry_matches_signature(next, ident, paramCount, paramList);
		if (match) {
			return next;
		}
		else {
			next = next->nextEntry;
		}
	}
	//could not find it
	return NULL;
}

struct scarl_symbol_table_entry *lookup_based_on_invocation_node(
	struct scarl_symbol_table *st,
	struct ast_node *invocation_node
) {
	//first we derive the types of the parameter list
	//by inferring its types

	int parameterCount = 0;
	struct ast_node *param = invocation_node->leftmostChild->nextSibling->leftmostChild;
	while (param != NULL) {
		param = param->nextSibling;
		parameterCount++;
	}

	int *inferred_types = NULL;
	//now we have the number of parameters
	if (parameterCount > 0) {
		inferred_types = malloc(sizeof(int)*parameterCount);
		param = invocation_node->leftmostChild->nextSibling->leftmostChild;
		int i = 0;
		while (param != NULL) {
			//infer based on the expression
			int expr_type_inference = get_expression_type(st, param);
			if (expr_type_inference == -1) {
				printf("An expression has an invalid type (near function invocation for %s)\n", invocation_node->leftmostChild->str_value);
				exit(1);
			}
			inferred_types[i] = expr_type_inference;
			i++;
			param = param->nextSibling;
		}
		
	}
	
	struct scarl_symbol_table_entry *invoc_entry = lookup(st, invocation_node->leftmostChild->str_value, inferred_types, parameterCount);
	if (invoc_entry == NULL) {
		printf("Could not find signature for function \'%s\'. Expected a function with ", invocation_node->leftmostChild->str_value);
		printf("%i parameters of types ", parameterCount);
		for (int i = 0; i < parameterCount; i++) {
			printf("%s, ", get_node_type_str(inferred_types[i]));
		}
	}
	if (inferred_types != NULL) {
		free(inferred_types);
	}
	return invoc_entry;
}

//only prints the entries of a symbol table
void print_symbol_table(struct scarl_symbol_table *st) {
	printf("symbol table id = %i  ", st->tableId);
	if (st->parentTable == NULL) {
		printf("(this is the root table)\n");
	}
	else {
		printf("(parent table id = %i)\n", st->parentTable->tableId);
	}
	if (st->entries == NULL) {
		printf("<empty symbol table>\n");
	}
	else {
		printf("Frame size is %i\n", st->frameSize);
		//print the header
		printf("+");
		for (int i = 0; i < 109; i++) {
			printf("-");
		}
		printf("+\n");
		//ident is 17, 
		printf("| identifier     ");
		//type is 25
		printf("| type                   ");
		//parameters is 13
		printf("| param count ");
		//parameter list is 35
		int paramListSpace = 39;
		printf("| parameter list                       ");
		//frame offset is 15
		printf("| frame offset ");
		//line end is 1
		printf("|\n");
		//total space taken up is 102 characters
		printf("+"); 
		for (int i = 0; i < 109; i++) {
			printf("-");
		}
		printf("+\n");


		//print all entries
		struct scarl_symbol_table_entry *entry = st->entries;
		while (entry != NULL) {
			//print it

			printf("|%-16s", entry->ident);
			printf("|%-24s", get_node_type_str(entry->type_flag));
			printf("|%-13i|", entry->parameters);
			if (entry->parameters > 0) {
				int charsLeft = paramListSpace;
				//ignoring formatting for now
				
				for (int i = 0; i < entry->parameters; i++) {
					char *type_str = get_node_type_str(entry->parameterList[i]);
					charsLeft = charsLeft - (strlen(type_str) + 2);
					
					printf("%s, ", type_str);
				}
				if (charsLeft > 0) {
					for (int i = 0; i < charsLeft-1; i++) {
						printf(" ");
					}
				}
				printf("|");
			}
			else {
				printf("<none>                                |");
			}
			//existence of symbol table
			printf("%-14i|", entry->frameOffset);

			printf("\n");
			entry = entry->nextEntry;
		}
		//print the bottom of this table
		printf("+");
		for (int i = 0; i < 109; i++) {
			printf("-");
		}
		printf("+\n\n");
	}

	//now recursively print this table's child tables

	struct scarl_symbol_table *child_table = st->firstChildSt;
	while (child_table != NULL) {
		print_symbol_table(child_table);
		child_table = child_table->nextSiblingSt;
	}
}

void formal_parameter_node_to_parameter_list(struct ast_node *formal_parameters, int *paramCount, int **paramList, char ***paramIdentList) {

		//counting the number of formal parameters
		struct ast_node *formal_param_node = formal_parameters->leftmostChild;
		while (formal_param_node != NULL) {
			formal_param_node = formal_param_node->nextSibling;
			*paramCount = *paramCount + 1;
		}


		//now allocate space and fill it up with the list of types
		//printf("Allocting %i bytes\n", (sizeof(int) * parameterCounter));

		*paramList = (int*)malloc(sizeof(int) * (*paramCount));
		*paramIdentList = (char**)malloc(sizeof(char*) * (*paramCount));
		formal_param_node = formal_parameters->leftmostChild;
		for (int i = 0; i < *paramCount; i++) {
			(*paramList)[i] = formal_param_node->leftmostChild->int_value;
			(*paramIdentList)[i] = _strdup(formal_param_node->leftmostChild->nextSibling->str_value);
			formal_param_node = formal_param_node->nextSibling;
		}
		//complete list created
}