#include <stdio.h>



// linked lists are cool because: you can add or remove elements in the middle of the list // you don't need to define a size for it
// linked lists are uncool because to access an element of the array, you have to iterate through it // you have to allocate them dynamically // it takes more memory than a regular array
// [pointer to first element] -> [value | pointer to next] -> [value | pointer to next] -> ... -> [value | pointer to NULL (end)]
typedef struct _linkedListNode { // we use this 'inner' name because the declaration is not complete because it's recursive
	unsigned int value;
	struct _linkedListNode* next; // we have to precise that it's a "struct"
} linkedListNode;



void printLinkedList (linkedListNode* head) {
	printf("\n");
	linkedListNode* current = head;
	unsigned int counter = 0;
	while (current != NULL) {
		printf("%d: %d (%p)\n", counter, current->value, current);
		current = current->next;
		counter++;
	}
}

void addToEnd (linkedListNode* head, int value) {
	linkedListNode* current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = (linkedListNode*) malloc(sizeof(linkedListNode));
	current->next->value = value;
	current->next->next = NULL; // very important
}

void pushToLinkedList(linkedListNode** head, int value) {
	linkedListNode* newNode = (linkedListNode*) malloc(sizeof(linkedListNode));
	newNode->next = *head;
	newNode->value = value;
	*head = newNode;
}

int popFromLinkedList(linkedListNode** head) {
	int value = (*head)->value;
	linkedListNode* nodeToRemove = *head;
	*head = (*head)->next;
	free(nodeToRemove);
	return value;
}

int removeLast (linkedListNode* head) {
	linkedListNode* current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}
	linkedListNode* nodeToRemove = current->next;
	int value = nodeToRemove->value;
	free(nodeToRemove);
	current->next = NULL;
	return value;
}

int removeByIndex(linkedListNode* head, int index) {
	linkedListNode* current = head;
	int counter = 0;
	while (counter != index - 1) {
		current = current->next;
		counter++;
	}
	linkedListNode* nodeToRemove = current->next;
	current->next = nodeToRemove->next;
	int value = nodeToRemove->value;
	free(nodeToRemove);
	return value;
}