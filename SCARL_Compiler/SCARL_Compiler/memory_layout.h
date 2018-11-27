#ifndef __SCARL_MEMORY_LAYOUT_H__
#define __SCARL_MEMORY_LAYOUT_H__

#include "scarl_symboltable.h"

/*
	Grabs the symbol tables so that they have the correct frame offsets

	Each function definition is a singular frame

	1st pass: frame sizes
	2nd pass: frame offsets

	memory sizes are already characteristics of the entries
	the frame size of the symbol table associated with a function
	is the size of a frame for that function

	parameters are to be included in the stack frame of a function

*/

//process to calculate frame sizes: count the individual pieces
//can be recursive
void calculate_frame_sizes(struct scarl_symbol_table *st);

void calculate_frame_offsets(struct scarl_symbol_table *st);

#endif