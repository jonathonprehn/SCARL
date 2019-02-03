
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

char *get_file_extension(char *file_name) {
	// just find the last period and
	// make a string to copy it into
	int last_dot = 0;
	int i = 0;
	while (file_name[i] != '\0') {
		if (file_name[i] == '.') {
			last_dot = i;
		}
		i++;
	}
	char *extension = (char*)malloc(sizeof(char) * (i - last_dot));
	i = last_dot + 1;
	while (file_name[i] != '\0') {
		extension[i - (last_dot + 1)] = file_name[i];
		i++;
	}
	extension[i - (last_dot + 1)] = '\0';
	return extension;
}

char** arcl_tokenize(char *src_line, int *arr_length) {	
	int token_count = 1;
	int i = 0;
	while (src_line[i] != '\0') {
		if (src_line[i] == ' ') {
			token_count++;
		}
		i++;
	}

	// number of spaces + 1 == number of tokens
	int *lengths = (int*)malloc(sizeof(int) * token_count);
	for (int l = 0; l < token_count; l++) {
		lengths[l] = 0;
	}
	int t = 0;
	i = 0;
	while (src_line[i] != '\0') {
		if (src_line[i] == ' ') {
			//we know the character count for token 't'
			t++;
		}
		else {
			lengths[t]++;
		}
		i++;
	}

	//initialize token array
	char **token_array = (char**)malloc(sizeof(char*)*token_count);
	for (int r = 0; r < token_count; r++) {
		token_array[r] = (char*)malloc(sizeof(char)*(lengths[r] + 1));
	}

	t = 0;
	i = 0;
	int b = 0;
	while (src_line[i] != '\0') {
		if (src_line[i] == ' ') {
			//we know the character count for token 't'
			token_array[t][b] = '\0';
			b = 0;
			t++;
		}
		else {
			token_array[t][b] = src_line[i];
			b++;
		}
		i++;
	}
	//the last token needs to have a NULL delimiter
	token_array[t][b] = '\0';

	free(lengths);
	*arr_length = token_count;
	return token_array;
}