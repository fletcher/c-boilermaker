/**

	libPratt -- Boilerplate starting point for a Pratt parser

	@file scanner.h

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


#ifndef SCANNER_H
#define SCANNER_H


typedef enum {
	END = 0,
	MINUS,
	PLUS,
	MULTIPLY,
	DIVIDE,
	INTEGER,
	LPAREN,
	RPAREN,
} token_type;


/// Re2c scanner data -- this structure is used by the re2c
/// scanner to track progress and offsets within the source
/// string.
struct Scanner {
	const char *	text;		//!< Start of text to be scanned
	const char *	start;		//!< Start of current token
	const char *	cur;		//!< Character currently being matched
	const char *	ptr;		//!< Used for backtracking by re2c
	const char *	ctx;
	token_type		curType;	//!< Type of current token
	int				depth;
};

typedef struct Scanner Scanner;


/// Build a scanner for a given string
Scanner scanner(const char * text);


/// Build a scanner for a given query, keeping a private copy of the string
/// Needed in Swift, for example
Scanner scanner_persistent_query(const char * text);


/// Free the private copy of the string
void scanner_free_query(Scanner s);


/// Scan text for tokens
int scan(Scanner * s);

#endif
