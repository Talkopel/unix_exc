# include <stdlib.h>
# include <stdio.h>
# include <string.h>


# define max(x,y) (x > y) ? x : y
# define BALANCE 0
# define HRIGHT 1
# define HLEFT 2

# define COUNT 10

typedef struct Node {
	int val;
	int height;
	struct Node *left;
	struct Node *right;
} Node;


/* AVL functions declaration */
Node *AVL_fix(Node *root, int balance);
Node *AVL_check(Node *sub);
/* rotations */
Node *rotate_right(Node *root);
Node *rotate_left(Node *root);


static Node* root = NULL;


Node *new_node(int val) {
	
	Node *node;

	node = (Node *) malloc(sizeof(Node));
	memset(node, 0, sizeof(Node));
	node->val = val;

	return node;
}

int height(Node *sub) {
	
	if (sub == NULL) return -1;

	return max(1 + height(sub->left),1 + height(sub->right)) ;

}


Node *search(Node *root, int val) {

	if (root == NULL || val == root->val)
		return root;
	
	if (val < root->val)
		/* search left subtree */
		return search(root->left, val);
	
	/* search right subtree */
	return search(root->right, val);
}


Node *insert(Node *sub, int val) {
	
	Node *n, *tmp;

	if (sub == NULL) return new_node(val);
	
	if (val < sub->val) {
		if (sub->left != NULL) n = insert(sub->left, val);
		else {
			sub->left = new_node(val);
			return sub->left;
		}
	}

	else if (val > sub->val) {
		if (sub->right != NULL) n = insert(sub->right, val);
		else {
			sub->right = new_node(val);
			return sub->right;
		}
	
	}	
	else return search(root, val);
	
	if ((tmp = AVL_check(sub->right)) != NULL) {
		sub->right = tmp;
	}	
	if ((tmp = AVL_check(sub->left)) != NULL) {
		sub->left = tmp;
	}
	if (root == sub && (tmp = AVL_check(root)) != NULL) root = tmp;
	
	return n;
	
}

Node *AVL_fix(Node *sub, int balance) {
	
	
	switch(balance) {
	
		case HRIGHT: 
			printf("AVL_Fix: node %d is right heavy!\n", sub->val);
			if (sub->right == NULL || height(sub->right->left) - height(sub->right->right)  <= 0) 
				return rotate_left(sub);
			else {
				/* if right child is left heavy, rotate him right */		
				sub->right = rotate_right(sub->right);
				return rotate_left(sub);
			}
			
			break;
		case HLEFT:
			printf("AVL_Fix: node %d is left heavy!\n", sub->val);
			if (sub->left == NULL || height(sub->left->right) - height(sub->left->left) <= 0) 
				return rotate_right(sub);
			else {
				/* if left chiild is right heavy, rotate him left */
				sub->left = rotate_left(sub->left);
				return rotate_right(sub);
		
			}
			break;

	}
	return NULL;

}

Node *AVL_check(Node *sub) {		

	if (sub == NULL) return NULL;
	
	int hl, hr;
	hl = height(sub->left);
	hr = height(sub->right);	

	if (hl - hr >= 2) {
		/* this node is left heavy by 2 */
		return AVL_fix(sub, HLEFT);
	}
	else if (hr - hl >=2) {
		/* this node is right heavy by 2 */
		return AVL_fix(sub, HRIGHT);
	}
	else return NULL;

}

Node *rotate_right(Node *sub) {
	Node *a, *b;

	a = sub;
	b = a->left;
	a->left = b->right;
	b->right = a;
		

	/*
	a->hl = height(a->left);
	a->hr = height(a->right);

	b->hl = height(b->left);
	b->hr = height(b->right);*/
	
	return b;

}

Node *rotate_left(Node *sub) {
	
	Node *a, *b;

	a = sub;
	b = a->right;
	a->right = b->left;
	b->left = a;
	

	/*
	a->hl = height(a->left);
	a->hr = height(a->right);

	b->hl = height(b->left);
	b->hr = height(b->right);*/
	return b;

}

void inorder_traversal(Node *root) {
	
	if (root == NULL) return;
	
	inorder_traversal(root->left);
	printf("node: %d ---- height: %d\n", root->val, height(root));
	inorder_traversal(root->right);

}

void print2DUtil(Node *root, int space) {
	/* taken from geeksforgeeks */
	if (root == NULL) return; 
  
	space += COUNT; 
  
	print2DUtil(root->right, space); 
  
	printf("\n"); 
	for (int i = COUNT; i < space; i++) 
		printf(" "); 
	printf("v%d\n", root->val); 
   
	print2DUtil(root->left, space); 

}

int main(int argc, char *argv[]) {

	Node *n;	
	
	root = insert(root, 50);
	insert(root, 60); 
	insert(root, 55);
	insert(root, 65);
	insert(root, 70);
	insert(root, 30);
	insert(root, 31);
	insert(root, 33);
	insert(root, 32);
	print2DUtil(root, 0);
	printf("height: %d\n",height(root));
	/*inorder_traversal(root);*/

}
