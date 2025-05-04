/**

	libPratt -- Boilerplate starting point for a Pratt parser

	@file pratt_node.c

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


#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "scanner.h"
#include "pratt_node.h"
#include "text_buffer.h"


#ifdef TEST
	#include "CuTest.h"
#endif


/// Binding power
typedef enum {
	BP_NONE = 0,
	BP_TERM = 2,		// + -
	BP_FACTOR = 4,		// * /
	BP_UNARY = 6,		// ! -

	BP_MAX,
} BP;


/// Parsing rules
typedef struct {
	const char *		label;
	BP					lbp;
	BP					rbp;
} ParseRule;


static ParseRule rules[] = {
	[MINUS]		= { "minus",	BP_TERM,	BP_MAX },
	[PLUS]		= { "plus",		BP_TERM,	BP_TERM },
	[MULTIPLY]	= { "multiply",	BP_FACTOR,	BP_FACTOR },
	[DIVIDE]	= { "divide",	BP_FACTOR,	BP_FACTOR },
	[INTEGER]	= { "integer",	BP_NONE,	BP_NONE },
	[LPAREN]	= { "lparen",	BP_NONE,	BP_NONE },
	[RPAREN]	= { "rparen",	BP_NONE,	BP_NONE },
};


/// Forward declaration
static node * expr(Scanner * s, BP rbp);


/// Null denotation handler for current token type
/// (aka "head handler function")
/// Handles prefix operators
static node * nud(Scanner * s) {
	node * n = NULL;

	int rbp = rules[s->curType].rbp;

	switch (s->curType) {
		case INTEGER:
			n = int_node(atoi(s->start));
			break;

		case MINUS:
			s->curType = scan(s);		// Skip to next token
			n = unary_node(NODE_NEGATIVE, expr(s, rbp));
			return n;					// Return but don't skip to next token again

		case LPAREN:
			s->curType = scan(s);		// Skip to next token
			n = expr(s, rbp);

			if (s->curType != RPAREN) {
				fprintf(stderr, "**<%s>**\n** %*s\n** Expected ')', found %s\n", s->text, (int)(s->start - s->text + 1), "|", rules[s->curType].label);
				node_free(n);
				return NULL;
			}

			break;

		default:
			fprintf(stderr, "**<%s>**\n** %*s\n** Expected prefix token; found %s\n", s->text, (int)(s->start - s->text + 1), "|", rules[s->curType].label);
			return 0;
	}

	s->curType = scan(s);	// Skip to next token

	return n;
}


/// Left denotation handler for current token type
/// (aka "tail handler function")
/// Handles infix and postfix operators
static node * led(Scanner * s, node * left) {
	node * n = NULL;

	Scanner copy = *s;
	int rbp = rules[s->curType].rbp;

	s->curType = scan(s);	// Skip to next token

	switch (copy.curType) {
		case INTEGER:
			n = int_node(atoi(copy.start));
			break;

		case MINUS:
			n = binary_node(NODE_MINUS, left, expr(s, rbp));
			break;

		case PLUS:
			n = binary_node(NODE_PLUS, left, expr(s, rbp));
			break;

		case MULTIPLY:
			n = binary_node(NODE_MULTIPLY, left, expr(s, rbp));
			break;

		case DIVIDE:
			n = binary_node(NODE_DIVIDE, left, expr(s, rbp));
			break;

		default:
			fprintf(stderr, "**<%s>**\n** %*s\n** Expected infix/postfix token; found %s\n", s->text, (int)(s->start - s->text + 1), "|", rules[s->curType].label);
			return NULL;
	}

	return n;
}


/// Core Pratt parser algorithm entry
/// Parse tokens with binding power < specified threshold
static node * expr(Scanner * s, BP rbp) {
	node * left = nud(s);

	while (rbp < rules[s->curType].lbp) {
		left = led(s, left);
	}

	return left;
}


int pratt_string(const char * text) {
	node * n;

	// Create scanner
	Scanner s = scanner(text);

	// Identify first token type
	s.curType = scan(&s);

	do {
		// Recursively parse each expression and print result
		n = expr(&s, BP_NONE);
		ast_prefix(stdout, n);
		ast_prefix_indented(stdout, n);
		node_free(n);
	} while (s.curType);

	return 0;
}


int pratt_file(FILE * f) {
	text_buffer * buf = buffer_file(f, kDEFAULTCAPACITY);

	int r = pratt_string(buf->text);

	text_buffer_free(buf, 1);

	return r;
}


int pratt_filename(const char * fname) {
	int r = 0;

	FILE * f = fopen(fname, "r");

	if (f) {
		r = pratt_file(f);
		fclose(f);
	}

	return r;
}
