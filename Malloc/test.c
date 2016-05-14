#include <stdlib.h>
#include <time.h>
#include "my_malloc.h"
#include "tests.h"
// #include "grader.h"
// #include "malloc_common.h"

FILE* file;

size_t total_freelist_block_size() {
    size_t total = 0;
    for (metadata_t *t = freelist; t; t = t->next)
        total += t->block_size;
    return total;
}
size_t total_freelist_count() {
    size_t total = 0;
    for (metadata_t *t = freelist; t; t = t->next)
        total++;
    return total;
}

// void deduct_points(int points, const char *tag, const char *message) {
//     fprintf(file, "SUB: (-%d) %s: %s\n", points, tag, message);
//     fflush(file);
// }

// void add_points(int points, const char *tag, const char *message) {
//     fprintf(file, "ADD: ( %d ) %s: %s\n", points, tag, message);
//     fflush(file);
// }

void printList() {
    metadata_t *temp;
    printf("------LIST-----\n");
    for (temp = freelist; temp != NULL; temp = temp->next) {
        printf("(%d,%d)->", temp->block_size, temp->request_size);
    }
    printf("NULL\n");
    printf("------END------\n");
}
/*int freelist_ordered_general(int is_size) {*/
    /*for (metadata_t *t = freelist; t; t = t->next)*/
        /*if (t->next && (is_size ? t->size > t->next->size : t > t->next))*/
            /*return 0;*/
    /*return 1;*/
/*}*/
/*int freelist_ordered_size() { return freelist_ordered_general(1); }*/
/*int freelist_ordered_addr() { return freelist_ordered_general(0); }*/
#define metadata_plus_canary_size (sizeof(metadata_t) + 2*sizeof(int))
#define to_metadata(i) ( (metadata_t*)(((char*)i)-(sizeof(metadata_t) + sizeof(int))) )

/* Thoroughly checks their my_malloc function */
void check_malloc_3() {
    //char* tag = "check_malloc_3 - stress test";
    printf("hi");
    char* last_data = NULL;
    for (size_t i = 0; i < 1000; i++) {
        size_t size = (i*i)%1000 + 1;
        char* data = my_malloc(size);
        for (size_t j = 0; j < size; j++)
            data[j] = i*j;
        if (last_data) {
            size_t old_size = ((i-1)*(i-1))%1000 + 1;
            for (size_t j = 0; j < old_size; j++)
                if (last_data[j] != (char)((i-1)*j)) {
                    printf("failed\n");
                    //deduct_points(MALLOC_STRESS, tag, "Did not pass stress test");
                    return;
                }
            my_free(last_data);
        }
        last_data = data;
    }
    my_free(last_data);
    printf("success\n");
    //add_points(MALLOC_STRESS, tag, "Did pass stress test");
}
int main() {

	check_malloc_3();

}
