#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static hash_item *ht_new_item(const char* k, const char *v)
{
    hash_item* new_item = malloc(sizeof(hash_item));
    new_item->key = strdup(k);
    new_item->value = strdup(v);
    return new_item;
}

static void ht_del_item(hash_item* i)
{
    free(i->key);
    free(i->value);
    free(i);
}

hash_table *ht_new()
{
    hash_table* ht = malloc(sizeof(hash_table));

    ht->size = 53;   // expand in resizing func
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(hash_item)); 
    return ht;
}


void ht_del_hash_table(hash_table* ht)
{
    for (int i = 0; i < ht->size; i++) {
        hash_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}

