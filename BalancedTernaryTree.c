#include <stdio.h>
#include <stdlib.h>
// structure for a ternary tree node
typedef struct TernaryNode {
	int key;
	int height;
	struct TernaryNode* left;
	struct TernaryNode* middle;
	struct TernaryNode* right;
} TernaryNode;
// Function to create a new node
TernaryNode* createNode(int key) {
	TernaryNode* newNode = (TernaryNode*)malloc(sizeof(TernaryNode));
	newNode->key = key;
	newNode->height = 1;
	newNode->left = NULL;
	newNode->middle = NULL;
	newNode->right = NULL;
	return newNode;
}
// Function to calculate the height of a node
int height(TernaryNode* node) {
	return node == NULL ? 0 : node->height;
}
// Function to update the height of a node
void updateHeight(TernaryNode* node) {
	if (node != NULL) {
		int leftHeight = height(node->left);
		int rightHeight = height(node->right);
		node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
	}
}
// Rotate right to balance the tree
TernaryNode* rotateRight(TernaryNode* y) {
	TernaryNode* x = y->left;
	y->left = x->right;
	x->right = y;
	updateHeight(y);
	updateHeight(x);
	return x;
}
// Rotate left to balance the tree
TernaryNode* rotateLeft(TernaryNode* x) {
	TernaryNode* y = x->right;
	x->right = y->left;
	y->left = x;
	updateHeight(x);
	updateHeight(y);
	return y;
}
// Balance a node
TernaryNode* balanceNode(TernaryNode* node) {
	if (node == NULL) return NULL;
	int balanceFactor = height(node->left) - height(node->right);
	// Left-heavy case
	if (balanceFactor > 1) {
		if (height(node->left->left) < height(node->left->right)) {
			node->left = rotateLeft(node->left);
		}
		return rotateRight(node);
	}
	// Right-heavy case
	if (balanceFactor < -1) {
		if (height(node->right->right) < height(node->right->left)) {
			node->right = rotateRight(node->right);
		}
		return rotateLeft(node);
	}
	updateHeight(node);
	return node;
}
// Insert a key into the ternary tree
TernaryNode* insert(TernaryNode* root, int key) {
	if (root == NULL) {
		return createNode(key);
	}
	if (key < root->key) {
		root->left = insert(root->left, key);
	}
	else if (key == root->key) {
		root->middle = insert(root->middle, key);
	}
	else {
		root->right = insert(root->right, key);
	}
	// Balance the tree
	return balanceNode(root);
}
// Search for a key in the ternary tree
TernaryNode* search(TernaryNode* root, int key) {
	if (root == NULL || root->key == key) {
		return root;
	}
	if (key < root->key) {
		return search(root->left, key);
	}
	else if (key == root->key) {
		return search(root->middle, key);
	}
	else {
		return search(root->right, key);
	}
}
// In-order traversal
void inOrderTraversal(TernaryNode* root) {
	if (root == NULL) return;
	inOrderTraversal(root->left);
	printf("%d ", root->key);
	inOrderTraversal(root->middle);
	inOrderTraversal(root->right);
}
// Free memory
void freeTree(TernaryNode* root) {
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->middle);
	freeTree(root->right);
	free(root);
}
// Main function
int main() {
	TernaryNode* root = NULL;
	// Insert elements
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 5);
	root = insert(root, 10); // Duplicate keys go to the middle
	root = insert(root, 15);
	root = insert(root, 25);
	printf("In-order traversal of the balanced ternary tree:\n");
	inOrderTraversal(root);
	printf("\n");
	// Search for a key
	int searchKey;
	printf("Enter for the key to search:");
	scanf("%d",&searchKey);
	TernaryNode* result = search(root, searchKey);
	if (result != NULL) {
		printf("Key %d found in the tree.\n", searchKey);
	}
	else {
		printf("Key %d not found in the tree.\n", searchKey);
	}
	// Free memory
	freeTree(root);
	return 0;
}
