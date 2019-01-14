
#include "linker_util.h"

void read_line(FILE *file, char **buf) {
	int c;
	int i = 0;
	while ((c = getc(file)) != EOF && c != '\n') {
		(*buf)[i] = c;
		i++;
	}
	(*buf)[i] = '\0';
}

void write_line(FILE *file, char **buf) {
	int i = 0;
	while ((*buf)[i] != '\0') {
		fprintf(file, "%c", (*buf)[i]);
		i++;
	}
	fprintf(file, "\n");
}

int is_a_device_declaration(char **ln) {
	char *str = *ln;
	//if it begins with 3 '@' symbols then it is a declaration
	if (strlen(str) > 3) {
		return str[0] == '@' &&
			str[1] == '@' &&
			str[2] == '@';
	}
	return 0;
}

char *get_file_extension(char *fileName) {
	return "not done yet";
}