#ifndef __SCARL_DEVICES_PLACEHOLDERS_H__
#define __SCARL_DEVICES_PLACEHOLDERS_H__

#include <stdlib.h>
#include <stdio.h>

#include "scarl_symboltable.h"
#include "scarlast.h"

void add_device_functions_to_symbol_table(char *device_ident, int device_type, struct scarl_symbol_table *table_to_add_to);

#endif