# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/eeprom_read_program.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/eeprom_read_program.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eeprom_read_program.dir/flags.make

CMakeFiles/eeprom_read_program.dir/main.c.o: CMakeFiles/eeprom_read_program.dir/flags.make
CMakeFiles/eeprom_read_program.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/eeprom_read_program.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/eeprom_read_program.dir/main.c.o   -c "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/main.c"

CMakeFiles/eeprom_read_program.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eeprom_read_program.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/main.c" > CMakeFiles/eeprom_read_program.dir/main.c.i

CMakeFiles/eeprom_read_program.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eeprom_read_program.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/main.c" -o CMakeFiles/eeprom_read_program.dir/main.c.s

CMakeFiles/eeprom_read_program.dir/conversions.c.o: CMakeFiles/eeprom_read_program.dir/flags.make
CMakeFiles/eeprom_read_program.dir/conversions.c.o: ../conversions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/eeprom_read_program.dir/conversions.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/eeprom_read_program.dir/conversions.c.o   -c "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/conversions.c"

CMakeFiles/eeprom_read_program.dir/conversions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eeprom_read_program.dir/conversions.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/conversions.c" > CMakeFiles/eeprom_read_program.dir/conversions.c.i

CMakeFiles/eeprom_read_program.dir/conversions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eeprom_read_program.dir/conversions.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/conversions.c" -o CMakeFiles/eeprom_read_program.dir/conversions.c.s

CMakeFiles/eeprom_read_program.dir/file_read.c.o: CMakeFiles/eeprom_read_program.dir/flags.make
CMakeFiles/eeprom_read_program.dir/file_read.c.o: ../file_read.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/eeprom_read_program.dir/file_read.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/eeprom_read_program.dir/file_read.c.o   -c "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/file_read.c"

CMakeFiles/eeprom_read_program.dir/file_read.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eeprom_read_program.dir/file_read.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/file_read.c" > CMakeFiles/eeprom_read_program.dir/file_read.c.i

CMakeFiles/eeprom_read_program.dir/file_read.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eeprom_read_program.dir/file_read.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/file_read.c" -o CMakeFiles/eeprom_read_program.dir/file_read.c.s

# Object files for target eeprom_read_program
eeprom_read_program_OBJECTS = \
"CMakeFiles/eeprom_read_program.dir/main.c.o" \
"CMakeFiles/eeprom_read_program.dir/conversions.c.o" \
"CMakeFiles/eeprom_read_program.dir/file_read.c.o"

# External object files for target eeprom_read_program
eeprom_read_program_EXTERNAL_OBJECTS =

eeprom_read_program: CMakeFiles/eeprom_read_program.dir/main.c.o
eeprom_read_program: CMakeFiles/eeprom_read_program.dir/conversions.c.o
eeprom_read_program: CMakeFiles/eeprom_read_program.dir/file_read.c.o
eeprom_read_program: CMakeFiles/eeprom_read_program.dir/build.make
eeprom_read_program: CMakeFiles/eeprom_read_program.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable eeprom_read_program"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eeprom_read_program.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eeprom_read_program.dir/build: eeprom_read_program

.PHONY : CMakeFiles/eeprom_read_program.dir/build

CMakeFiles/eeprom_read_program.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eeprom_read_program.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eeprom_read_program.dir/clean

CMakeFiles/eeprom_read_program.dir/depend:
	cd "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program" "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program" "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug" "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug" "/Users/klemensrameder/Library/Mobile Documents/com~apple~CloudDocs/Diplomarbeit/Software/eeprom_program/eeprom_read_program/cmake-build-debug/CMakeFiles/eeprom_read_program.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/eeprom_read_program.dir/depend

