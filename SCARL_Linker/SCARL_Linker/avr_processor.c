
#include <stdio.h>
#include <stdlib.h>

#include "avr_processor.h"
#include "dmap_info.h"
#include "device_type_map.h"
#include "linker_util.h"

void link_processing_avr_assembler(
	char *assembler_file, 
	char *input_file,
	struct dmap_info *info)
{
	// Transpile / Linking to take place
	FILE *assembler = NULL;
	FILE *input = NULL;
	fopen_s(&assembler, assembler_file, "w");
	fopen_s(&input, input_file, "r");

	write_avr_header(assembler);

	char *ln = (char*)malloc(sizeof(char) * 128);

	//read each ARCL line and then process it
	//similar to how you did it in
	//the arcl_processor.c file
	while (!feof(input)) {
		read_line(input, &ln);
		if (is_a_device_declaration(&ln)) {
			//write the function definitions for the
			//appropriate type

			//extract the identifier name and the device type
			char *device_ident = NULL;
			char *device_type_str = NULL;

			char buf[64];
			int i = 3; //skip the first 3 @
			int buf_index = 0;
			while (ln[i] != '?') {
				buf[buf_index] = ln[i];
				i++;
				buf_index++;
			}
			buf[buf_index] = '\0';
			device_type_str = _strdup(buf);
			i++; // pass the ? 
			buf_index = 0;
			while (ln[i] != '@') {
				buf[buf_index] = ln[i];
				i++;
				buf_index++;
			}
			buf[buf_index] = ' \0';
			device_ident = _strdup(buf);
			int device_type_int_value = atoi(device_type_str);
			free(device_type_str);

			write_avr_procedures_for_device(assembler, device_type_int_value, device_ident, info);
		}
		else {
			//Convert ARCL line to AVR assembler
			//ignore empty lines
			if (strcmp("", ln) != 0) {
				transpile_arcl_instruction_to_avr_assembler(assembler, ln);
			}
		}
	}

	write_avr_footer(assembler);

	free(ln);
	fclose(assembler);
	fclose(input);
}


void write_avr_procedures_for_device(
	FILE *assembler_file,
	int device_type,
	char *device_identifier,
	struct dmap_info *info) {
	
	struct dmap_mapping *mapping = get_mapping(
		info, device_identifier);

	if (mapping == NULL) {
		fprintf(stderr, "FATAL: Missing pin definition for device \"%s\" in .dmap file\n", device_identifier);
		exit(1);
	}
	int pin_number = mapping->pin;

	switch (device_type) {
	case LIGHT_ACTUATOR:
	{
		// on procedure
		

		// off procedure
		

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		
	}
	break;
	case SERVO_ACTUATOR:
	{
		// forward procedure
		

		// backward procedure
		

		// stop procedure
		

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		

	}
	break;
	case SOUND_SENSOR:
	{
		// senseSound procedure
		

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		
	}
	break;
	case LIGHT_SENSOR:
	{
		// senseLight procedure
		


		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		
	}
	break;
	case DISTANCE_SENSOR:
	{
		// senseDistance procedure


		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		
	}
	break;
	case TEMPERATURE_SENSOR:
	{
		// senseTemperature procedure

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		
	}
	break;
	}
}

