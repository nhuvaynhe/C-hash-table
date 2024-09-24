#include "test.h"
#include "prime.h"
#include "hash_table.h"

hash_table *my_ht;

TEST(test_prime) {
    ASSERT(is_prime(1) == -1);
    ASSERT(is_prime(3) == 1);
    ASSERT(is_prime(4) == 0);
    ASSERT(next_prime(160) == 163);
}

TEST(test_create_ht) {
    ASSERT(my_ht->base_size == 30);
    ASSERT(my_ht->count == 0);
    ASSERT(my_ht->size == 31);
}

TEST(test_insert_ht) {
    ASSERT(strcmp(ht_search(my_ht, "ngocdai"), "16062002") == 0);
    ASSERT(strcmp(ht_search(my_ht, "yenlinh"), "06032002") == 0);
    ASSERT(strcmp(ht_search(my_ht, "date"), "hello") == 0);
    ASSERT(strcmp(ht_search(my_ht, "today"), "22092024") == 0);

    ASSERT(ht_search(my_ht, "year") == NULL);
}

TEST(test_resize_up_ht) {
    ASSERT(my_ht->count == 15);
    ASSERT(my_ht->base_size == 60);
}

int main() {
    my_ht = ht_new();

    RUN_TEST(test_prime);
    RUN_TEST(test_create_ht);

    /* 1 to 5 */
    ht_insert(my_ht, "ngocdai", "16062002");
    ht_insert(my_ht, "yenlinh", "06032002");
    ht_insert(my_ht, "date", "hello");
    ht_insert(my_ht, "today", "22092024");
    ht_insert(my_ht, "alice", "01011990");
    ASSERT(my_ht->count == 5);
    RUN_TEST(test_insert_ht);
    
    /* 6 to 10 */
    ht_insert(my_ht, "test1", "25051995");
    ht_insert(my_ht, "test2", "03082000");
    ht_insert(my_ht, "test3", "14022001");
    ht_insert(my_ht, "test4", "05061998");
    ht_insert(my_ht, "test5", "08082003");

    /* 11 to 15 */
    ht_insert(my_ht, "test6", "22042004");
    ht_insert(my_ht, "test7", "17071997");
    ht_insert(my_ht, "test8", "30092000");
    ht_insert(my_ht, "test9", "15032002");
    ht_insert(my_ht, "test10", "11011989");


    RUN_TEST(test_resize_up_ht);
    RUN_TEST(test_insert_ht);

    return failed;
}
    
