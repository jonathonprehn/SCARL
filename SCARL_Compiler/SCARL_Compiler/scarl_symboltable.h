#ifndef __SCARL_SYMBOL_TABLE_H__
#define __SCARL_SYMBOL_TABLE_H__

#include "scarlast.h"

struct scarl_symbol_table;
struct scarl_symbol_table_entry;

struct scarl_symbol_table_entry {
	//the name of this symbol
	char *ident;
	//the type of the entry. Denotes return type if a function
	int type_flag;
	//the list of formal parameters if function type.
	//the parameterList not being null denotes a function
	int *parameterList;
	//identifiers of parameters for the code generation part
	char **parameterIdentifiers;
	//count of params
	int parameters;
	//the symbol table that this entry resides in
	struct scarl_symbol_table *st;
	//the symbol table for the body of this function if this denotes a function type
	struct scarl_symbol_table *functionSt;
	//the next symbol table entry in the list
	struct scarl_symbol_table_entry *nextEntry;
	
	//code generation varables
	int frameOffset; //applicable to local variables only
	int memSize; //applicable to local variables only

	int is_placeholder; //for device function placeholders
};

struct scarl_symbol_table {
	int tableId; //for debugging purposes only
	//the list of symbol table entries in this table
	struct scarl_symbol_table_entry *entries;
	//the parent table is null if this is the root table
	struct scarl_symbol_table *parentTable;
	//this is a pointer to the list of children symbol tables 
	//to construct the symbol table tree
	struct scarl_symbol_table *firstChildSt;
	//the next sibling in the list of symbol table siblings (from a symbol table parent)
	struct scarl_symbol_table *nextSiblingSt;

	int frameSize; // the size of this symbol table
};

struct scarl_symbol_table *create_symbol_table(struct scarl_symbol_table *parent_table);

struct scarl_symbol_table_entry *create_symbol_table_entry(
		char *ident,
		int type_flag,
		//the parameter list for if this is a function
		int *parameterList,
		//the parameter count for if this is a function
		int parameterCount,
		//the symbol table for if this is a function
		struct scarl_symbol_table *symbol_table
	);

void formal_parameter_node_to_parameter_list(struct ast_node *formal_param_node, int *paramCont, int **paramList, char ***paramIdentifiers);

int get_type_size(int type);

int entry_matches_signature(struct scarl_symbol_table_entry *entry, char *ident, int paramCount, int *paramList);

//if the entry violates any language rules, then it returns an error code,
//otherwise it returns a 0
int declare_symbol_table_entry(
	//the table to add this entry to
	struct scarl_symbol_table *st, 
	//the entry to add
	struct scarl_symbol_table_entry *entry
	);


void add_symbol_table_child(
	struct scarl_symbol_table *parent_table, 
	struct scarl_symbol_table *child_table
);

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
	);

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
);

struct scarl_symbol_table_entry *lookup_based_on_invocation_node(
	struct scarl_symbol_table *st, 
	struct ast_node *invocation_node
);

void print_symbol_table(struct scarl_symbol_table *st);

#endif
