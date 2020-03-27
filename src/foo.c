/**

	libBoilerplate -- Standardized configuration to simplify your life

	@file foo.c

	@brief


	@author	Fletcher T. Penney
	@bug

**/

/*

	Copyright © 2020 Fletcher T. Penney.


	Test

*/

#include <stdlib.h>

#include "foo.h"
#include "bar.h"

int foo(int x) {
	return x * 2;
}


#ifdef TEST
void Test_foo(CuTest * tc) {
	int test = foo(15);

	CuAssertIntEquals(tc, 30, test);
}
#endif


int foo_bar(int x) {
	return foo(bar(x));
}


#ifdef TEST
void Test_foo_bar(CuTest * tc) {
	int test = foo_bar(10);

	CuAssertIntEquals(tc, 40, test);
}
#endif