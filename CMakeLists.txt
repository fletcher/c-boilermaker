#
#	Boilerplate CMake configuration for a macOS application.
#
#	Designed by Fletcher T. Penney
#	See the LICENSE file for copyright and licensing information.
#

cmake_minimum_required(VERSION 2.6)


# ===================
# Customize This Part
# ===================

# Project Description

set (My_Project_Title "BoilermakerApp")
set (My_Project_Description "Standardized configuration to simplify your life")
set (My_Project_Author "Fletcher T. Penney")
set (My_Project_Revised_Date "2020-04-11")
set (My_Project_Version_Major 1)
set (My_Project_Version_Minor 0)
set (My_Project_Version_Patch 0)

set (My_Project_Copyright_Date "2020")

set (My_Project_Identifier "net.fletcherpenney.boilermaker")

string(TIMESTAMP My_Build_Version "%Y.%m.%d.%H.%M")


# Source files and headers

set(src_files
	src/main.m

	src/AppDelegate.m
	src/Document.m
	src/ViewController.m

	src/DemoPrefsViewController.m
	src/MASPreferencesWindowController.m
)

set(public_headers
)

set(private_headers
	src/AppDelegate.h
	src/Document.h
	src/ViewController.h

	src/DemoPrefsViewController.h
	src/MASPreferencesViewController.h
	src/MASPreferencesWindowController.h
)

set(resources
	resources/Main.storyboard

	resources/MASPreferencesWindow.xib
)

set(main_storyboard
	Main
)

# Include other CMake projects?
# add_subdirectory(submodules/foo)

# Libraries for linking
# on macOS can link to frameworks using: "-framework QuartzCore", for example
set(libraries_to_link
)

# This is an ugly hack, but it seems to work.
# When linking to a framework in Xcode, we need to be able to
# search for public headers within that framework
# "$SRCROOT/build-xcode/submodules/libFoo/$<CONFIG>/libFoo.framework/.."
# 
set(framework_search_paths
)

# Link to Cocoa Framework?
set (link_to_cocoa 1)

# Enable ARC for Obj-C?
# set (enable_arc 1)


# =======================
# Leave the rest alone...
# =======================

# Configuration

set (My_Project_Version "${My_Project_Version_Major}.${My_Project_Version_Minor}.${My_Project_Version_Patch}")
set (My_Project_Copyright "Copyright © ${My_Project_Copyright_Date} ${My_Project_Author}.")

string(TOUPPER ${My_Project_Title} My_Project_Title_Caps  )
string(REGEX REPLACE " " "_" My_Project_Title_Caps ${My_Project_Title_Caps} )

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project (${My_Project_Title} VERSION "${My_Project_Version}")


# Search source directory
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test)


# Search build directory (for version.h)
include_directories(${PROJECT_BINARY_DIR})


# Configure library/framework

add_executable("${My_Project_Title}"
	MACOSX_BUNDLE src/main.m
	${src_files}
	${private_headers}
	${public_headers}
	${resources}
)

string (REPLACE ";" " " framework_search_paths_string "${framework_search_paths}")

set_target_properties("${My_Project_Title}"
	PROPERTIES
	MACOSX_BUNDLE TRUE
	XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${My_Project_Identifier}"
	XCODE_ATTRIBUTE_MARKETING_VERSION ${My_Project_Version}
	MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME} Version ${My_Project_Version}, ${My_Project_Copyright} All rights reserved."
	MACOSX_BUNDLE_COPYRIGHT "${My_Project_Copyright}  All rights reserved."
	RESOURCE "${resources}"
	XCODE_ATTRIBUTE_FRAMEWORK_SEARCH_PATHS "${XCODE_ATTRIBUTE_FRAMEWORK_SEARCH_PATHS} ${framework_search_paths_string}"
	PUBLIC_HEADER "${public_headers}"
	XCODE_ATTRIBUTE_INSTALL_PATH "/Applications"
)

# Link to other libraries
target_link_libraries("${My_Project_Title}"
	${libraries_to_link}
)

# Link to Apple Cocoa Framework?
if (link_to_cocoa)
	target_link_libraries("${My_Project_Title}" "-framework Cocoa")
endif (link_to_cocoa)

# Enable ARC
if (enable_arc)
	set_property (TARGET "${My_Project_Title}"
		APPEND_STRING PROPERTY COMPILE_FLAGS "-fobjc-arc"
	)
endif (enable_arc)

# Use custom Info.plist template
# Original was here:
#	/usr/local/Cellar/cmake/3.15.5/share/cmake/Modules/MacOSXBundleInfo.plist.in
set_property(TARGET "${My_Project_Title}"
	PROPERTY MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/templates/Info.plist.in"
)


# ======================
# Process Template Files
# ======================

file(READ ${PROJECT_SOURCE_DIR}/LICENSE My_Project_License)

string(REGEX REPLACE "\n" "\n\t" My_Project_License_Indented ${My_Project_License})

string(REGEX REPLACE "\"" "\\\\\"" My_Project_License_Escaped ${My_Project_License_Indented})

string(REGEX REPLACE "\n" "\\\\n\"\\\\\n\"" My_Project_License_Literal ${My_Project_License_Escaped})


configure_file (
	"${PROJECT_SOURCE_DIR}/templates/template.c.in"
	"${PROJECT_BINARY_DIR}/template.c"
)

configure_file (
	"${PROJECT_SOURCE_DIR}/templates/template.h.in"
	"${PROJECT_BINARY_DIR}/template.h"
)

