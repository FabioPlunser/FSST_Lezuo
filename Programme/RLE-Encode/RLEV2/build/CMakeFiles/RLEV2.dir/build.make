# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/build

# Include any dependencies generated for this target.
include CMakeFiles/RLEV2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RLEV2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RLEV2.dir/flags.make

CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.o: CMakeFiles/RLEV2.dir/flags.make
CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.o: ../src/RLE-Encode-V2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.o"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.o   -c /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/src/RLE-Encode-V2.c

CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.i"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/src/RLE-Encode-V2.c > CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.i

CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.s"
	/bin/gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/src/RLE-Encode-V2.c -o CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.s

# Object files for target RLEV2
RLEV2_OBJECTS = \
"CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.o"

# External object files for target RLEV2
RLEV2_EXTERNAL_OBJECTS =

RLEV2: CMakeFiles/RLEV2.dir/src/RLE-Encode-V2.c.o
RLEV2: CMakeFiles/RLEV2.dir/build.make
RLEV2: CMakeFiles/RLEV2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable RLEV2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RLEV2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RLEV2.dir/build: RLEV2

.PHONY : CMakeFiles/RLEV2.dir/build

CMakeFiles/RLEV2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RLEV2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RLEV2.dir/clean

CMakeFiles/RLEV2.dir/depend:
	cd /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2 /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2 /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/build /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/build /home/peppi/FSST_Lezuo/Programme/RLE-Encode/RLEV2/build/CMakeFiles/RLEV2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RLEV2.dir/depend

