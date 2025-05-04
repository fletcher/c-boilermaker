/**

	libPratt -- Boilerplate starting point for a Pratt parser

	@file node.h

	@brief


	@author	Fletcher T. Penney
	@bug

**/

/*

	Copyright © 2025 Fletcher T. Penney.


	MIT License

	Copyright (c) 2020 Fletcher T. Penney

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/


#ifndef NODE_H
#define NODE_H


typedef enum {
	NODE_MINUS,
	NODE_PLUS,
	NODE_MULTIPLY,
	NODE_DIVIDE,
	NODE_NEGATIVE,
	NODE_INTEGER,
	NODE_TEXT,
} node_type;


struct node {
	node_type			type;

	union {
		int				integer;
		const char *	text;
	} payload;

	struct node *		first;
	struct node *		second;
};

typedef struct node node;


node * node_new(node_type t);
void node_free(node * n);

void ast_prefix(FILE * stream, node * n);

node * binary_node(node_type t, node * first, node * second);
node * unary_node(node_type t, node * first);

node * int_node(int i);
node * text_node(const char * t, int len);

#endif
