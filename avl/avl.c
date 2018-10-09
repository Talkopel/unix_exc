# include <stdlib.h>
# include <stdio.h>
# include <string.h>


# define max(x,y) (x >= y) ? x : y
# define BALANCE 0
# define HRIGHT 1
# define HLEFT 2

typedef struct Node {
	int hr, hl;
	int val;
	struct Node *left;
	struct Node *right;
} Node;


/* AVL functions declaration */
void AVL_fix(Node *root, int balance);
void AVL_check(Node *root);
/* rotations */
void rotate_right(Node *root);

static Node* root = NULL;


Node *new_node(int val) {
	
	Node *node;

	node = (Node *) malloc(sizeof(Node));
	memset(node, 0, sizeof(Node));
	node->val = val;

	return node;
}


int height(Node *root) {
	
	if (root == NULL || root->left == NULL && root->right == NULL)
		return 0;

	return  max(1 + height(root->left), 1 + height(root->right)) ;

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


Node *insert(Node *root, int val) {
	
	Node *n;

	if (root == NULL) return new_node(val);
	
	if (val < root->val) {
		if (root->left != NULL) {
			root->hl++;
			n = insert(root->left, val);
			AVL_check(root);
			return n;

		}
		else {
			root->left = new_node(val);
			return root->left;
		}
	}

	else if (val > root->val) {
		if (root->right != NULL) {
			root->hr++;
			n = insert(root->right, val);
			AVL_check(root);
			return n;
		}
		else {
			root->right = new_node(val);
			return root->right;
		}
	
	}
	
}

void AVL_fix(Node *root, int balance) {
	
	switch(balance) {
	
		case HRIGHT: 
			printf("AVL_Fix: node %d is right heavy!\n", root->val);
			break;
		case HLEFT:
			printf("AVL_Fix: node %d is left heavy!\n", root->val);
			break;

	}

}

void AVL_check(Node *root) {
	
	if (root->hl - root->hr >= 2) {
		/* this node is left heavy by 2 */
		AVL_fix(root, HLEFT);
	}
	else if (root->hr - root->hl >=2) {
		/* this node is right heavy by 2 */
		AVL_fix(root, HRIGHT);
	}

}

void rotate_right(Node *root) {

	return;

}

void inorder_traversal(Node *root) {
	
	if (root == NULL) return;
	
	inorder_traversal(root->left);
	printf("node: %d ---- hright: %d\n", root->val, root->hr - root->hl);
	inorder_traversal(root->right);

}

int main(int argc, char *argv[]) {

	Node *n;	
	
	root = insert(root, 50);
	insert(root, 20);
	insert(root, 40);
	insert(root, 10);
	insert(root, 15);
	inorder_traversal(root);
	printf("height: %d\n",height(root));

}
