#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include "bst.h"

typedef struct item {
    int id;
    char *label;
} item_t;

void free_item(void *data) {
    item_t *item = (item_t*) data;
    free(item->label);
    free(item);
}

item_t* create_item(int id, const char* label) {
    item_t *item = (item_t *)malloc(sizeof(item_t));
    item->id = id;
    item->label = strdup(label);
    
    return item;
}

void print_item(void *data) {
    item_t *item = (item_t *)data;
    printf("ID: %d, Label: %s\n", item->id, item->label);
}

int compare_item(void *first, void *second) {
    item_t *first_item = (item_t*) first;
    item_t *second_item = (item_t*) second;
    
    return (first_item->id - second_item->id);
}

void test_insert_and_search_single_item() {
    bst_node_t *root = NULL;
    
    item_t *itemFirst = create_item(0, "first");
    item_t *itemSecond = create_item(1, "second");
    item_t *itemThird = create_item(2, "third");

    root = insert_node(root, itemFirst, compare_item);
    root = insert_node(root, itemSecond, compare_item);
    root = insert_node(root, itemThird, compare_item);
    
    CU_ASSERT_PTR_NOT_NULL(root);
    
    inorder_traversal(root, print_item);

    item_t item_to_search = {.id = 1};

    item_t *found_item = (item_t*)search_node(root, &item_to_search, compare_item);
    CU_ASSERT_PTR_NOT_NULL(found_item);

    free_tree(root, free_item);
}

void test_insert_duplicate_ids() {
    bst_node_t *root = NULL;
    
    item_t *itemFirst = create_item(0, "first");
    item_t *itemFirstAgain = create_item(0, "first");

    root = insert_node(root, itemFirst, compare_item);
    root = insert_node(root, itemFirstAgain, compare_item);
    
    inorder_traversal(root, print_item);

    free_tree(root, free_item);
}

void test_search_empty_tree() {
    bst_node_t *root = NULL;
    item_t search_key = {.id = 0};
    item_t *found_item = (item_t*)search_node(root, &search_key, compare_item);
    
    CU_ASSERT_PTR_NULL(found_item);
}

void test_search_nonexisting_item() {
    bst_node_t *root = NULL;

    item_t *itemFirst = create_item(0, "first");
    root = insert_node(root, itemFirst, compare_item);
    
    item_t search_key = {.id = 1};
    item_t *found_item = (item_t*)search_node(root, &search_key, compare_item);

    CU_ASSERT_PTR_NULL(found_item);

    free_tree(root, free_item);
}

void test_delete_items() {
    bst_node_t *root = NULL;
    
    item_t *itemFirst = create_item(0, "first");
    item_t *itemSecond = create_item(1, "second");
    item_t *itemThird = create_item(2, "third");

    root = insert_node(root, itemFirst, compare_item);
    root = insert_node(root, itemSecond, compare_item);
    root = insert_node(root, itemThird, compare_item);

    root = delete_node(root, itemSecond, compare_item, free_item);

    item_t second_item_to_search = {.id = 0};
    item_t third_item_to_search = {.id = 2};
    
    item_t *second_found_item = (item_t*)search_node(root, &second_item_to_search, compare_item);
    CU_ASSERT_PTR_NOT_NULL(second_found_item);
    
    item_t *third_found_item = (item_t*)search_node(root, &third_item_to_search, compare_item);
    CU_ASSERT_PTR_NOT_NULL(third_found_item);

    free_tree(root, free_item);
}

int main()
{
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    CU_pSuite insertion = CU_add_suite("Insertion", NULL, NULL);
    CU_pSuite search = CU_add_suite("Search", NULL, NULL);
    CU_pSuite deletion = CU_add_suite("Deletion", NULL, NULL);
    CU_pSuite edge_cases = CU_add_suite("Edge Cases", NULL, NULL);
    
    CU_add_test(insertion, "Insert single item", test_insert_and_search_single_item);
    CU_add_test(insertion, "Insert duplicate IDs", test_insert_duplicate_ids);
    
    CU_add_test(search, "Search empty tree", test_search_empty_tree);
    CU_add_test(search, "Search nonexisting item", test_search_nonexisting_item);

    CU_add_test(deletion, "Delete item", test_delete_items);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_error();
}