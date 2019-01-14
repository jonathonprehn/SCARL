#ifndef __ARCL_PROCESSOR_H__
#define __ARCL_PROCESSOR_H__

void link_processing_arcl(char *arcl_file, char *input_file, struct dmap_info *info);
void write_arcl_procedures_for_device(FILE *arcl_file, int device_type, char *device_identifier, struct dmap_info *info);

#endif