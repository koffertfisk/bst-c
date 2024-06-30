#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

bst_node_t* create_node(void *data) {
    bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
    if (new_node == NULL)
        return NULL;

    new_node->data = data;
    new_node->left = new_node->right = NULL;
    
    return new_node;
}

bst_node_t* insert_node(bst_node_t *root, void *data, compare_function compare_func) {
    if (root == NULL)
        return create_node(data);

    if (compare_func(data, root->data) < 0)
        root->left = insert_node(root->left, data, compare_func);
    else
        root->right = insert_node(root->right, data, compare_func);

    return root;
}

void inorder_traversal(bst_node_t *root, print_function print_func) {
    if (root != NULL) {
        inorder_traversal(root->left, print_func);
        print_func(root->data);
        inorder_traversal(root->right, print_func);
    }
}

void preorder_traversal(bst_node_t *root, print_function print_func) {
    if (root != NULL) {
        print_func(root->data);
        preorder_traversal(root->left, print_func);
        preorder_traversal(root->right, print_func);
    }
}

void postorder_traversal(bst_node_t *root, print_function print_func) {
    if (root != NULL) {
        postorder_traversal(root->left, print_func);
        postorder_traversal(root->right, print_func);
        print_func(root->data);
    }
}

void* search_node(bst_node_t *root, void *data, compare_function compare_func) {
    if (root == NULL || compare_func(data, root->data) == 0)
        return root;

    if (compare_func(data, root->data) < 0) {
        return search_node(root->left, data, compare_func);
    }
    
    return search_node(root->right, data, compare_func);
}

bst_node_t* delete_node(bst_node_t *root, void* data, compare_function compare_func, free_function free_func) {
    if (root == NULL) {
        return root;
    }

    if (compare_func(data, root->data) < 0) {
        root->left = delete_node(root->left, data, compare_func, free_func);
    } else if (compare_func(data, root->data) > 0) {
        root->right = delete_node(root->right, data, compare_func, free_func);
    } else {
        if (root->left == NULL) {
            bst_node_t *right_child = root->right;
            free_func(root->data);
            free(root);
            
            return right_child;
        } else if (root->right == NULL) {
            bst_node_t *left_child = root->left;
            free_func(root->data);
            free(root);
            
            return left_child;
        }

        bst_node_t *parent = root;
        bst_node_t *successor = root->right;
        while (successor->left != NULL) {
            parent = successor;
            successor = successor->left;
        }

        void *temp_data = root->data;
        root->data = successor->data;
        successor->data = temp_data;

        if (parent != root) {
            parent->left = delete_node(parent->left, successor->data, compare_func, free_func);
        } else {
            parent->right = delete_node(parent->right, successor->data, compare_func, free_func);
        }
    }

    return root;
}

int get_number_of_nodes(bst_node_t *root) {
    if (root == NULL)
        return 0;
    return 1 + get_number_of_nodes(root->left) + get_number_of_nodes(root->right);
}

static void collect_data_inorder(bst_node_t *root, void **array, int *index) {
    if (root != NULL) {
        collect_data_inorder(root->left, array, index);
        array[(*index)++] = root->data;
        collect_data_inorder(root->right, array, index);
    }
}

void** get_all_data_inorder(bst_node_t *root, int *size) {
    *size = get_number_of_nodes(root);
    void **array = malloc(*size * sizeof(void *));
    if (array == NULL) {
        *size = 0;
        return NULL;
    }
    
    int index = 0;
    collect_data_inorder(root, array, &index);
    
    return array;
}

void free_tree(bst_node_t *root, free_function free_func) {
    if (root != NULL) {
        free_tree(root->left, free_func);
        free_tree(root->right, free_func);
        free_func(root->data);
        free(root);
    }
}