void transpile_arcl_instruction_to_avr_assembler(
	FILE *assembler, 
	char *arcl_line
) {
	//tokenize
	int token_count = 0;
	char **token_array = NULL;
	token_array = arcl_tokenize(arcl_line, &token_count);
	char *instruction_code = token_array[0];

	if (strcmp("ADD", instruction_code) == 0) {
		char *reg1 = token_array[1];
		char *reg2 = token_array[2];

		fprintf(assembler, "\tADD %s, %s\n",
			atmega_low_register(reg2), atmega_low_register(reg1));
		fprintf(assembler, "\tADC %s, %s\n",
			atmega_high_register(reg2), atmega_high_register(reg1));
	}
	else if (strcmp("SUB", instruction_code) == 0) {
		char *reg1 = token_array[1];
		char *reg2 = token_array[2];

		fprintf(assembler, "\tSUB %s, %s\n",
			atmega_low_register(reg2), atmega_low_register(reg1));
		fprintf(assembler, "\tSBC %s, %s\n",
			atmega_high_register(reg2), atmega_high_register(reg1));
		//now reverse the sign of reg2
		//TO DO
	}
	else if (strcmp("MULT", instruction_code) == 0) {
		//TODO
	}
	else if (strcmp("DIV", instruction_code) == 0) {
		//TODO
	}
	else if (strcmp("FLIP", instruction_code) == 0) {
		char *reg = token_array[1];
		
		//TO DO reverse sign
	}
	else if (strcmp("MOV", instruction_code) == 0) {
		char *src = token_array[1];
		char *dst = token_array[2];

		fprintf(assembler, "\tMOV %s, %s\n",
			atmega_low_register(dst), atmega_low_register(src));
		fprintf(assembler, "\tMOV %s, %s\n",
			atmega_high_register(dst), atmega_high_register(src));
	}
	else if (strcmp("LOADL", instruction_code) == 0) {
		int lit = atoi(token_array[2]);
		char *reg = token_array[1];
		int abs_lit = abs(lit);
		int low = abs_lit % 256;
		int high = abs_lit / 256;
		
		//we can do different things depending on the
		//size of the literal
		if (abs_lit >= 256) {
			fprintf(assembler, "\tLDI %s, %i\n",
				atmega_low_register(reg), low);
			fprintf(assembler, "\tLDI %s, %i\n",
				atmega_high_register(reg), high);
		}
		else {
			//it is small enough to be  in the low end only
			fprintf(assembler, "\tLDI %s, %i\n",
				atmega_low_register(reg), low);
			fprintf(assembler, "\tLDI %s, %i\n",
				atmega_high_register(reg), 0);
		}
		//make negative if it was a negative literal
		if (lit < 0) {
			//TODO reverse the sign
		}
	}
	else if (strcmp("LOADF", instruction_code) == 0) {

	}
	else if (strcmp("LOADR", instruction_code) == 0) {

	}
	else if (strcmp("STORF", instruction_code) == 0) {

	}
	else if (strcmp("STORR", instruction_code) == 0) {

	}
	else if (strcmp("FRAMEU", instruction_code) == 0) {
		// decrement the stack pointer by (offset * 2) bytes
		int offset = atoi(token_array[1]);
		

	}
	else if (strcmp("FRAMEO", instruction_code) == 0) {
		// increment the stack pointer by (offset * 2) bytes

	}
	else if (strcmp("RSAVE", instruction_code) == 0) {

	}
	else if (strcmp("RLOAD", instruction_code) == 0) {

	}
	else if (strcmp("LABEL", instruction_code) == 0) {
		fprintf(assembler, "\t%s:\n", token_array[1]);
	}
	else if (strcmp("PROC", instruction_code) == 0) {
		fprintf(assembler, "%s:\n", token_array[1]);
	}
	else if (strcmp("RET", instruction_code) == 0) {
		fprintf(assembler, "\tRET\n\n");
	}
	else if (strcmp("CALL", instruction_code) == 0) {
		fprintf(assembler, "\tCALL %s\n", token_array[1]);
	}
	else if (strcmp("JMP", instruction_code) == 0) {

	}
	else if (strcmp("CMP", instruction_code) == 0) {
		char *reg1 = token_array[1];
		char *reg2 = token_array[2];

		fprintf(assembler, "\tCP %s, %s\n",
			atmega_low_register(reg2), atmega_low_register(reg1));
		fprintf(assembler, "\tCPC %s, %s\n",
			atmega_high_register(reg2), atmega_high_register(reg1));
	}
	else if (strcmp("JPE", instruction_code) == 0) {

	}
	else if (strcmp("JPNE", instruction_code) == 0) {

	}
	else if (strcmp("JPGR", instruction_code) == 0) {

	}
	else if (strcmp("JPLS", instruction_code) == 0) {

	}
	else if (strcmp("JPGE", instruction_code) == 0) {

	}
	else if (strcmp("JPLE", instruction_code) == 0) {

	}
	else if (strcmp("JAND", instruction_code) == 0) {

	}
	else if (strcmp("JOR", instruction_code) == 0) {

	}
	else if (strcmp("DELAY", instruction_code) == 0) {

	}
	else if (strcmp("OUTPUT", instruction_code) == 0) {

	}
	else if (strcmp("INPUT", instruction_code) == 0) {

	}
	else if (strcmp("WRITE", instruction_code) == 0) {

	}
	else if (strcmp("READ", instruction_code) == 0) {

	}
	else {

	}
	//free tokenized space
	for (int i = 0; i < token_count; i++) {
		free(token_array[i]);
	}
	free(token_array);
}

/* Static table to make these operations faster/better */

char *atmega_registers_table[16] = {
	"r17", "r16", //arcl R0
	"r19", "r18", //arcl R1
	"r21", "r20", //arcl R2
	"r23", "r22", //arcl R3
	"r25", "r24", //arcl R4
	"r27", "r26", //arcl R5
	"r29", "r28", //arcl R6
	"???", "???"  //arcl R7 - using r31 and r30 for frame pointer
};

char *atmega_low_register(char *arcl_register) {
	if (strcmp(arcl_register, "FRR") != 0) {
		int index = arcl_register[1] - '0';
		return atmega_registers_table[index * 2];
	}
	return "unknown";
}

char *atmega_high_register(char *arcl_register) {
	if (strcmp(arcl_register, "FRR") != 0) {
		int index = arcl_register[1] - '0';
		return atmega_registers_table[(index * 2) + 1];
	}
	return "unknown";
}

void write_avr_header(FILE *assembler_file) {
	fprintf(assembler_file, ".cseg\n");
	fprintf(assembler_file, "\n");
	fprintf(assembler_file, "initialize_arcl_exec:\n");
	fprintf(assembler_file, "\tLDI r16,low(RAMEND)\n");
	fprintf(assembler_file, "\tOUT SPL,r16\n");
	fprintf(assembler_file, "\tLDI r17,high(RAMEND)\n");
	fprintf(assembler_file, "\tOUT SPH,r17\n");
	fprintf(assembler_file, "\tMOV r30, r16\t; Low address for frame pointer\n");
	fprintf(assembler_file, "\tMOV r31, r17\t; High address for frame pointer\n");
	fprintf(assembler_file, "\tCALL main_\n\n");
}

void write_avr_footer(FILE *assembler_file) {
	fprintf(assembler_file, ".org initialize_arcl_exec\n");
	fprintf(assembler_file, ".exit\n");
}

