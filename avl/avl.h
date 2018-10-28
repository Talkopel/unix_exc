# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define max(x,y) (x > y) ? x : y

/* Balance constants */
typedef enum avl_test_function_e {
	AVL_are_equal = 0,
	AVL_left_argument_higher,
	AVL_right_argument_higher
} avl_test_function_t;

typedef enum avl_api_result_e {
	AVL_failed = -1,
	AVL_success
} avl_api_ret_t;

/* height is always calculate height(left) - height(right) */ 
typedef enum avl_balance_factor_e {
	AVL_heavy_left = 2,
	AVL_heavy_right = -2,
	AVL_balanced = 0
} avl_balance_factor_t; 

/* struct of a node in the tree */
typedef struct node_s {
	void *value;
	struct node_s *left;
	struct node_s *right;

} node_t; 

/**
 * callback function - implement a function with this prototype to test two values
 * return the relevant enum entry located in avl_test_function_t (^)
 * @param value1 is a void pointer to a tested value
 * @param value2 is a void pointer to the other tested value
 */
typedef avl_test_function_t (*avl_node_value_test)(void *value1, void *value2);

/**
 * callback function - implement a function with this prototype to handle calls from traversal
 * @param node is a pointer to the node given in small to large order
 */
typedef void (*avl_traversal_callback)(node_t *node);

typedef struct avl_tree_s {
	unsigned int value_size; /* size of varriable pointed to by value in the node_t structure */
	avl_node_value_test test_function; /* pointer to evaluation function of two values */
	avl_traversal_callback callback; /* pointer to traversal callback function */
	node_t *root; /* internal use  do not touch: root of the avl tree */
} avl_tree_t;	


/**
 * AVL tree initialization function, call to set up root node
 * @param settings is a pointer to avl_tree_t structure with the desired settings
 * @param root_value is a pointer to the value desired in the root node
 */
avl_api_ret_t AVL_init(avl_tree_t *avl_tree, void *root_value);

/** 
 * AVL tree deletion function, call to securly free all the nodes
 * @param settings is a pointer to avl_tree_t used initialize the tree
 */
avl_api_ret_t AVL_free(avl_tree_t *avl_tree);

/**
 * AVL tree searh function, returns pointer to the found node or NULL if not found
 * @param avl_tree is a pointer to the tree to perform the operation on
 * @param value is a pointer to the value to find 
 * NOTE: this function uses the "avl_node_value_test" function
 */
node_t *AVL_search(avl_tree_t *avl_tree, void *value);

/**
 * AVL tree insert function - retains AVL property
 * @param avl_tree is a pointer to the tree to perform the operation on
 * @param value is a pointer to the value to add to the tree
 */
avl_api_ret_t AVL_insert(avl_tree_t *avl_tree, void *value);

/**
 * AVL tree traversal by order. This function will call the callback supplied
 * to the init function (avl_tree_t.callback)
 * @param avl_tree is a pointer the to tree upon which to perform the traversal
 */
void AVL_traverse(avl_tree_t *avl_tree);

/* INTERNAL FUNCTIONS */

/**
 * internal use function - fixes imabalance, returns pointer to new head
 * @param subtree is a pointer to the imbalanced node_s structure
*/
node_t *_AVL_fix(node_t *subtree);

/**
 * internal use function - returns pointer to new head
 * @param subtree is a pointer to a node_t that needs to be rotated
 */
node_t *_rotate_right(node_t *subtree);

/**
 * internal use function -returns pointer to new head 
 * @param subtree is a pointer to a node_t that needs to be rotated
 */
node_t *_rotate_left(node_t *subtree);

/**
 * intenal use function - creates a new node with a given value
 * @param *avl_tree is a pointer to the given tree
 * @param *new_node_value points to a location of the value for this new node
 */
node_t *_create_new_node(avl_tree_t *avl_tree, void *new_node_value);


/** 
 * internal use function - returns height of a given node using a recursive algorithm 
 * @param node* is a pointer to the node to gather the height of
 */ 
int _get_recursive_node_height(node_t *node);

/**
 * internal use function - returns height of a given node iterativley
 * @param node if a pointer to the node to gather the height of
 */
int _get_iterative_node_height(node_t *node);

/**
 * internal use function - allocates value_size buffer, and copies data to it and return pointer
ize size of the value field of the node
 * @param value points to the location to copy the value from
 */ 
void *_allocate_value_with_data(unsigned int value_size, void *value);


/**
 * internal use function - frees value and node
 * @param node is the node to free (NEEDS TO HAVE NO CHILDREN)
 */
int _free_childless_node(node_t *node);

/**
 * internal use function - searches for node recursivley 
 * @param avltree is the avl tree on which the operation is done
 * @param subtree current subtree in recursive algorithm
 * @param value is a pointer to location of the value to check against
 */
node_t *_search_from_node(avl_tree_t *avl_tree, node_t *node, void *value);

/**
 * internal use function - inserts node at correct position and retains AVL 
 * @param node current node we are looking through
 * @param value pointer to the value we'd like to add
 * @param avl_tree, pointer to the tree we work on
 */
avl_api_ret_t _insert_from_node(avl_tree_t *avl_tree ,node_t *node, void *value);


/**
 * internal use function - recursivly traverses the tree 
 * @param avl_tree pointer to the tree
 * @param node is the current node
 */
void _traverse_tree(avl_tree_t *avl_tree, node_t *node);

