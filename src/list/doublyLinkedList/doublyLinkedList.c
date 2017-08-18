/*
 * adtHelpers.c
 *
 *  Created on: 31 May 2015
 *      Author: Jk
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "../../error/error.h"
#include "doublyLinkedList.h"

/* Allocates memory for an individual entry in the list */
individualEntry *memAllocEntry(void) {
  individualEntry *entryPtr = malloc(sizeof(individualEntry));
  checkAlloc(entryPtr, "Failed to allocate memory for entryPtr ",
      MEMORY_ALLOCATE_FAILURE);
  return entryPtr;
}

/* Creates new empty doubly linked list */
listEntries * createNewList() {
	listEntries *newList = malloc(sizeof(listEntries));
  newList->head = memAllocEntry();
  newList->tail = memAllocEntry();
  newList->head->prev = NULL;
  newList->tail->next = NULL;
  newList->head->next = newList->tail;
  newList->tail->prev = newList->head;
  return newList;
}

/* Returns an iterator at the beginning of the list */
listIterator listStart(listEntries *list) {
  return list->head->next;
}

/* Returns an iterator at the end of the list */
listIterator listEnd(listEntries *list) {
  return list->tail;
}

/* Inserts an element to the given list */
void insertToList(listEntries *list, listIterator iter, char *newLabel,
    uint32_t newLabelAddress) {
  individualEntry *newEntry = memAllocEntry();
  newEntry->label = removeLastChar(newLabel);
  newEntry->labelAddress = newLabelAddress;
  newEntry->prev = iter->prev;
  newEntry->next = iter;
  iter->prev->next = newEntry;
  iter->prev = newEntry;
}

/* Iterator goes to the next element by pointing to the next pointer */
listIterator listIteratorNext(listIterator iter) {
  return iter->next;
}

/* Checks if current element is not the head or the tail of the list */
int listIteratorCurrent(listIterator iter) {
  int result = -1;
  if (iter->prev != NULL && iter->next != NULL) {
    result = 1;
  }
  return result;
}

/* Returns the contents of the iterator that points the label */
char *listIteratorLabel(listIterator iter) {
  assert(listIteratorCurrent(iter));
  return iter->label;
}

/* Returns the contents of the iterator that points to the label's address */
uint32_t listIteratorAddress(listIterator iter) {
  assert(listIteratorCurrent(iter));
  return iter->labelAddress;
}

/* Inserts an element at the head of the list */
void insertInHead(listEntries *list, char *label, uint32_t labelAddress) {
  insertToList(list, listStart(list), label, labelAddress);
}

/* Inserts an element at the tail of the list */
void insertInTail(listEntries *list, char *label, uint32_t labelAddress) {
  insertToList(list, listEnd(list), label, labelAddress);
}

/* Frees individual entry for which there's memory allocated before */
void freeIndividualEntry(individualEntry *entry) {
  free(entry);
}

/* Frees the doubly linked list for which memory was allocated before */
void freeList(listEntries *list) {
  individualEntry *entry = list->head;
  while (entry != NULL) {
    individualEntry *next = entry->next;
    freeIndividualEntry(entry);
    entry = next;
  }
  free(list);
}

/* Returns the address of a specific label in the selected list */
uint32_t findLabelAddress(char *label, listEntries *list) {
	 uint32_t result = 0;
		individualEntry *current = list->head->next;
	    while(current != NULL && current != listEnd(list))	{
	    	if (strcmp(current->label, label) == 0)	{
	    		result = current->labelAddress;
	    	}
	    	current = current->next;
	    }
	    return result;
}
