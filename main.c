#include <stdio.h>
#include "hash_table.h"

int main()
{
    hash_table *ht = ht_new();
    printf("Create hash table successfully.\n");

    ht_del_hash_table(ht);
    printf("Delete hash table successfully.\n");
}
