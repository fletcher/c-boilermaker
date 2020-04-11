## About ##

|            |                           |  
| ---------- | ------------------------- |  
| Title:     | BoilermakerApp        |  
| Author:    | Fletcher T. Penney       |  
| Date:      | 2020-04-11 |  
| Copyright: | Copyright © 2020 Fletcher T. Penney.    |  
| Version:   | 1.0.0      |  


## Introduction ##

Several years ago I created [c-template] as a quick way to initialize new
projects with a standardized directory structure, a default CMake
configuration, and more. It turned out to be incredibly useful, and I learned
a lot about CMake in the process.

If I had it to do over again, there were a few things I would do differently.
I learned a bit more about integrating CMake with Xcode.  I learned, well a
lot of things, actually.

This is the successor to that project.

`c-boilermaker` is a boilerplate setup that does most of the things that
`c-template` does, but it does them better:

*	Standardized directory structure
*	Support for CuTest unit testing
*	Support for building Xcode projects


It fixes a few things that did not work well before:

*	Building frameworks for Xcode no longer require manually fixing the `Copy
	Files` in `Build Phases` every time the project is rebuilt.

*	There are separate branches for plain libraries/frameworks (`master`), macOS
	applications (`mac-app`), and macOS document-based applications
	(`mac-app-doc-based`). This allows easily creating new macOS applications
	using the same setup used for plain C projects, which is something that the
	old system was not good at.

*	The `CMakeLists.txt` file is better organized, with better differentiation
	between what should be customized for each project, and what should be left
	alone.

The tighter integration with Xcode and macOS applications was important to me.
The more experience I get with various aspects of programming, the more
convinced I am that focusing on plain text source files is the way to go.  Let
other tools handle the creationg of complex file formats based on those
simpler source files.  This includes working with `CMakeLists.txt` instead of
an Xcode `.xcodeproj` file.  Or building GUIs programmatically instead of with
interface builder (actually, it's even better with an additional layer of
abstraction that converts a simple text description of a GUI into the code to
build the GUI for you, but that's another story...)

This allows me to do a couple of things:

*	It is easy to ensure that the Xcode project is "right" when it is built from
	scratch whenever you want.  This requires a better understanding of what
	you're doing rather than randomly changing settings in Xcode and hoping for
	the best.

*	It allows me to easily build the same project via Xcode on macOS, or from
	the commandline via `make`. This allows two independent ways of compiling,
	which will sometimes identify different potential problems.  Throw in
	`xcodebuild` from the command-line, and you have another quasi-indepent way
	of building.

The main issue right now is that Xcode Storyboard files are tricky to get
right.  Xcode handles converting a plain text version of a Storyboard into a
compiled version for you.  But Cmake doesn't do that when building via `make`.
And compiling in advance causes CMake not to install the directory as a
resource.  I will continue to look into this, but honestly my preference is
not to use Storyboards in the first place, so I will probably focus on that
route instead.  I welcome suggestions on this aspect if anyone has any good
ideas.

There are a few things that have not been implemented yet:

*	Doxygen support for integrated documentation
*	Github gh-pages support for automatically placing documenation into github
*	*nix -> Windows cross-platform compiling
*	iOS CMake toolchain support

I intend to add these things as I come to need them so I can try to implement
them in as thoughtful a way as possible.  I've started using this for new
projects, and so far it is working great.  Over time, I will start migrating
some of my older projects as well, but may leave well enough alone for some of
them.


[c-template]: https://github.com/fletcher/c-template


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


### Storyboards ###

If you are using macOS storyboards, they need to be compiled first.
Xcode handles this automatically.  It would be possible to add this
behavior to CMake, but would add complexity for something that is
unlikely to be really necessary.

To compile you, can use a command like:

	ibtool --compile Main.storyboardc Main.storyboard


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
