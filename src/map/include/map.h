#include <stdio.h>
#ifndef _MYMAP_H_
#define _MYMAP_H_

typedef struct Map Map;

void print_map(Map *map);
Btree *insert(Map* map, const char *key, const char *value);
bool exists(Map *map, const char *key);
const char *get(Map *map, const char *key);

#endif