# Update the project README, to pull in new version #, etc.
configure_file (
	"${PROJECT_SOURCE_DIR}/templates/README.md.in"
	"${CMAKE_CURRENT_LIST_DIR}/README.md"
)

configure_file (
	"${PROJECT_SOURCE_DIR}/templates/version.h.in"
	"${PROJECT_BINARY_DIR}/version.h"
)


# ===========================================
# Build Test Suite with CuTest (unit testing)
# ===========================================

# from http://stackoverflow.com/questions/25199677/how-to-detect-if-current-scope-has-a-parent-in-cmake
get_directory_property(hasParent PARENT_DIRECTORY)


set(test_files
	test/CuTest.c
	test/CuTest.h
	${PROJECT_BINARY_DIR}/AllTests.c
)


# Process source files to look for tests to run
add_custom_command (
	OUTPUT ${PROJECT_BINARY_DIR}/AllTests.c
	COMMAND bash ${PROJECT_SOURCE_DIR}/test/make-tests.sh ${PROJECT_SOURCE_DIR}/src/*.c > ${PROJECT_BINARY_DIR}/AllTests.c
)


if(hasParent)
	# Don't create "run_tests" when we're a sub-project for something else
else()
	# Only create framework if we are the parent project
	set_target_properties("${My_Project_Title}"
		PROPERTIES
		FRAMEWORK TRUE
	)

	if (DEFINED TEST)
		add_definitions(-DTEST)

		add_executable(run_tests
			${src_files}
			${private_headers}
			${public_headers}
			${test_files}
		)

		# Link to other libraries
		target_link_libraries(run_tests
			${libraries_to_link}
		)

		# Link to Apple Cocoa Framework?
		if (link_to_cocoa)
			target_link_libraries(run_tests "-framework Cocoa")
		endif (link_to_cocoa)

		# Enable ARC
		if (enable_arc)
			set_property (TARGET run_tests
				APPEND_STRING PROPERTY COMPILE_FLAGS "-fobjc-arc"
			)
		endif (enable_arc)

		enable_testing()

		add_test( test ${PROJECT_BINARY_DIR}/run_tests)

		# valgrind memory testing
	#	find_program (MEMORYCHECK_COMMAND valgrind)
	#	SET (MEMORYCHECK_COMMAND_OPTIONS --leak-check=full --error-exitcode=1)
	#
	#	add_test( memory_test ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} ${PROJECT_BINARY_DIR}/run_tests)

	endif()
endif()


# ==========================
# Build Installer with CPack
# ==========================

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "${My_Project_Description}")
set (CPACK_PACKAGE_VERSION "${My_Project_Version_Major}.${My_Project_Version_Minor}.${My_Project_Version_Patch}")
set (CPACK_PACKAGE_VERSION_MAJOR "${My_Project_Version_Major}")
set (CPACK_PACKAGE_VERSION_MINOR "${My_Project_Version_Minor}")
set (CPACK_PACKAGE_VERSION_PATCH "My_Project_Version_Patch")

configure_file (
	"${PROJECT_SOURCE_DIR}/LICENSE"
	"${PROJECT_BINARY_DIR}/LICENSE.txt"
)
configure_file (
	"${PROJECT_SOURCE_DIR}/README.md"
	"${PROJECT_BINARY_DIR}/README.txt"
)

set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_BINARY_DIR}/LICENSE.txt")
set (CPACK_RESOURCE_FILE_README "${PROJECT_BINARY_DIR}/README.txt")

if (DEFINED TEST)
	# Don't install the test suite
else()
	if (APPLE)
		# Apple Builds

		if (DEFINED ZIP)
			set (CPACK_GENERATOR ZIP)
		else (DEFINED ZIP)
			set (CPACK_GENERATOR productbuild)
		endif (DEFINED ZIP)
	else (APPLE)
		if (WIN32)
			# Windows Builds

			if (DEFINED ZIP)
				set (CPACK_GENERATOR ZIP)
			else (DEFINED ZIP)
				set (CPACK_GENERATOR NSIS)
			endif (DEFINED ZIP)
		elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
			# Linux
			set (CPACK_GENERATOR ZIP)
		endif (WIN32)
	endif (APPLE)

	# Install Target
	install (TARGETS ${My_Project_Title}
		DESTINATION bin
		COMPONENT Main
	)
	set (CPACK_COMPONENT_MAIN_DISPLAY_NAME "${My_Project_Title}")
	set (CPACK_COMPONENT_MAIN_DESCRIPTION "Install ${My_Project_Title}.")

	if (public_headers)
		# Install Headers
		install(FILES
			${public_headers}
			DESTINATION include/${My_Project_Title}
			COMPONENT Headers
		)
		set (CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Development")
		set (CPACK_COMPONENT_HEADERS_DESCRIPTION "Install the public headers for development use.")

		set (CPACK_COMPONENTS_ALL Main Headers)
	else (public_headers)
		set (CPACK_COMPONENTS_ALL Main)
	endif (public_headers)

	# Install Documentation
	install(FILES
		"${PROJECT_BINARY_DIR}/LICENSE.txt"
		"${PROJECT_BINARY_DIR}/README.txt"
		COMPONENT Docs
		DESTINATION .
	)
	set (CPACK_COMPONENT_DOCS_DISPLAY_NAME "Documentation")
	set (CPACK_COMPONENT_DOCS_DESCRIPTION "Install README and LICENSE.")

endif (DEFINED TEST)

include(CPack)
