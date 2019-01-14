#ifndef __SCARL_DMAP_INFO_H__
#define __SCARL_DMAP_INFO_H__

struct dmap_mapping;

struct dmap_info {
	char *platform;
	struct dmap_mapping *mappings;
};

struct dmap_mapping {
	char *ident;
	int pin;
	struct dmap_mapping *next;
};

struct dmap_info *create_dmap_info(char *platform);
void destroy_dmap_info(struct dmap_info *info);
struct dmap_mapping *create_mapping(char *ident, int pin);
void destroy_mapping(struct dmap_mapping *mapping);
struct dmap_mapping *get_mapping(struct dmap_info *info, char *by_ident);
struct dmap_mapping *get_mapping_by_pin(struct dmap_info *info, int by_pin);
struct dmap_info *read_dmap_file(char *dmap_file_name);

#endif