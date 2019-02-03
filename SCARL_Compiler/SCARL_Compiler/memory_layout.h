/*
 *  This file is part of the SCARL toolkit.
 *  
 *  SCARL is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  SCARL is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with SCARL.  If not, see <https://www.gnu.org/licenses/>.
 */
 
 
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