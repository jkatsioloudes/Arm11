/*
 * node.h
 *
 *  Created on: 1 Jun 2015
 *      Author: am5514
 */

#ifndef NODE_H
#define NODE_H

//Node data structure
typedef struct node {
	char *mnemonic;
  void *data;
  struct node *next;
} node;


#endif /* NODE_H_ */
