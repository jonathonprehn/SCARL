#ifndef __SCARL_LINKER_UTIL_H__
#define __SCARL_LINKER_UTIL_H__

#include <stdio.h>

void read_line(FILE *file, char **buf);
void write_line(FILE *file, char **buf);
int is_a_device_declaration(char **ln);
char *get_file_extension(char *fileName);

#endif