
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dmap_info.h"

struct dmap_info * create_dmap_info(char * platform)
{
	struct dmap_info *info = (struct dmap_info*)malloc(sizeof(struct dmap_info));
	info->platform = _strdup(platform);
	info->mappings = NULL;
	return info;
}

void destroy_dmap_info(struct dmap_info * info)
{
	free(info->platform);
	struct dmap_mapping *cur_map = NULL;
	cur_map = info->mappings;
	while (cur_map != NULL) {
		struct dmap_mapping *to_free = cur_map;
		cur_map = cur_map->next;
		destroy_mapping(to_free);
	}
	free(info);
}

struct dmap_mapping * create_mapping(char * ident, int pin)
{
	struct dmap_mapping *mapping = (struct dmap_mapping*)malloc(sizeof(struct dmap_mapping));
	mapping->ident = _strdup(ident);
	mapping->pin = pin;
	mapping->next = NULL;
	return mapping;
}

void add_mapping(struct dmap_info *info, struct dmap_mapping *mapping) {
	if (info->mappings == NULL) {
		info->mappings = mapping;
	}
	else {
		struct dmap_mapping *cur = info->mappings;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = mapping;
	}
}

void destroy_mapping(struct dmap_mapping * mapping)
{
	free(mapping->ident);
	free(mapping);
}

struct dmap_mapping * get_mapping(struct dmap_info * info, char * by_ident)
{
	struct dmap_mapping *cur = info->mappings;
	while (cur != NULL && strcmp(by_ident, cur->ident) != 0) {
		cur = cur->next;
	}
	return cur;
}

struct dmap_mapping * get_mapping_by_pin(struct dmap_info * info, int by_pin)
{
	struct dmap_mapping *cur = info->mappings;
	while (cur != NULL && cur->pin != by_pin) {
		cur = cur->next;
	}
	return cur;
}

struct dmap_info *read_dmap_file(char *dmap_file_name) {
	struct dmap_info *info = create_dmap_info("default");
	
	FILE *f = NULL;
	fopen_s(&f, dmap_file_name, "r");
	char lhs[64];
	char rhs[64];
	int read_count = 0;
	while (!feof(f)) {
		{
			int c = 0;
			int i = 0;
			while ((c = getc(f)) != EOF && c != '=') {
				lhs[i] = c;
				i++;
				read_count++;
			}
			lhs[i] = '\0';
		}
		{
			int c = 0;
			int i = 0;
			while ((c = getc(f)) != EOF && c != '\n') {
				rhs[i] = c;
				i++;
				read_count++;
			}
			rhs[i] = '\0';
		}

		if (read_count > 0 && strlen(lhs) > 0) {
			if (strcmp(lhs, "platform") == 0) {
				info->platform = _strdup(rhs);
				printf("Platform -> %s\n", rhs);
			}
			else {
				int pin_number = atoi(rhs);
				struct dmap_mapping *mapping = create_mapping(lhs, pin_number);
				add_mapping(info, mapping);
				printf("Mapping: %s -> %i\n", lhs, pin_number);
			}
		}
	}
	fclose(f);
	return info;
}