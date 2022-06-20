#include <stdio.h>



// linked lists: can add and remove elements in the middle of the list; no need to define a size; must iterate through list to access an element; must be allocated dynamically; takes up more memory
// [value | pointer to next] -> [value | pointer to next] -> ... -> [value | pointer to NULL (end)]
// every struct is accessed by a pointer
typedef struct _linkedListNode { // must use this 'inner' name because of recursion
	unsigned int value;
	struct _linkedListNode * next; // must say that it's a "struct"
} linkedListNode;



void printLinkedList (linkedListNode * head) {
	linkedListNode * current = head;
	unsigned int counter = 0;
	while (current != NULL) {
		printf("%d: %d (%p)\n", counter, current->value, current);
		current = current->next;
		counter++;
	}
	printf("\n");
}

void addToEnd (linkedListNode * head, int value) {
	linkedListNode * current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = (linkedListNode *) malloc(sizeof(linkedListNode));
	current->next->value = value;
	current->next->next = NULL; // very important
}

void pushToLinkedList(linkedListNode ** head, int value) {
	linkedListNode * newNode = (linkedListNode *) malloc(sizeof(linkedListNode));
	newNode->next = *head;
	newNode->value = value;
	*head = newNode;
}

int popFromLinkedList(linkedListNode ** head) {
	int value = (*head)->value;
	linkedListNode * nodeToRemove = *head;
	*head = (*head)->next;
	free(nodeToRemove);
	return value;
}

int removeLast (linkedListNode * head) {
	linkedListNode * current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}
	linkedListNode * nodeToRemove = current->next;
	int value = nodeToRemove->value;
	free(nodeToRemove);
	current->next = NULL;
	return value;
}

int removeByIndex(linkedListNode * head, int index) {
	linkedListNode * current = head;
	int counter = 0;
	while (counter != index - 1) {
		current = current->next;
		counter++;
	}
	linkedListNode * nodeToRemove = current->next;
	current->next = nodeToRemove->next;
	int value = nodeToRemove->value;
	free(nodeToRemove);
	return value;
}