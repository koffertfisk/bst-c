#ifndef BST_H
#define BST_H

/**
 * @file bst.h
 * @brief Binary Search Tree (BST) for holding generic elements.
 * 
 * This header file defines the interface for a BST that can store
 * generic elements. It provides functions for creating, manipulating, and
 * destroying BSTs, as well as inorder, preorder and postorder traversal.
 * 
 * @date 2024-06-24
 * @version 1.0
 * 
 * @author Marcus Enderskog
 */

/// @brief BST node structure type definition for holding generic data items.
typedef struct bst_node bst_node_t;

/// @brief BST node structure type definition for holding generic data items.
struct bst_node {
    void *data;             // Data contained within the node.
    struct bst_node *left;  // Pointer to this node's left child.
    struct bst_node *right; // Pointer to this node's right child.
};

/** 
 * @brief Function pointer for comparison of two items.
 * 
 * @param first The first item to compare.
 * @param second The second item to compare.
 * 
 * @return An integer representation of the comparison result; typically 0 for equality, 
 * a negative integer for the first item being smaller than the second, and vice versa.
 */
typedef int (*compare_function)(void *, void *);

/** 
 * @brief Function pointer for deallocating data memory.
 * 
 * @param data The data to be deallocated.
 **/
typedef void (*free_function)(void *);

/** 
 * @brief Function pointer for printing data.
 * 
 * @param data The data to be printed.
 */
typedef void (*print_function)(void *);

/**
 * @brief Creates a new BST node.
 * 
 * @param data The data to store in the new node.
 * @return A pointer to the newly created BST node.
 */
bst_node_t* create_node(void *data);

/**
 * @brief Inserts a new node into the BST.
 * 
 * @param root The root of the BST.
 * @param data The data to insert into the BST.
 * @param compare_func The function used to compare two data items.
 * @return The root of the BST after insertion.
 */
bst_node_t* insert_node(bst_node_t *root, void *data, compare_function compare_func);

/**
 * @brief Searches for a node in the BST.
 * 
 * @param root The root of the BST.
 * @param data The data to search for in the BST.
 * @param compare_func The function used to compare two data items.
 * @return A pointer to the found node, or NULL if the node was not found.
 */
void* search_node(bst_node_t *root, void *data, compare_function compare_func);

/**
 * @brief Deletes a node from the BST.
 * 
 * @param root The root of the BST.
 * @param data The data of the node to delete.
 * @param compare_func The function used to compare two data items.
 * @param free_func The function used to deallocate the data memory.
 * @return The root of the BST after deletion.
 */
bst_node_t* delete_node(bst_node_t *root, void* data, compare_function compare_func, free_function free_func);

/**
 * @brief Frees all nodes in the BST.
 * 
 * @param root The root of the BST.
 * @param free_func The function used to deallocate the data memory.
 */
void free_tree(bst_node_t *root, free_function free_func);

/**
 * @brief Performs an inorder traversal of the BST.
 * 
 * @param root The root of the BST.
 * @param print_func The function used to print the data of each node.
 */
void inorder_traversal(bst_node_t *root, print_function print_func);

/**
 * @brief Performs a preorder traversal of the BST.
 * 
 * @param root The root of the BST.
 * @param print_func The function used to print the data of each node.
 */
void preorder_traversal(bst_node_t *root, print_function print_func);

/**
 * @brief Performs a postorder traversal of the BST.
 * 
 * @param root The root of the BST.
 * @param print_func The function used to print the data of each node.
 */
void postorder_traversal(bst_node_t *root, print_function print_func);

#endif
