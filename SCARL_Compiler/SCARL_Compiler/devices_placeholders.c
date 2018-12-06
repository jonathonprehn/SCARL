
#include <string.h>
#include <stdarg.h> 

#include "devices_placeholders.h"
#include "function_labels.h"

char *generate_device_func_ident(char *device_ident, char *func_name) {
	char *fin = NULL;
	int fin_size = strlen(device_ident) + strlen(func_name) + 2;
	fin = (char*)malloc(sizeof(char) * fin_size);
	int i = 0;
	for (int k = 0; k < strlen(device_ident); k++) {
		fin[i] = device_ident[k];
		i++;
	}
	fin[i++] = '.'; //important
	for (int k = 0; k < strlen(func_name); k++) {
		fin[i] = func_name[k];
		i++;
	}
	fin[i] = '\0';
	return fin;
}

int *create_param_list(int paramCount, ...) {
	va_list args;
	va_start(args, paramCount);
	int *ls = (int*)malloc(sizeof(int)*paramCount);
	for (int i = 0; i < paramCount; i++) {
		ls[i] = va_arg(args, int);
	}
	va_end(args);
	return ls;
}

struct scarl_symbol_table_entry * add_function_block_with_local_vars_setup(
	struct scarl_symbol_table *parentTable,
	char *ident,
	int returnType,
	int varCount,
	...
) { /* type name, type name, ... */
	va_list args;
	va_start(args, varCount);
	int localVariableCount = varCount / 2;
	struct scarl_symbol_table *func_symbol_table = create_symbol_table(parentTable);
	int *paramList = (int*)malloc(sizeof(int) * localVariableCount);
	char **identList = (char**)malloc(sizeof(char*) * localVariableCount);
	for (int i = 0; i < localVariableCount; i++) {
		int local_var_type = va_arg(args, int);
		char *var_name = va_arg(args, char*);
		paramList[i] = local_var_type;
		identList[i] = _strdup(var_name); //what da fuck
		struct scarl_symbol_table_entry *local_var = create_symbol_table_entry(_strdup(var_name), local_var_type, NULL, 0, NULL);
		declare_symbol_table_entry(func_symbol_table, local_var);
	}

	struct scarl_symbol_table_entry *the_entry = create_symbol_table_entry(
		ident, returnType,
		paramList, localVariableCount, NULL);
	the_entry->parameterIdentifiers = identList;
	the_entry->is_placeholder = 1;
	the_entry->functionSt = func_symbol_table;
	va_end(args);
	return the_entry;
}

char **create_ident_list(int valCount, ...) {
	va_list args;
	va_start(args, valCount);
	char **ls = (char**)malloc(sizeof(char*) * valCount);
	for (int i = 0; i < valCount; i++) {
		ls[i] = _strdup(va_arg(args, char*));
	}
	va_end(args);
	return ls;
}

//need to create the symbol tables for these
//functions that are not yet implemented
//so the generated code can properly call them
//for when the procecures are 
//properly linked (added to the program)

void add_device_functions_to_symbol_table(
	char *device_ident, 
	int device_type, 
	struct scarl_symbol_table *table_to_add_to)
{
	//these functions shall be in the symbol table but not
	//in the actual AST, so arcl_codegen will not catch them
	//however, after a device declaration, the 
	//device declarations generate TODO labels that asks
	//scarllink to generate the functions that the device will use
	//device declarations are essentially a shorthand for the declaration
	//of the functions that will control the said device. The device identifier
	//is never used as an identifier for anything except to define functions
	switch (device_type) {
	case LIGHT_ACTUATOR:
	{
		char *on_func = generate_device_func_ident(device_ident, "on");
		char *off_func = generate_device_func_ident(device_ident, "off");
		int *temp_list = NULL;
	
		//now declare them in the symbol table

		//create the symbol table for the function to declare and add the anticipated local variable info to it
		{
			declare_symbol_table_entry(
				table_to_add_to,
				add_function_block_with_local_vars_setup(
					table_to_add_to,
					on_func,
					VOID, //return type
					2, //1 local variable from 2 parameters 
					INT, "power"
				)
			);
		}
		
		{
			//empty symbol table but have it anyway
			struct scarl_symbol_table *off_symbol_table = create_symbol_table(table_to_add_to);
			struct scarl_symbol_table_entry *off_func_entry = create_symbol_table_entry(off_func, VOID, NULL, 0, NULL);
			off_func_entry->functionSt = off_symbol_table;
			off_func_entry->is_placeholder = 1;
			declare_symbol_table_entry(
				table_to_add_to,
				off_func_entry
			);
		}


		//the identifiers are now used in the function table so we don't need
		//to delete them
	}
	break;
	case SERVO_ACTUATOR:
	{
		char *forward_ident = generate_device_func_ident(device_ident, "forward");
		char *backward_ident = generate_device_func_ident(device_ident, "backward");
		char *stop_ident = generate_device_func_ident(device_ident, "stop");

		declare_symbol_table_entry(
			table_to_add_to,
			add_function_block_with_local_vars_setup(
				table_to_add_to,
				forward_ident,
				VOID, //return type
				2, //1 local variable from 2 parameters 
				INT, "power"
			)
		);

		declare_symbol_table_entry(
			table_to_add_to,
			add_function_block_with_local_vars_setup(
				table_to_add_to,
				backward_ident,
				VOID, //return type
				2, //1 local variable from 2 parameters 
				INT, "power"
			)
		);

		declare_symbol_table_entry(
			table_to_add_to,
			add_function_block_with_local_vars_setup(
				table_to_add_to,
				stop_ident,
				VOID, //return type
				0
			)
		);
	}
	break;
	case SOUND_SENSOR:
	{
		char *sound_ident = generate_device_func_ident(device_ident, "senseSound");
		declare_symbol_table_entry(
			table_to_add_to,
			add_function_block_with_local_vars_setup(
				table_to_add_to,
				sound_ident,
				VOID, //return type
				0
			)
		);
	}
	break;
	case LIGHT_SENSOR:
	{
		char *light_ident = generate_device_func_ident(device_ident, "senseLight");
		declare_symbol_table_entry(
			table_to_add_to,
			add_function_block_with_local_vars_setup(
				table_to_add_to,
				light_ident,
				VOID, //return type
				0
			)
		);
	}
	break;
	case DISTANCE_SENSOR:
	{
		char *distance_ident = generate_device_func_ident(device_ident, "senseDistance");
		declare_symbol_table_entry(
			table_to_add_to,
			add_function_block_with_local_vars_setup(
				table_to_add_to,
				distance_ident,
				VOID, //return type
				0
			)
		);
	}
	break;
	case TEMPERATURE_SENSOR:
	{
		char *temperature_ident = generate_device_func_ident(device_ident, "senseTemperature");
		declare_symbol_table_entry(
			table_to_add_to,
			add_function_block_with_local_vars_setup(
				table_to_add_to,
				temperature_ident,
				VOID, //return type
				0
			)
		);
	}
	break;
	}
}
