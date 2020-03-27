## About ##

|            |                           |  
| ---------- | ------------------------- |  
| Title:     | libBoilermaker        |  
| Author:    | Fletcher T. Penney       |  
| Date:      | 2020-03-26 |  
| Copyright: | Copyright © 2020 Fletcher T. Penney.    |  
| Version:   | 0.1.0      |  


## How to build ##

### macOS ###

You can automatically build Xcode projects:

*	`make xcode` -- regular build
*	`make xcode-test` -- build `run_tests` to perform CuTest unit tests

The Xcode projects can then be opened in Xcode, or you can build from
the command line via `xcodebuild`.


### Other ###

*	`make` -- regular build
*	`make-test` -- build `run_tests` to perform CuTest unit tests

These steps configure a build directory, but you still have to perform
the actual compilation.  Once you perform either step above, `cd build`
or `cd build-test` and then `make` (and `./run_tests` or `ctest` or
`make test` for the unit testing variant).

## License ##

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
