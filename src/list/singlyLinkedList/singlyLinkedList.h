/*
 * linkedList.h
 *
 *  Created on: 1 Jun 2015
 *      Author: am5514
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//Single linked list
typedef struct linkedList {
	node *rootNode;
	node *lastNode;
	uint32_t size;
} linkedList;

//Creation of new linked list
linkedList* createLinkedList();

//Insertion of a node into a linked list
void insertNode(linkedList* list, void *data, char *mnemonic);

//Deletion of a node in a linked list
void deleteNode(linkedList *list, int index);

//Retrieve an element from a linked list
void* getElement(linkedList* list, char *mnemonic);

//Is the list empty
uint32_t listIsEmpty(linkedList *list);

//List size
uint32_t listSize(linkedList *list);

//Free linked list
void freeLinkedList(linkedList *list);

#endif /* LINKEDLIST_H_ */
