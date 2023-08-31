#include <string.h>
#include "map.h"


typedef struct BTree {
    const char *key;
    const char *value;
    struct BTree *right;
    struct BTree *left;
} BTree;

struct Map {
    BTree *tree;
};


void print_map(Map *map) {
    printf("%s", map->ptr);
}


Btree *insert(Map* map, const char *key, const char *value)
{
    BTree *current, *prev;
    int cmp_res = 0;
    prev = NULL;
    current = map->tree;
    while(current && cmp_res) {
        prev = current;
        cmp_res = strcmp(key, current->key);
        if (cmp_res == 0)
            return current;
        else {
            if (cmp_res < 0)
                current = prev->left;
            else {
                current = prev->right;
            }
        }
    }
    current = calloc(sizeof(Btree));
    current->key = strdup(key);
    current->value = strdup(value);
    if (!prev) {
        map->tree = current;
    }
    else {
        if (cmp_res < 0)
            prev->left = current;
        else {
            prev->right = current;
        }
    }
};

bool exists(Map *map, const char *key)
{
    const char *res = get(map, key);
    return res != NULL;
}

const char *get(Map* map, const char *key)
{
    BTree *current;
    int cmp_res;
    if ((current = map->tree) == NULL)
        return NULL;

    while (current)
    {
        cmp_res = strcmp(key, current->key);
        if (cmp_res == 0)
            return current->value;
        else
        {
            if (cmp_res < 0)
                current = current->left;
            else
                current = current->right;
        }
    }
    return NULL;
};
