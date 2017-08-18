/*
 * assemble.h
 *
 *  Created on: 2 Jun 2015
 *      Author: am5514
 */

#ifndef ASSEMBLE_H
#define ASSEMBLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../bitManipulation/bitManipulation.h"
#include "../auxiliary/auxiliary.h"
#include "../tokenizer/tokenizer.h"
#include "../list/singlyLinkedList/singlyLinkedList.h"
#include "../initialise/initialise.h"
#include "../twoPass/twoPass.h"
#include "../assembleInstruction/opcode/opcode.h"
#include "../error/error.h"

/* Assembles a file and return true on success or false on failure */
bool assembleFile(char *src, char *dst);

#endif
