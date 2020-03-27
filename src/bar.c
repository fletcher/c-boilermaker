/**

	libBoilerplate -- Standardized configuration to simplify your life

	@file bar.c

	@brief


	@author	Fletcher T. Penney
	@bug

**/

/*

	Copyright © 2020 Fletcher T. Penney.


	Test

*/


#include <stdlib.h>

#include "bar.h"


int bar(int x) {
	return x + 10;
}


#ifdef TEST
void Test_bar(CuTest * tc) {
	int test = bar(10);

	CuAssertIntEquals(tc, 20, test);
}
#endif
