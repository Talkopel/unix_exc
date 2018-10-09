# include <stdlib.h>
# include <stdio.h>
# include <string.h>


# define max(x,y) (x >= y) ? x : y
# define BALANCE 0
# define HRIGHT 1
# define HLEFT 2

typedef struct Node {
	int val;
	int balance;
	int height;
	struct Node *left;
	struct Node *right;
} Node;


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

	if (root == NULL) return new_node(val);
	
	if (val < root->val) {
		if (root->left != NULL)
			return insert(root->left, val);
		else {
			root->left = new_node(val);
			return root->left;
		}
	}

	else if (val > root->val) {
		if (root->right != NULL)
			return insert(root->right, val);
		else {
			root->right = new_node(val);
			return root->right;
		}
	}
	
}

void inorder_traversal(Node *root) {
	
	if (root == NULL) return;
	
	inorder_traversal(root->left);
	printf("%d\n", root->val);
	inorder_traversal(root->right);

}

int main(int argc, char *argv[]) {

	Node *n;	
	
	root = insert(root, 50);
	insert(root, 20);
	insert(root, 60);
	insert(root, 25);
	insert(root, 600);
	insert(root, 500);
	inorder_traversal(root);
	printf("height: %d\n",height(root));

}
