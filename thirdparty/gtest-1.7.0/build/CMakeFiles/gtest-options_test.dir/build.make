# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ivansoban/dev/gtest-1.7.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ivansoban/dev/gtest-1.7.0/build

# Include any dependencies generated for this target.
include CMakeFiles/gtest-options_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gtest-options_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gtest-options_test.dir/flags.make

CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o: CMakeFiles/gtest-options_test.dir/flags.make
CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o: ../test/gtest-options_test.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/ivansoban/dev/gtest-1.7.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o -c /Users/ivansoban/dev/gtest-1.7.0/test/gtest-options_test.cc

CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/ivansoban/dev/gtest-1.7.0/test/gtest-options_test.cc > CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.i

CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/ivansoban/dev/gtest-1.7.0/test/gtest-options_test.cc -o CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.s

CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o.requires:
.PHONY : CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o.requires

CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o.provides: CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o.requires
	$(MAKE) -f CMakeFiles/gtest-options_test.dir/build.make CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o.provides.build
.PHONY : CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o.provides

CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o.provides.build: CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o

# Object files for target gtest-options_test
gtest__options_test_OBJECTS = \
"CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o"

# External object files for target gtest-options_test
gtest__options_test_EXTERNAL_OBJECTS =

gtest-options_test: CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o
gtest-options_test: CMakeFiles/gtest-options_test.dir/build.make
gtest-options_test: libgtest_main.a
gtest-options_test: libgtest.a
gtest-options_test: CMakeFiles/gtest-options_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable gtest-options_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest-options_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gtest-options_test.dir/build: gtest-options_test
.PHONY : CMakeFiles/gtest-options_test.dir/build

CMakeFiles/gtest-options_test.dir/requires: CMakeFiles/gtest-options_test.dir/test/gtest-options_test.cc.o.requires
.PHONY : CMakeFiles/gtest-options_test.dir/requires

CMakeFiles/gtest-options_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gtest-options_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gtest-options_test.dir/clean

CMakeFiles/gtest-options_test.dir/depend:
	cd /Users/ivansoban/dev/gtest-1.7.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ivansoban/dev/gtest-1.7.0 /Users/ivansoban/dev/gtest-1.7.0 /Users/ivansoban/dev/gtest-1.7.0/build /Users/ivansoban/dev/gtest-1.7.0/build /Users/ivansoban/dev/gtest-1.7.0/build/CMakeFiles/gtest-options_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gtest-options_test.dir/depend

