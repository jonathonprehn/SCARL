
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "device_type_map.h"
#include "dmap_info.h"
#include "arcl_processor.h"
#include "avr_processor.h"
#include "linker_util.h"

// Compared to the compiler, the linker is very simple
// we take in a DMAP and RCL file and then insert
// ARCL code into the spaces where the device declaration
// statements were in the original SCARL source file as
// indicated by @@@type?identifier@@@ lines.

int main(int argc, char *argv[]) {

	char *dmap_file = NULL;
	char *arcl_file = NULL;
	char *output_file = "linked_arcl_code.rcl";

	//first we require 1 DMAP file and 1 RCL file
	//search for an output file name as well
	if (argc <= 1) {
		fprintf(stderr, "Error: Need input files\n");
		fprintf(stderr, "scarllink <d-map-file> <arcl-file> { -o <output-file-name> }\n");
	}
	else if (argc == 3) {
		dmap_file = argv[1];
		arcl_file = argv[2];
	}
	else if (argc == 5) {
		dmap_file = argv[1];
		arcl_file = argv[2];
		output_file = argv[4];
	}
	else {
		fprintf(stderr, "Error: input files as shown here:\n");
		fprintf(stderr, "scarllink <d-map-file> <arcl-file> { -o <output-file-name> }\n");
	}

	// this code will be used for when the extension of
	// the output file is an RCL file. A different code 
	// will need to be written for when we want AVR assembler
	// code to be output (.asm extension)

	struct dmap_info *dmap = read_dmap_file(dmap_file);

	char *extension = get_file_extension(output_file);
	printf("Extension is %s\n", extension);

	if (strcmp("rcl", extension) == 0) {
		printf("Linking as ARCL code file\n");
		link_processing_arcl(output_file, arcl_file, dmap);
	}
	else if (strcmp("asm", extension) == 0) {
		printf("Linking as an AVR assembler code file\n");
		link_processing_avr_assembler(output_file, arcl_file, dmap);
	}
	return 0;
}