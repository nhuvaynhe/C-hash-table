#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#define HT_PRIME_1      163
#define HT_PRIME_2      111

#if (DEBUG)
#define HT_INITIAL_BASE_SIZE 20
#else
#define HT_INITIAL_BASE_SIZE 50
#endif

typedef struct hash_item {
    char *key;
    char *value;
} hash_item;

typedef struct hash_table {
    int size;
    int count;
    int base_size;
    hash_item** items;
} hash_table;

/******************** PRIVATE ********************/
static int hashing_func(const char *s, const int num, const int buckets);
static hash_item* ht_new_item(const char* k, const char *v);
static void ht_del_item(hash_item *i); 
static int ht_get_hash(const char *s, const int buckets, const int attempt);
static hash_table *ht_new_sized(const int base_size);
static void ht_resize(hash_table *ht, const int base_size);
/************* END OF PRIVATE SECTION ************/

/********************* PUBLIC ********************/
hash_table* ht_new();
void ht_del_hash_table(hash_table *ht);
void ht_insert(hash_table *ht, const char *key, const char *value);
char* ht_search(hash_table *ht, const char *key);
void ht_delete(hash_table *ht, const char *key);
/************* END OF PUBLIC SECTION ************/

#endif
