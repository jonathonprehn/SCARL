#ifndef __ARCL_AVR_PROCESSOR_H__
#define __ARCL_AVR_PROCESSOR_H__

void write_avr_procedures_for_device(FILE *assembler_file, int device_type, char *device_identifier, struct dmap_info *info);
void link_processing_avr_assembler(char *assembler_file, char *input_file, struct dmap_info *info);
void transpile_arcl_instruction_to_avr_assembler(FILE *assembler, char *arcl_line);
char *atmega_low_register(char *arcl_register);
char *atmega_high_register(char *arcl_register);
void write_avr_header(FILE *assembler_file);
void write_avr_footer(FILE *assembler_file);

#endif