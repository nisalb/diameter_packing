# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/edz/Developer/diameter_binpacking

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/edz/Developer/diameter_binpacking/build

# Include any dependencies generated for this target.
include CMakeFiles/avp_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/avp_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/avp_test.dir/flags.make

CMakeFiles/avp_test.dir/src/test.c.o: CMakeFiles/avp_test.dir/flags.make
CMakeFiles/avp_test.dir/src/test.c.o: ../src/test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/edz/Developer/diameter_binpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/avp_test.dir/src/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/avp_test.dir/src/test.c.o   -c /home/edz/Developer/diameter_binpacking/src/test.c

CMakeFiles/avp_test.dir/src/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/avp_test.dir/src/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/edz/Developer/diameter_binpacking/src/test.c > CMakeFiles/avp_test.dir/src/test.c.i

CMakeFiles/avp_test.dir/src/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/avp_test.dir/src/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/edz/Developer/diameter_binpacking/src/test.c -o CMakeFiles/avp_test.dir/src/test.c.s

CMakeFiles/avp_test.dir/src/avp.c.o: CMakeFiles/avp_test.dir/flags.make
CMakeFiles/avp_test.dir/src/avp.c.o: ../src/avp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/edz/Developer/diameter_binpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/avp_test.dir/src/avp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/avp_test.dir/src/avp.c.o   -c /home/edz/Developer/diameter_binpacking/src/avp.c

CMakeFiles/avp_test.dir/src/avp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/avp_test.dir/src/avp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/edz/Developer/diameter_binpacking/src/avp.c > CMakeFiles/avp_test.dir/src/avp.c.i

CMakeFiles/avp_test.dir/src/avp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/avp_test.dir/src/avp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/edz/Developer/diameter_binpacking/src/avp.c -o CMakeFiles/avp_test.dir/src/avp.c.s

CMakeFiles/avp_test.dir/src/msg.c.o: CMakeFiles/avp_test.dir/flags.make
CMakeFiles/avp_test.dir/src/msg.c.o: ../src/msg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/edz/Developer/diameter_binpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/avp_test.dir/src/msg.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/avp_test.dir/src/msg.c.o   -c /home/edz/Developer/diameter_binpacking/src/msg.c

CMakeFiles/avp_test.dir/src/msg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/avp_test.dir/src/msg.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/edz/Developer/diameter_binpacking/src/msg.c > CMakeFiles/avp_test.dir/src/msg.c.i

CMakeFiles/avp_test.dir/src/msg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/avp_test.dir/src/msg.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/edz/Developer/diameter_binpacking/src/msg.c -o CMakeFiles/avp_test.dir/src/msg.c.s

# Object files for target avp_test
avp_test_OBJECTS = \
"CMakeFiles/avp_test.dir/src/test.c.o" \
"CMakeFiles/avp_test.dir/src/avp.c.o" \
"CMakeFiles/avp_test.dir/src/msg.c.o"

# External object files for target avp_test
avp_test_EXTERNAL_OBJECTS =

avp_test: CMakeFiles/avp_test.dir/src/test.c.o
avp_test: CMakeFiles/avp_test.dir/src/avp.c.o
avp_test: CMakeFiles/avp_test.dir/src/msg.c.o
avp_test: CMakeFiles/avp_test.dir/build.make
avp_test: CMakeFiles/avp_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/edz/Developer/diameter_binpacking/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable avp_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/avp_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/avp_test.dir/build: avp_test

.PHONY : CMakeFiles/avp_test.dir/build

CMakeFiles/avp_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/avp_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/avp_test.dir/clean

CMakeFiles/avp_test.dir/depend:
	cd /home/edz/Developer/diameter_binpacking/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/edz/Developer/diameter_binpacking /home/edz/Developer/diameter_binpacking /home/edz/Developer/diameter_binpacking/build /home/edz/Developer/diameter_binpacking/build /home/edz/Developer/diameter_binpacking/build/CMakeFiles/avp_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/avp_test.dir/depend

