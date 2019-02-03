
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arcl_processor.h"
#include "dmap_info.h"
#include "device_type_map.h"
#include "linker_util.h"

//arcl_file is the output file, while the input_fie is the input file
void link_processing_arcl(char *arcl_file, char *input_file, struct dmap_info *info) {
	FILE *arcl = NULL;
	FILE *input = NULL;
	fopen_s(&arcl, arcl_file, "w");
	fopen_s(&input, input_file, "r");

	char *ln = (char*)malloc(sizeof(char)*128);
	//find the lines to insert function definitions (device declarations)
	//and do so using the DMAP information 
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
			while(ln[i] != '@') {
				buf[buf_index] = ln[i];
				i++;
				buf_index++;
			}
			buf[buf_index] = ' \0';
			device_ident = _strdup(buf);
			int device_type_int_value = atoi(device_type_str);
			free(device_type_str);

			write_arcl_procedures_for_device(arcl, device_type_int_value, device_ident, info);
		}
		else {
			//just write the line as it appears
			if (strcmp(ln, "") != 0) {
				write_line(arcl, &ln);
			}
			//don't write an empty line
		}
	}
	
	free(ln);
	fclose(arcl);
	fclose(input);
}


void write_arcl_procedures_for_device(FILE *arcl_file, int device_type, char *device_identifier, struct dmap_info *info) {
	
	struct dmap_mapping *mapping = get_mapping(info, device_identifier);
	
	if (mapping == NULL) {
		fprintf(stderr, "FATAL: Missing pin definition for device \"%s\" in .dmap file\n", device_identifier);
		exit(1);
	}
	int pin_number = mapping->pin;

	switch (device_type) {
	case LIGHT_ACTUATOR:
	{
		// on procedure
		fprintf(arcl_file, "PROC %s.on264_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "LOADF R1 0\n"); //load passed in power level
		fprintf(arcl_file, "WRITE R0 R1\n");
		fprintf(arcl_file, "RET\n");

		// off procedure
		fprintf(arcl_file, "PROC %s.off_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "LOADL R1 0\n"); //load register with 0 power to turn off
		fprintf(arcl_file, "WRITE R0 R1\n");
		fprintf(arcl_file, "RET\n");

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		fprintf(arcl_file, "PROC initialize_%s\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "OUTPUT R0\n");
		fprintf(arcl_file, "RET\n");
	}
		break;
	case SERVO_ACTUATOR:
	{
		// forward procedure
		fprintf(arcl_file, "PROC %s.forward264_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "LOADF R1 0\n"); //load passed in power level
		fprintf(arcl_file, "WRITE R0 R1\n");
		fprintf(arcl_file, "RET\n");

		// backward procedure
		fprintf(arcl_file, "PROC %s.backward264_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "LOADF R1 0\n"); //load passed in power level
		fprintf(arcl_file, "FLIP R1\n"); // negative power indicating other direction ???
		fprintf(arcl_file, "WRITE R0 R1\n");
		fprintf(arcl_file, "RET\n");

		// stop procedure
		fprintf(arcl_file, "PROC %s.stop_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "LOADL R1 0\n"); //load register with 0 power to turn off
		fprintf(arcl_file, "WRITE R0 R1\n");
		fprintf(arcl_file, "RET\n");

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		fprintf(arcl_file, "PROC initialize_%s\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "OUTPUT R0\n");
		fprintf(arcl_file, "RET\n");
	}
		break;
	case SOUND_SENSOR:
	{
		// senseSound procedure
		fprintf(arcl_file, "PROC %s.senseSound_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "READ R0 R1\n"); //read so data goes into R1
		fprintf(arcl_file, "MOV R1 FRR\n"); //put data into return register
		fprintf(arcl_file, "RET\n");

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		fprintf(arcl_file, "PROC initialize_%s\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "INPUT R0\n");
		fprintf(arcl_file, "RET\n");
	}
		break;
	case LIGHT_SENSOR:
	{
		// senseLight procedure
		fprintf(arcl_file, "PROC %s.senseLight_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "READ R0 R1\n"); //read so data goes into R1
		fprintf(arcl_file, "MOV R1 FRR\n"); //put data into return register
		fprintf(arcl_file, "RET\n");


		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		fprintf(arcl_file, "PROC initialize_%s\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "INPUT R0\n");
		fprintf(arcl_file, "RET\n");
	}
		break;
	case DISTANCE_SENSOR:
	{
		// senseDistance procedure
		fprintf(arcl_file, "PROC %s.senseDistance_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "READ R0 R1\n"); //read so data goes into R1
		fprintf(arcl_file, "MOV R1 FRR\n"); //put data into return register
		fprintf(arcl_file, "RET\n");

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		fprintf(arcl_file, "PROC initialize_%s\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "INPUT R0\n");
		fprintf(arcl_file, "RET\n");
	}
		break;
	case TEMPERATURE_SENSOR:
	{
		// senseTemperature procedure
		fprintf(arcl_file, "PROC %s.senseTemperature_\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "READ R0 R1\n"); //read so data goes into R1
		fprintf(arcl_file, "MOV R1 FRR\n"); //put data into return register
		fprintf(arcl_file, "RET\n");

		//configure the pin as output (it is an actuator)
		//using an arbitrary register since ths is an isolated statement
		fprintf(arcl_file, "PROC initialize_%s\n", device_identifier);
		fprintf(arcl_file, "LOADL R0 %i\n", pin_number);
		fprintf(arcl_file, "INPUT R0\n");
		fprintf(arcl_file, "RET\n");
	}
		break;
	}
}