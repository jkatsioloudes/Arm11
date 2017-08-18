/*
 * doublyLinkedList.h
 *
 *  Created on: 31 May 2015
 *      Author: Jk
 *  Doubly linked list ADT with information on the instruction
 *   passed and links to the next and previous lists.

 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "../../tokenizer/tokenizer.h"

/* Holds details for an individual instruction */
typedef struct individualEntry {

	char *label;                  /* Is a string like "mov" */
	uint32_t labelAddress;        /* The address of the label */
	struct individualEntry *prev;
	struct individualEntry *next;

} individualEntry;

/* Used by a helper function for freeing the memory allocated */
typedef individualEntry *listIterator;

/* Represents the list in the form (VALUE - NEXT - PREV) */
typedef struct {
	individualEntry *head;
	individualEntry *tail;
} listEntries;

/* Allocates memory for an individual entry in the list */
individualEntry *memAllocEntry (void);

/* Creates new empty doubly linked list */
listEntries *createNewList ();

/* Returns an iterator at the beginning of the list */
listIterator listStart (listEntries *list);

/* Returns an iterator at the end of the list */
listIterator listEnd (listEntries *list);

/* Inserts an element to the given list */
void insertToList (listEntries *list, listIterator iter, char *newLabel, uint32_t newLabelAddress);

/* Iterator goes to the next element by pointing to the next pointer */
listIterator listIteratorNext (listIterator iter);

/* Checks if current element is not the head or the tail of the list */
int listIteratorCurrent (listIterator iter);

/* Returns the contents of the iterator that points the label */
char *listIteratorLabel (listIterator iter);

/* Returns the contents of the iterator that points to the label's address */
uint32_t listIteratorAddress (listIterator iter);

/* Inserts an element at the head of the list */
void insertInHead (listEntries *list, char *label, uint32_t labelAddress);

/* Inserts an element at the tail of the list */
void insertInTail (listEntries *list, char *label, uint32_t labelAddress);

/* Frees individual entry for which there's memory allocated before */
void freeIndividualEntry (individualEntry *entry);

/* Frees the doubly linked list for which memory was allocated before */
void freeList (listEntries *list);

/* Returns the address of a specific label in the selected list */
uint32_t findLabelAddress(char *labelToBeFound, listEntries *listToSearch);

#endif
