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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alexander/exacel/exascel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexander/exacel/exascel

# Include any dependencies generated for this target.
include CMakeFiles/exascel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exascel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exascel.dir/flags.make

CMakeFiles/exascel.dir/exascel.cxx.o: CMakeFiles/exascel.dir/flags.make
CMakeFiles/exascel.dir/exascel.cxx.o: exascel.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexander/exacel/exascel/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/exascel.dir/exascel.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/exascel.dir/exascel.cxx.o -c /home/alexander/exacel/exascel/exascel.cxx

CMakeFiles/exascel.dir/exascel.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exascel.dir/exascel.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alexander/exacel/exascel/exascel.cxx > CMakeFiles/exascel.dir/exascel.cxx.i

CMakeFiles/exascel.dir/exascel.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exascel.dir/exascel.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alexander/exacel/exascel/exascel.cxx -o CMakeFiles/exascel.dir/exascel.cxx.s

CMakeFiles/exascel.dir/exascel.cxx.o.requires:
.PHONY : CMakeFiles/exascel.dir/exascel.cxx.o.requires

CMakeFiles/exascel.dir/exascel.cxx.o.provides: CMakeFiles/exascel.dir/exascel.cxx.o.requires
	$(MAKE) -f CMakeFiles/exascel.dir/build.make CMakeFiles/exascel.dir/exascel.cxx.o.provides.build
.PHONY : CMakeFiles/exascel.dir/exascel.cxx.o.provides

CMakeFiles/exascel.dir/exascel.cxx.o.provides.build: CMakeFiles/exascel.dir/exascel.cxx.o

CMakeFiles/exascel.dir/reader.cxx.o: CMakeFiles/exascel.dir/flags.make
CMakeFiles/exascel.dir/reader.cxx.o: reader.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alexander/exacel/exascel/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/exascel.dir/reader.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/exascel.dir/reader.cxx.o -c /home/alexander/exacel/exascel/reader.cxx

CMakeFiles/exascel.dir/reader.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exascel.dir/reader.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/alexander/exacel/exascel/reader.cxx > CMakeFiles/exascel.dir/reader.cxx.i

CMakeFiles/exascel.dir/reader.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exascel.dir/reader.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/alexander/exacel/exascel/reader.cxx -o CMakeFiles/exascel.dir/reader.cxx.s

CMakeFiles/exascel.dir/reader.cxx.o.requires:
.PHONY : CMakeFiles/exascel.dir/reader.cxx.o.requires

CMakeFiles/exascel.dir/reader.cxx.o.provides: CMakeFiles/exascel.dir/reader.cxx.o.requires
	$(MAKE) -f CMakeFiles/exascel.dir/build.make CMakeFiles/exascel.dir/reader.cxx.o.provides.build
.PHONY : CMakeFiles/exascel.dir/reader.cxx.o.provides

CMakeFiles/exascel.dir/reader.cxx.o.provides.build: CMakeFiles/exascel.dir/reader.cxx.o

# Object files for target exascel
exascel_OBJECTS = \
"CMakeFiles/exascel.dir/exascel.cxx.o" \
"CMakeFiles/exascel.dir/reader.cxx.o"

# External object files for target exascel
exascel_EXTERNAL_OBJECTS =

exascel: CMakeFiles/exascel.dir/exascel.cxx.o
exascel: CMakeFiles/exascel.dir/reader.cxx.o
exascel: CMakeFiles/exascel.dir/build.make
exascel: CMakeFiles/exascel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable exascel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exascel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exascel.dir/build: exascel
.PHONY : CMakeFiles/exascel.dir/build

CMakeFiles/exascel.dir/requires: CMakeFiles/exascel.dir/exascel.cxx.o.requires
CMakeFiles/exascel.dir/requires: CMakeFiles/exascel.dir/reader.cxx.o.requires
.PHONY : CMakeFiles/exascel.dir/requires

CMakeFiles/exascel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exascel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exascel.dir/clean

CMakeFiles/exascel.dir/depend:
	cd /home/alexander/exacel/exascel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexander/exacel/exascel /home/alexander/exacel/exascel /home/alexander/exacel/exascel /home/alexander/exacel/exascel /home/alexander/exacel/exascel/CMakeFiles/exascel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exascel.dir/depend

