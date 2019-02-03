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
 
 
 #ifndef __SCARL_DEVICES_PLACEHOLDERS_H__
#define __SCARL_DEVICES_PLACEHOLDERS_H__

#include <stdlib.h>
#include <stdio.h>

#include "scarl_symboltable.h"
#include "scarlast.h"

void add_device_functions_to_symbol_table(char *device_ident, int device_type, struct scarl_symbol_table *table_to_add_to);

#endif