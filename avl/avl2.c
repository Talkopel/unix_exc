# include "avl.h"


/* API functions see documentation in avl.h */
avl_api_ret_t AVL_init(avl_tree_t *avl_tree, void *root_value) {
	
	node_t *root = NULL; 
	avl_api_ret_t ret = AVL_failed;
	root = _create_new_node(avl_tree, root_value);
	if (NULL != root) {
		avl_tree->root = root;
		ret = AVL_success;
	}
	return ret;

}

avl_api_ret_t AVL_free(avl_tree_t *avl_tree) {
	return 0;
}

node_t *AVL_search(avl_tree_t *avl_tree, void *value) {

	node_t *found_node = NULL;
	if (NULL != avl_tree->root) {
		found_node = _search_from_node(avl_tree, avl_tree->root, value);
	}
	return found_node;
}

avl_api_ret_t AVL_insert(avl_tree_t *avl_tree, void *value) {
	
	avl_api_ret_t ret = AVL_failed;
	if (NULL != avl_tree->root) {
		ret = _insert_from_node(avl_tree, avl_tree->root, value);
	}

	return ret;
}

void AVL_traverse(avl_tree_t *avl_tree) {
	_traverse_tree(avl_tree, avl_tree->root);
}


/* INTERNAL USE FUNCTIONS */
/* this function fixes the AVL property and returns the fixed parent 
 * to understand a little bit more about the algoritm read the rotations doc below*/
node_t *_AVL_fix(node_t *subtree) {
	
	node_t *new_parent = NULL;
	node_t *tested_child = NULL;
	int height_difference = 0;

	if (NULL == subtree) {
		/* avoid logic and complications below -> return now */
		return NULL;
	}	
	
	height_difference = _get_recursive_node_height(subtree->left) - 
			    _get_recursive_node_height(subtree->right);
	
	if (height_difference <= AVL_heavy_right) {
		/* this subtree is right heavy */
		tested_child = subtree->right;
		height_difference = _get_recursive_node_height(subtree->left) -
				    _get_recursive_node_height(subtree->right);
		
		/* becuase the algorithm is recursive we can assume:
		 * the highest imbalance of the children will at most be |1|
		*/ 
		if (height_difference > AVL_balanced){
			/* of balance by twords the left side, at most |1|, rotate right child right */
			subtree->right = _rotate_right(subtree->right);
		}
		new_parent = _rotate_left(subtree);
	}	
	else if (height_difference >= AVL_heavy_left) {
		/* this subtree is left heavy */
		tested_child = subtree->left;
		height_difference = _get_recursive_node_height(subtree->left) -
				    _get_recursive_node_height(subtree->right);
		if (height_difference < AVL_balanced) {
			/* left child is right heavy - rotate left (assumption above) */
			subtree->left = _rotate_left(subtree->left);
		}
		new_parent = _rotate_right(subtree);
	}

	return new_parent;
}

/* rotations 
 * to retain the trees AVL propery rotations have to be made
 * There are 4 types of rotations, but they can be broken down to two simple rotations
 * these are the cases: if a node is right heavy check its right child
 * if the right child is left heavy, rotate the child right and its parent left
 * otherwise, only rotate the parent left (apply symmetry to gain 2 more cases)
 * this means only two functions need to be implemented - rotate right and left. 
 **/
node_t *_rotate_right(node_t *subtree) {
	
	node_t *old_parent = NULL;
	node_t *new_parent = NULL;
	
	/* rotation swithes parent with the right child */
	old_parent = subtree;		
	new_parent = old_parent->left;
	old_parent = new_parent->right;
	new_parent->right = old_parent;

	return new_parent;
}

node_t *_rotate_left(node_t *subtree) {
	
	node_t *old_parent = NULL;
	node_t *new_parent = NULL;
	
	/* rotation switches parent with right child */ 
	old_parent = subtree;
	new_parent = old_parent->right;
	old_parent->right = new_parent->left;
	new_parent->left = old_parent;

	return new_parent;	
}

/* create new node and initialize value */
node_t *_create_new_node(avl_tree_t *avl_tree, void *new_node_value) {
	
	node_t *new_node = NULL;
	
	new_node = (node_t *) malloc(sizeof(node_t));
	if (NULL != new_node) {
		/* malloc success */
		new_node->value = _allocate_value_with_data(avl_tree->value_size,
							    new_node_value);
		new_node->left = NULL;
		new_node->right = NULL;
	}
	
	return new_node;
	
}

/* returns node height recursivly 
 * a tree with only one node has height zero, because it has no links*/
int _get_recursive_node_height(node_t *node) {

	int height = 0;
	
	if (NULL == node) {
		height = -1;	
	}
	else {
		height = max(1 + _get_recursive_node_height(node->left), 1 + _get_recursive_node_height(node->right));
	}

	return height;
}

/* allocate value for node */
void *_allocate_value_with_data(unsigned int value_size, void *value) {
	
	void *value_ptr = 0;
	
	value_ptr = malloc(value_size);
	if (NULL != value_ptr) {
		memcpy(value_ptr, value, value_size);
	}	

	return value_ptr;
}


/* frees childless node */
int _free_childless_node(node_t *node) {
	int success;
	if (node->right || node->left) {
		success = -1;
	}
	free(node->value);
	free(node);
	success = 0;
	return success;
}

/* searches recursivly */
node_t *_search_from_node(avl_tree_t *avl_tree, node_t *node, void *value) {
	
	node_t *found_node = NULL;
	avl_test_function_t test_result;	
		
	if (NULL != node) {
		/* get comparisson result */
		test_result = avl_tree->test_function(node->value, value);
		if (AVL_are_equal == test_result) {
			found_node = node;
		}
		else if (AVL_left_argument_higher == test_result) {
			found_node = _search_from_node(avl_tree, node->left, value);
		}
		else {
			found_node = _search_from_node(avl_tree, node->right, value);
		}
	}
	return found_node;
}

/* recursive insert */ 
avl_api_ret_t _insert_from_node(avl_tree_t *avl_tree, node_t *node, void *value) {
	
	node_t *new_parent = NULL; /* this varriable will be used to update parents if need be */
	avl_test_function_t test_result;
	avl_api_ret_t ret = AVL_failed;	
	node_t **call_offset = NULL;
	

	if (node != NULL) {
		/* check node's value against given value */
		test_result = avl_tree->test_function(node->value, value);
		if (AVL_are_equal == test_result) {
			/* to avoid more logic below a return is best placed here - the node was found in the tree */
			ret = AVL_success;
			return ret;
		}
		else if (AVL_left_argument_higher == test_result) {
			call_offset = &node->left;
		} 
		else {
			call_offset = &node->right;
		}
		
		if (NULL != *call_offset) {
			ret = _insert_from_node(avl_tree, *call_offset, value);
		}
		else {
			*call_offset = _create_new_node(avl_tree, value);
			if (NULL != *call_offset) {
				ret = AVL_success;
			}
		}
		
		/* fix right subtree */
		new_parent = _AVL_fix(node->right);
		if (new_parent != NULL) {
			node->right = new_parent;
		}
		/* fix left subtree */
		new_parent = _AVL_fix(node->left);
		if (new_parent != NULL) {
			node->left = new_parent; 
		}
	}
	
	
		
	return ret;
}



void _traverse_tree(avl_tree_t *avl_tree, node_t *node) {
	if (NULL == node) return;

	_traverse_tree(avl_tree, node->left);
	avl_tree->callback(node);
	_traverse_tree(avl_tree, node->right);
	
}
