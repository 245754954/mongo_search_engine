# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ftpuser/wiser/wiser/wiser/trunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ftpuser/wiser/wiser/wiser/trunk

# Include any dependencies generated for this target.
include CMakeFiles/hello_mongoc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hello_mongoc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hello_mongoc.dir/flags.make

CMakeFiles/hello_mongoc.dir/mongodatabase.c.o: CMakeFiles/hello_mongoc.dir/flags.make
CMakeFiles/hello_mongoc.dir/mongodatabase.c.o: mongodatabase.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hello_mongoc.dir/mongodatabase.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_mongoc.dir/mongodatabase.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/mongodatabase.c

CMakeFiles/hello_mongoc.dir/mongodatabase.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_mongoc.dir/mongodatabase.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/mongodatabase.c > CMakeFiles/hello_mongoc.dir/mongodatabase.c.i

CMakeFiles/hello_mongoc.dir/mongodatabase.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_mongoc.dir/mongodatabase.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/mongodatabase.c -o CMakeFiles/hello_mongoc.dir/mongodatabase.c.s

# Object files for target hello_mongoc
hello_mongoc_OBJECTS = \
"CMakeFiles/hello_mongoc.dir/mongodatabase.c.o"

# External object files for target hello_mongoc
hello_mongoc_EXTERNAL_OBJECTS =

hello_mongoc: CMakeFiles/hello_mongoc.dir/mongodatabase.c.o
hello_mongoc: CMakeFiles/hello_mongoc.dir/build.make
hello_mongoc: /usr/local/lib/libmongoc-1.0.so
hello_mongoc: /usr/local/lib/libbson-1.0.so
hello_mongoc: /usr/lib/x86_64-linux-gnu/libssl.so
hello_mongoc: /usr/lib/x86_64-linux-gnu/libcrypto.so
hello_mongoc: /usr/lib/x86_64-linux-gnu/libsnappy.so
hello_mongoc: /usr/lib/x86_64-linux-gnu/libicuuc.so
hello_mongoc: CMakeFiles/hello_mongoc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable hello_mongoc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello_mongoc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hello_mongoc.dir/build: hello_mongoc

.PHONY : CMakeFiles/hello_mongoc.dir/build

CMakeFiles/hello_mongoc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hello_mongoc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hello_mongoc.dir/clean

CMakeFiles/hello_mongoc.dir/depend:
	cd /home/ftpuser/wiser/wiser/wiser/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ftpuser/wiser/wiser/wiser/trunk /home/ftpuser/wiser/wiser/wiser/trunk /home/ftpuser/wiser/wiser/wiser/trunk /home/ftpuser/wiser/wiser/wiser/trunk /home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles/hello_mongoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hello_mongoc.dir/depend
