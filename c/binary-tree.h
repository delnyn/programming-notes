#include <stdio.h>
#include <stdlib.h>

typedef struct _binaryTreeNode {
	int value;
	struct _binaryTreeNode * left;
	struct _binaryTreeNode * right;
} binaryTreeNode;

void printTreeDFSInOrder (binaryTreeNode * tree) {
	if (tree->left != NULL) {
		printTreeDFSInOrder(tree->left);
	}
	printf("%d ", tree->value);
	if (tree->right != NULL) {
		printTreeDFSInOrder(tree->right);
	}
}

void appendNode (binaryTreeNode * tree, int value) {
	binaryTreeNode * current = tree;
	while (1) {
		if (current->value == 0) {
			current->value = value;
			break;
		} else if (value < current->value) {
			if (current->left == NULL)
			{
				current->left = (binaryTreeNode *) malloc(sizeof(binaryTreeNode));
				current->left->value = value;
				current->left->left = NULL;
				current->left->right = NULL;
				break;
			} else {
				current = current -> left;
				continue;
			}
		} else if (value > current->value) {
			if (current->right == NULL)
			{
				current->right = (binaryTreeNode *) malloc(sizeof(binaryTreeNode));
				current->right->value = value;
				current->right->left = NULL;
				current->right->right = NULL;
				break;
			} else {
				current = current -> right;
				continue;
			}
		} else {
			break;
		}
	}
}