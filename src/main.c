/**

	libPratt -- Boilerplate starting point for a Pratt parser

	@file main.c

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
#include <string.h>
#include <unistd.h>

#include "libPratt.h"


#define F(i,n) for(int i= 0;i<n;i++)


int main(int argc, char * const argv[]) {
	char action = '\0';
	int option;
	int err = 0;

	// Set offset to 1 if we want an "action" immediately following the program when called
	// e.g.  ./foo bar -x -y -z
	int offset = 0;

	if (argc > 1) {
		if (argv[1][0] != '-' || argv[1][1] == '-') {
			// Skip action or long argument (e.g. `--help`)
			offset = 1;
		}
	}


	// Read short options
	while ((option = getopt(argc - offset, &argv[offset], ":hxy:")) != -1) {
		switch (option) {
			case 'h':
				// help -- display usage
				fprintf(stdout, "%s: option recognized -- %c\n", argv[0], option);
				err = -1;
				break;

			case 'x':
				// option without argument
				fprintf(stdout, "%s: option recognized -- %c\n", argv[0], option);
				break;

			case 'y':
				// option with required argument
				fprintf(stdout, "%s: option recognized -- %c (%s)\n", argv[0], option, optarg);
				break;

			case ':':
				// required argument is missing
				fprintf(stdout, "%s: option needs value -- %c\n", argv[0], optopt);
				err = 1;
				break;

			case '?':
				// option is not recognized
				fprintf(stderr, "%s: option not recognized -- %c\n", argv[0], optopt);
				err = 1;
				break;
		}
	}


	// Is an action required?
	if (!err && !offset) {
		fprintf(stderr, "%s: action missing\n", argv[0]);
		err = 1;
	}

	if (err == 0 && offset) {
		if (argc < offset + 1) {
			// Required action missing
			err = 1;
		} else if (strcmp(argv[1], "--help") == 0) {
			// help -- display usage
			err = -1;
		} else if (strcmp(argv[1], "calc") == 0) {
			action = 'c';
		} else {
			fprintf(stderr, "%s: action not recognized -- %s\n", argv[0], argv[1]);
			err = 1;
		}
	}


	// Read arguments
	// for (optind += offset; optind < argc; optind++) {
	// 	fprintf(stderr, "%s: argument -- %s\n", argv[0], argv[optind]);
	// }


	if (err) {
		// Error
		fprintf(stderr, "usage: %s {action1|action2} [-xh] [-y arg]\n", argv[0]);
	} else {
		// Proceed
		switch (action) {
			case 'c':
				if (optind + offset < argc) {
					for (optind += offset; optind < argc; optind++) {
						pratt_filename(argv[optind]);
					}
				} else {
					pratt_file(stdin);
				}

				break;
		}
	}

	// Clean up

	return err;
}
