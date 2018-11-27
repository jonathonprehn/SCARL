
#include <stdlib.h>
#include <stdio.h>

#include "scarl_symboltable.h"
#include "memory_layout.h"

int get_total_tables_size(struct scarl_symbol_table *table_to_get_for) {
	int frame_size = 0;
	struct scarl_symbol_table_entry *entry = table_to_get_for->entries;
	while (entry != NULL) {
		frame_size += get_type_size(entry->type_flag);
		entry = entry->nextEntry;
	}
	//now recursively add the child tables to this one
	struct scarl_symbol_table *child_table = table_to_get_for->firstChildSt;
	while (child_table != NULL) {
		frame_size += get_total_tables_size(child_table);
		child_table = child_table->nextSiblingSt;
	}
	table_to_get_for->frameSize = frame_size;
	return frame_size;
}

void calculate_frame_sizes_function(struct scarl_symbol_table *functionSt, int callee_param, int *callee_paramList) {
	//add the parameters to the size of the function block
	//for the expectation of stacking parameters
	struct scarl_symbol_table_entry *entry = functionSt->entries;
	int frame_size = 0;

	if (callee_param > 0) {
		for (int i = 0; i < callee_param; i++) {
			functionSt->frameSize += get_type_size(callee_paramList[i]);
		}
	}

	int functionSt_frameSize = get_total_tables_size(functionSt);
	//functionSt->frameSize += functionSt_frameSize;
}

void calculate_frame_sizes(struct scarl_symbol_table *st) {
	int frame_size = 0;
	struct scarl_symbol_table_entry *entry = NULL;

	entry = st->entries;
	while (entry != NULL) {
		if (entry->functionSt == NULL) {
			frame_size += get_type_size(entry->type_flag);
		}
		else {
			calculate_frame_sizes_function(entry->functionSt, entry->parameters, entry->parameterList);
		}

		entry = entry->nextEntry;
	}

	st->frameSize = frame_size;

	//second pass, we want to get all functions and then add the
	//sub symbol tables to the total frame size of their symbol
	//tables so that we have the following aggregate frame sizes
	//
	//1. global space needed
	//2. space needed for each function stack frame

}

//assuming this table and all others are in the 
//same stack frame
void subtable_frame_offsets(int *offset, struct scarl_symbol_table *parent) {
	//first calculate the offets for this table
	struct scarl_symbol_table_entry *entry = parent->entries;
	while (entry != NULL) {
		entry->frameOffset = *offset;
		*offset = *offset + 1;
		entry = entry->nextEntry;
	}
	//now do it for each subtable
	struct scarl_symbol_table *subtable = parent->firstChildSt;
	while (subtable != NULL) {
		subtable_frame_offsets(offset, subtable);
		subtable = subtable->nextSiblingSt;
	}
}

void calculate_frame_offsets(struct scarl_symbol_table *st) {
	int cur_frame_offset = 0;
	struct scarl_symbol_table_entry *entry = NULL;

	//remember, each function has a single stack frame for
	//its execution
	entry = st->entries;
	int globalOffset = 0;
	while (entry != NULL) {
		if (entry->functionSt == NULL) {
			entry->frameOffset = globalOffset;
			globalOffset++;
		}
		else {
			//frame relative offsets
			int offset = 0;

			//allocate space for parameter offsets
			entry->parameterOffsets = (int*)malloc(sizeof(int) * entry->parameters);

			//first we stack parameter offsets
			for (int i = 0; i < entry->parameters; i++) {
				entry->parameterOffsets[i] = offset;
				offset++;
			}
			//now the rest of the offsets
			subtable_frame_offsets(&offset, entry->functionSt);
		}

		entry = entry->nextEntry;
	}
}

