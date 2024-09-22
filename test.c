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
    ASSERT(my_ht->base_size == 7);
    ASSERT(my_ht->count == 0);
    ASSERT(my_ht->size == next_prime(my_ht->base_size));
}

TEST(test_insert_ht) {

    ASSERT(strcmp(ht_search(my_ht, "ngocdai"), "16062002") == 0);
    ASSERT(strcmp(ht_search(my_ht, "yenlinh"), "06032002") == 0);
    ASSERT(strcmp(ht_search(my_ht, "date"), "26102019") == 0);
    ASSERT(strcmp(ht_search(my_ht, "today"), "22092024") == 0);
    ASSERT(strcmp(ht_search(my_ht, "years"), "5years") == 0);

    ASSERT(ht_search(my_ht, "year") == NULL);
    ASSERT(my_ht->count == 5);
}

TEST(test_resize_up_ht) {
    ASSERT(my_ht->count == 6);
    ASSERT(my_ht->base_size == 40);
    printf("%d-%d", my_ht->count, my_ht->base_size);
}

int main() {
    my_ht = ht_new();

    RUN_TEST(test_prime);
    RUN_TEST(test_create_ht);
    
    ht_insert(my_ht, "ngocdai", "16062002");
    ht_insert(my_ht, "yenlinh", "06032002");
    ht_insert(my_ht, "date", "26102019");
    ht_insert(my_ht, "today", "22092024");
    ht_insert(my_ht, "years", "5years");
    RUN_TEST(test_insert_ht);

    ht_insert(my_ht, "alice", "01011990");
    ht_insert(my_ht, "bob", "25051995");
    ht_insert(my_ht, "carol", "12121985");
    ht_insert(my_ht, "dave", "03082000");
    ht_insert(my_ht, "eve", "14022001");
    ht_insert(my_ht, "frank", "05061998");
    ht_insert(my_ht, "grace", "08082003");
    ht_insert(my_ht, "hank", "22042004");
    ht_insert(my_ht, "iris", "17071997");
    ht_insert(my_ht, "jack", "30092000");
    ht_insert(my_ht, "kate", "15032002");
    ht_insert(my_ht, "leo", "11011989");
    ht_insert(my_ht, "mona", "22052001");
    ht_insert(my_ht, "nate", "04082005");
    ht_insert(my_ht, "olivia", "19062003");

    RUN_TEST(test_resize_up_ht);

    return failed;
}
    
