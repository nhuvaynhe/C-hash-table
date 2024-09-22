#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"
#include "prime.h"

static hash_item HT_DELETED_ITEM = {NULL, NULL};

/****************************** PRIVATE FUNC ******************************/
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

static int hashing_func(const char *s, const int num, const int buckets)
{
    long hash = 0;
    int len = strlen(s);
    int i;

    for (i = 0; i < len; i++) {
        hash += (long) pow(num, len-(i+1)) * s[i];
        hash = hash % buckets;
    }

    return hash;
}

static int ht_get_hash(const char *s, const int buckets, const int attempt)
{
    const int hash_a = hashing_func(s, HT_PRIME_1, buckets);
    const int hash_b = hashing_func(s, HT_PRIME_2, buckets);
    return (hash_a + (attempt * (hash_b + 1))) % buckets;
}

static hash_table *ht_new_size(const int base_size)
{
    hash_table* ht = malloc(sizeof(hash_table));
    if (!ht) {
        return NULL;
    }

    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);   // expand in resizing func

    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(hash_item)); 
    return ht;
}

static void ht_resize(hash_table *ht, const int base_size)
{
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }

    hash_table *new_ht = ht_new_size(base_size);
    for (int i = 0; i < ht->size; i++) {
        hash_item *item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }
    
    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    /* to delete the old hash table, assign its related data
     * to a new hash table, and the free the new one */
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    hash_item **tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}

static void ht_resize_up(hash_table *ht)
{
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

static void ht_resize_down(hash_table *ht)
{
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}

/****************************** PUBLIC FUNC ******************************/
hash_table *ht_new()
{
    return ht_new_size(HT_INITIAL_BASE_SIZE);
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

/**************************** HASH TABLE API ****************************/
void ht_insert(hash_table *ht, const char *key, const char *value)
{
    const int load = ht->count * 100 / ht->size;
    if (load > 70) { 
        ht_resize_up(ht);
    }

    hash_item *item = ht_new_item(key, value);
    int index = ht_get_hash(key, ht->size, 0);
    hash_item *cur_item = ht->items[index];
    int i = 1;

    // if key exists, overwrite the previous item.
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }
    }

    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        index = ht_get_hash(key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    }
    ht->items[index] = item;
    ht->count++;
}

char* ht_search(hash_table *ht, const char *key)
{
    int index = ht_get_hash(key, ht->size, 0);
    hash_item *item = ht->items[index];
    int i = 1;

    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }

    return NULL;
}

void ht_delete(hash_table *ht, const char *key)
{
    const int load = ht->count * 100 / ht->size;
    if (load < 10) { 
        ht_resize_down(ht);
    }

    int index = ht_get_hash(key, ht->size, 0);
    hash_item *item = ht->items[index];
    int i = 1;

    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}




