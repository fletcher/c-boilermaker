/**

	libPratt -- Boilerplate starting point for a Pratt parser

	@file scanner.c

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


#include <stdlib.h>
#include <string.h>

#include "scanner.h"


/// Build a scanner for a given string
Scanner scanner(const char * text) {
	Scanner s;

	s.text = text;
	s.start = text;
	s.cur = s.start;
	s.depth = 0;

	return s;
}


/// strdup() not available on all platforms
static char * my_strdup(const char * source) {
	if (source == NULL) {
		return NULL;
	}

	char * result = malloc(strlen(source) + 1);

	if (result) {
		strcpy(result, source);
	}

	return result;
}


/// Build a scanner for a given string, keeping a private copy
/// Needed in Swift, for example
Scanner scanner_persistent(const char * text) {
	Scanner s;

	s.text = my_strdup(text);
	s.start = s.text;
	s.cur = s.start;
	s.depth = 0;

	return s;
}


/// Free the private copy of the string
void scanner_free(Scanner s) {
	free((void *)s.text);
}


// Basic scanner struct

#define YYCTYPE		unsigned char
#define YYCURSOR	s->cur
#define YYMARKER	s->ptr
#define YYCTXMARKER	s->ctx

/// Scan text for tokens
int scan(Scanner * s) {

	scan:

	s->start = s->cur;

	/*!re2c
		re2c:yyfill:enable = 0;

		'+'									{ return PLUS; }
		'-'									{ return MINUS; }
		'*'									{ return MULTIPLY; }
		'/'									{ return DIVIDE; }

		'('									{ return LPAREN; }
		')'									{ return RPAREN; }

		[0-9]+								{ return INTEGER; }

		// Comment through end of line
		'//' [^\n\r\x00]*					{ goto scan; }		// Comments are ignored by scanner

		'\x00'								{ return END; }

		*									{ goto scan; }
	*/
}
