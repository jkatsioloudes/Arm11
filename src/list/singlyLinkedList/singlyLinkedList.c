/*
 * linkedList.c
 *
 *  Created on: 1 Jun 2015
 *      Author: am5514
 */

#include "singlyLinkedList.h"

#define EMPTY 0

//Creation of a new linked list
linkedList* createLinkedList() {
	linkedList *list = malloc(sizeof(linkedList));
	list->rootNode = NULL;
	list->lastNode = NULL;
	//list->rootNode->next = list->lastNode->next = NULL;
	//list->rootNode->data = list->lastNode->data = NULL;
	list->size = EMPTY;
	return list;
}

//Insertion of a node O(1)
void insertNode(linkedList* list, void *data, char *mnemonic) {

	//Create a new node
	node* newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->mnemonic = mnemonic;

	//If the list is empty
	if (listIsEmpty(list)) {
		//Point root and last node to this new node
		list->rootNode = list->lastNode = newNode;
	} else {
		list->lastNode->next = newNode;
		list->lastNode = newNode;
	}
	list->size++;
}

//Deletion of a node O(n)
void deleteNode(linkedList* list, int index) {

	//Assert: list is a valid initialised linkedlist and 0 <= index < list size
	//Optimise -> http://stackoverflow.com/questions/12914917/using-pointers-to-remove-item-from-singly-linked-list?rq=1

	//First find previous pointer to deleted node
	node* currentNode = list->rootNode;
	node* previousNode = currentNode;
	//3 Cases
	if (index == 0) {
		//1. Deleting the root node
		node* nextNode = list->rootNode->next;
		free(list->rootNode);
		list->rootNode = nextNode;
	} else if (index == listSize(list) - 1) {
		//2. Deleting the last node
		while (index--) { //Or currentNode != list->lastNode
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		previousNode->next = NULL;
		free(list->lastNode);
		list->lastNode = previousNode;
	} else {
		//3. Deleting a node that is not the first or last
		while (index--) { //Or currentNode != list->lastNode
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		previousNode->next = currentNode->next;
		free(currentNode);
	}
	//Decrement list size
	list->size--;
}

//Get an element from a linked list
void* getElement(linkedList* list, char *mnemonic) {

	if (strcmp(list->rootNode->mnemonic, mnemonic) == 0) {
		return list->rootNode->data;
	} else {
		node *currentNode = list->rootNode;
		for (int i = 0; i < listSize(list); i++) {
			currentNode = currentNode->next;
			if (strcmp(currentNode->mnemonic, mnemonic) == 0) {
				return currentNode->data;
			}
		}
		return NULL;
	}
}

//Size of the list
uint32_t listSize(linkedList *list) {
	return list->size;
}

//List is empty
uint32_t listIsEmpty(linkedList *list) {
	return (list->rootNode == NULL) | (listSize(list) == EMPTY);
}

/* Frees the doubly linked list for which memory was allocated before */
void freeLinkedList(linkedList *list) {
	node *currentNode = list->rootNode;
  while (currentNode != list->lastNode) {
    node *next = currentNode->next;
    free(currentNode->data);
    free(currentNode);
    currentNode = next;
  }
  free(list->lastNode->data);
  free(list->lastNode);
  free(list);
}

