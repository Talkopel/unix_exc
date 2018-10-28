# include "avl.h"
# include <time.h>



avl_test_function_t value_check(void *value1, void *value2) {
	int *first_value = 0;
	int *second_value = 0;
	avl_test_function_t ret;	

	first_value = (int *)(value1);
	second_value = (int *)(value2);
	
	if (*first_value == *second_value) {
		ret = AVL_are_equal;
	} 
	else if (*first_value > *second_value) {
		ret = AVL_left_argument_higher;
	}
	else {
		ret = AVL_right_argument_higher;
	}

	return ret;
}

void traversal_callback(node_t *node) {
	int *value = (int *) node->value;
	printf("value: %d\n", *value);
}

int main(int argc, char *argv[]) {
	
	avl_tree_t avl = {};
	int current_insert = 0;
	int i;
	time_t t_time;
	node_t *node;

	srand((unsigned) time(&t_time));

	avl.value_size = sizeof(int);
	avl.test_function = value_check;
	avl.callback = traversal_callback;
	avl.root = NULL;
	
	if (AVL_init(&avl, &current_insert) < 0) {
		printf("PROBLEM!\n");
	}
	else {
		printf("SUCESS\n");
	}	
	
	current_insert = 1;
	AVL_insert(&avl, &current_insert);
	for (i = 0; i < 50; i++) {
		current_insert = rand() % 50;
		AVL_insert(&avl, &current_insert);
	}
	/* 
	for (i = 0; i< 50; i++) {

		current_insert = rand() % 50;
		if ((node = AVL_search(&avl, &current_insert)) != NULL) {
			printf("INSERTED AND FOUND %d\n", current_insert);
		}
	}*/
	AVL_traverse(&avl);
	return 0;	

}


