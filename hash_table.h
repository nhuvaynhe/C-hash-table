#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

typedef struct hash_item {
    char *key;
    char *value;
} hash_item;

typedef struct hash_table {
    int size;
    int count;
    hash_item** items;
} hash_table;

/******************** PRIVATE ********************/

static hash_item *ht_new_item(const char* k, const char *v);
static void ht_del_item(hash_item *i); 

/************* END OF PRIVATE SECTION ************/

/********************* PUBLIC ********************/

hash_table *ht_new();
void ht_del_hash_table(hash_table *ht);

/************* END OF PUBLIC SECTION ************/

#endif
