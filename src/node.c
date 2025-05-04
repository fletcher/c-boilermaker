/**

	libPratt -- Boilerplate starting point for a Pratt parser

	@file node.c

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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"


#ifdef TEST
	#include "CuTest.h"
#endif


/// strndup not available on all platforms
static char * my_strndup(const char * source, size_t n) {
	if (source == NULL) {
		return NULL;
	}

	size_t len = 0;
	char * result;
	const char * test = source;

	// strlen is too slow if strlen(source) >> n
	for (len = 0; len < n; ++len) {
		if (*test == '\0') {
			break;
		}

		test++;
	}

	result = malloc(len + 1);

	if (result) {
		memcpy(result, source, len);
		result[len] = '\0';
	}

	return result;
}


node * node_new(node_type t) {
	node * n = calloc(1, sizeof(node));

	if (n) {
		n->type = t;
	}

	return n;
}


void node_free(node * n) {
	if (n) {
		node_free(n->first);
		node_free(n->second);

		switch (n->type) {
			case NODE_TEXT:
				free ((void *)n->payload.text);
				break;

			default:
				break;
		}

		free(n);
	}
}


node * unary_node(node_type t, node * first) {
	node * n = NULL;

	if (first) {
		n = node_new(t);

		if (n) {
			n->first = first;
		}
	}

	return n;
}


node * binary_node(node_type t, node * first, node * second) {
	node * n = NULL;

	if (first || second) {
		n = node_new(t);

		if (n) {
			n->first = first;
			n->second = second;
		}
	}

	return n;
}


node * int_node(int i) {
	node * n = node_new(NODE_INTEGER);

	if (n) {
		n->payload.integer = i;
	}

	return n;
}


node * text_node(const char * text, int len) {
	node * n = node_new(NODE_TEXT);

	if (n) {
		n->payload.text = my_strndup(text, len);
	}

	return n;
}


typedef struct {
	const char *	label;
	int				isBinary;
} debug;


static debug nodes[] = {
	[NODE_MINUS]	= { "minus",	true },
	[NODE_PLUS]		= { "plus",		true },
	[NODE_MULTIPLY]	= { "multiply",	true },
	[NODE_DIVIDE]	= { "divide",	true },
	[NODE_NEGATIVE]	= { "negative",	false },
	[NODE_INTEGER]	= { "integer",	true },
	[NODE_TEXT]		= { "text",		true },
};


static void node_prefix(FILE * stream, node * n) {
	if (n) {
		switch (n->type) {
			case NODE_INTEGER:
				fprintf(stream, "%d", n->payload.integer);
				break;

			case NODE_TEXT:
				fprintf(stream, "%s", n->payload.text);
				break;

			default:
				fprintf(stream, "(%s ", nodes[n->type].label);
				node_prefix(stream, n->first);

				if (nodes[n->type].isBinary) {
					fprintf(stream, " ");
					node_prefix(stream, n->second);
				} else if (n->second) {
					fprintf(stream, "*unexpected second*=>");
					node_prefix(stream, n->second);
				}

				fprintf(stream, ")");
				break;
		}
	}
}


void ast_prefix(FILE * stream, node * n) {
	if (n) {
		node_prefix(stream, n);
		fprintf(stream, "\n");
	} else {
		fprintf(stream, "null AST\n");
	}
}

