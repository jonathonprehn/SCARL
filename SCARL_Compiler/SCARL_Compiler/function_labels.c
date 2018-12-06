
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function_labels.h"

struct function_label_mapping;

struct function_label_mapping {
	struct ast_node *func_node;
	char *procedure_label;
	struct function_label_mapping *next;
};

//we have a table of preconstructed identifiers to check first
struct function_label_mapping *procedure_label_list = NULL;

struct function_label_mapping *find_mapping(struct ast_node *func_node) {
	struct function_label_mapping *mp = procedure_label_list;
	if (mp == NULL) {
		return NULL;
	}
	else {
		while (mp != NULL) {
			if (mp->func_node == func_node) {
				return mp;
			}
			mp = mp->next;
		}
		return NULL;
	}
}

struct function_label_mapping *find_mapping_entry(struct scarl_symbol_table_entry *func_entry) {
	struct function_label_mapping *mp = procedure_label_list;
	if (mp == NULL) {
		return NULL;
	}
	else {
		while (mp != NULL) {
			//we are going to see if this mapping can match
			//the given function entry
			struct ast_node *fn = mp->func_node;
			char *fn_ident = fn->leftmostChild->leftmostChild->nextSibling->str_value;
			struct ast_node *fn_param = fn->leftmostChild->nextSibling->leftmostChild;
			int i = 0;
			if (strcmp(func_entry->ident, fn_ident) == 0) {
				//now we need to see if the param
				//types match up
				while (fn_param != NULL) {
					if (func_entry->parameterList[i] == fn_param->leftmostChild->int_value) {
						i++;
					}
					else {
						fn_param = NULL;
					}
				}
				if (i == func_entry->parameters) {
					return mp; //they must be the same
				}
			}
			mp = mp->next;
		}
		return NULL;
	}
}

struct function_label_mapping *add_mapping(struct ast_node *func_node) {
	//construct the procedure string here
	char *proc_label = NULL;

	struct ast_node *ch = func_node->leftmostChild;
	char *ident_str = ch->leftmostChild->nextSibling->str_value;
	struct ast_node *fpl = ch->nextSibling; //now we are on the formal parameter list
	ch = ch->nextSibling->nextSibling; //block statement
	
	int space_for_types = 0;
	struct ast_node *cur_fp = fpl->leftmostChild;
	if (cur_fp != NULL) {
		char temp[10];
		while (cur_fp != NULL) {
			_itoa_s(cur_fp->type_flag, temp, 10, 10);
			space_for_types = space_for_types + strlen(temp) + 1; //append underscore
			cur_fp = cur_fp->nextSibling;
		}
	}
	else {
		//append an underscore to identifier name
		space_for_types = 1;
	}

	//now create the actual label
	int char_nums = (strlen(ident_str) + space_for_types);
	proc_label = (char*)malloc(sizeof(char) * char_nums + 1);
	//now copy over
	for (int i = 0; i < strlen(ident_str); i++) {
		proc_label[i] = ident_str[i];
	}
	if (space_for_types == 1) {
		proc_label[char_nums-1] = '_';
		proc_label[char_nums] = '\0';
	}
	else {
		cur_fp = fpl->leftmostChild;
		int i = strlen(ident_str);
		while (cur_fp != NULL) {
			char temp[10];
			_itoa_s(cur_fp->type_flag, temp, 10, 10);
			int len = strlen(temp);
			for (int k = 0; k < len; k++) {
				proc_label[i + k] = temp[k];
			}
			proc_label[i + len] = '_';
			i = i + len + 1;
			cur_fp = cur_fp->nextSibling;
		}
		proc_label[char_nums] = '\0';
	}
	//procedure label constructed
	//create mapping
	struct function_label_mapping *new_mapping = (struct function_label_mapping*)malloc(sizeof(struct function_label_mapping));
	new_mapping->func_node = func_node;
	new_mapping->procedure_label = proc_label;
	new_mapping->next = NULL;

	//now append this mapping to the list
	if (procedure_label_list == NULL) {
		procedure_label_list = new_mapping;
	}
	else {
		struct function_label_mapping *mp = procedure_label_list;
		while (mp->next != NULL) {
			mp = mp->next;
		}
		mp->next = new_mapping; //added
	}

	//return it the thing we just added
	return new_mapping;
}

char *get_procedure_label(struct ast_node *func_node) {
	struct function_label_mapping *label_mapping = find_mapping(func_node);
	if (label_mapping == NULL) {
		label_mapping = add_mapping(func_node);
		return label_mapping->procedure_label;
	}
	else {
		return label_mapping->procedure_label;
	}
}

char *get_procedure_label_entry(struct scarl_symbol_table_entry *func_entry) {
	struct function_label_mapping *label_mapping = find_mapping_entry(func_entry);
	if (label_mapping == NULL) {
		return NULL;
	}
	return label_mapping->procedure_label;
	
}

//the string from this function must be removed after use
char *generate_procedure_name_on_the_fly(char *ident, int *paramList, int paramCount) {
	char *proc_label = NULL;
	
	int space_for_types = 0;
	int i = 0;
	if (paramCount > 0) {
		for (i = 0; i < paramCount; i++) {
			char temp[10];
			_itoa_s(paramList[i], temp, 10, 10);
			space_for_types = space_for_types + strlen(temp) + 1; //append underscore
		}
	}
	else {
		//append an underscore to identifier name
		space_for_types = 1;
	}

	//now create the actual label
	int char_nums = (strlen(ident) + space_for_types);
	proc_label = (char*)malloc(sizeof(char) * char_nums + 1);
	//now copy over
	for (int i = 0; i < strlen(ident); i++) {
		proc_label[i] = ident[i];
	}
	if (space_for_types == 1) {
		proc_label[char_nums - 1] = '_';
		proc_label[char_nums] = '\0';
	}
	else {
		int i = strlen(ident);
		for (int p = 0; p < paramCount; p++) {
			char temp[10];
			_itoa_s(paramList[p], temp, 10, 10);
			int len = strlen(temp);
			for (int k = 0; k < len; k++) {
				proc_label[i + k] = temp[k];
			}
			proc_label[i + len] = '_';
			i = i + len + 1;
		}
		proc_label[char_nums] = '\0';
	}
	return proc_label;
}

