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
include CMakeFiles/searchengine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/searchengine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/searchengine.dir/flags.make

CMakeFiles/searchengine.dir/searchengine.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/searchengine.c.o: searchengine.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/searchengine.dir/searchengine.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/searchengine.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/searchengine.c

CMakeFiles/searchengine.dir/searchengine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/searchengine.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/searchengine.c > CMakeFiles/searchengine.dir/searchengine.c.i

CMakeFiles/searchengine.dir/searchengine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/searchengine.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/searchengine.c -o CMakeFiles/searchengine.dir/searchengine.c.s

CMakeFiles/searchengine.dir/myclient.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/myclient.c.o: myclient.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/searchengine.dir/myclient.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/myclient.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/myclient.c

CMakeFiles/searchengine.dir/myclient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/myclient.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/myclient.c > CMakeFiles/searchengine.dir/myclient.c.i

CMakeFiles/searchengine.dir/myclient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/myclient.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/myclient.c -o CMakeFiles/searchengine.dir/myclient.c.s

CMakeFiles/searchengine.dir/wiser.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/wiser.c.o: wiser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/searchengine.dir/wiser.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/wiser.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/wiser.c

CMakeFiles/searchengine.dir/wiser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/wiser.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/wiser.c > CMakeFiles/searchengine.dir/wiser.c.i

CMakeFiles/searchengine.dir/wiser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/wiser.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/wiser.c -o CMakeFiles/searchengine.dir/wiser.c.s

CMakeFiles/searchengine.dir/util.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/util.c.o: util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/searchengine.dir/util.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/util.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/util.c

CMakeFiles/searchengine.dir/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/util.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/util.c > CMakeFiles/searchengine.dir/util.c.i

CMakeFiles/searchengine.dir/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/util.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/util.c -o CMakeFiles/searchengine.dir/util.c.s

CMakeFiles/searchengine.dir/token.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/token.c.o: token.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/searchengine.dir/token.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/token.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/token.c

CMakeFiles/searchengine.dir/token.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/token.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/token.c > CMakeFiles/searchengine.dir/token.c.i

CMakeFiles/searchengine.dir/token.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/token.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/token.c -o CMakeFiles/searchengine.dir/token.c.s

CMakeFiles/searchengine.dir/search.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/search.c.o: search.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/searchengine.dir/search.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/search.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/search.c

CMakeFiles/searchengine.dir/search.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/search.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/search.c > CMakeFiles/searchengine.dir/search.c.i

CMakeFiles/searchengine.dir/search.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/search.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/search.c -o CMakeFiles/searchengine.dir/search.c.s

CMakeFiles/searchengine.dir/postings.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/postings.c.o: postings.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/searchengine.dir/postings.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/postings.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/postings.c

CMakeFiles/searchengine.dir/postings.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/postings.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/postings.c > CMakeFiles/searchengine.dir/postings.c.i

CMakeFiles/searchengine.dir/postings.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/postings.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/postings.c -o CMakeFiles/searchengine.dir/postings.c.s

CMakeFiles/searchengine.dir/database.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/database.c.o: database.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/searchengine.dir/database.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/database.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/database.c

CMakeFiles/searchengine.dir/database.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/database.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/database.c > CMakeFiles/searchengine.dir/database.c.i

CMakeFiles/searchengine.dir/database.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/database.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/database.c -o CMakeFiles/searchengine.dir/database.c.s

CMakeFiles/searchengine.dir/wikiload.c.o: CMakeFiles/searchengine.dir/flags.make
CMakeFiles/searchengine.dir/wikiload.c.o: wikiload.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/searchengine.dir/wikiload.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/searchengine.dir/wikiload.c.o   -c /home/ftpuser/wiser/wiser/wiser/trunk/wikiload.c

CMakeFiles/searchengine.dir/wikiload.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/searchengine.dir/wikiload.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ftpuser/wiser/wiser/wiser/trunk/wikiload.c > CMakeFiles/searchengine.dir/wikiload.c.i

CMakeFiles/searchengine.dir/wikiload.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/searchengine.dir/wikiload.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ftpuser/wiser/wiser/wiser/trunk/wikiload.c -o CMakeFiles/searchengine.dir/wikiload.c.s

# Object files for target searchengine
searchengine_OBJECTS = \
"CMakeFiles/searchengine.dir/searchengine.c.o" \
"CMakeFiles/searchengine.dir/myclient.c.o" \
"CMakeFiles/searchengine.dir/wiser.c.o" \
"CMakeFiles/searchengine.dir/util.c.o" \
"CMakeFiles/searchengine.dir/token.c.o" \
"CMakeFiles/searchengine.dir/search.c.o" \
"CMakeFiles/searchengine.dir/postings.c.o" \
"CMakeFiles/searchengine.dir/database.c.o" \
"CMakeFiles/searchengine.dir/wikiload.c.o"

# External object files for target searchengine
searchengine_EXTERNAL_OBJECTS =

searchengine: CMakeFiles/searchengine.dir/searchengine.c.o
searchengine: CMakeFiles/searchengine.dir/myclient.c.o
searchengine: CMakeFiles/searchengine.dir/wiser.c.o
searchengine: CMakeFiles/searchengine.dir/util.c.o
searchengine: CMakeFiles/searchengine.dir/token.c.o
searchengine: CMakeFiles/searchengine.dir/search.c.o
searchengine: CMakeFiles/searchengine.dir/postings.c.o
searchengine: CMakeFiles/searchengine.dir/database.c.o
searchengine: CMakeFiles/searchengine.dir/wikiload.c.o
searchengine: CMakeFiles/searchengine.dir/build.make
searchengine: CMakeFiles/searchengine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable searchengine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/searchengine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/searchengine.dir/build: searchengine

.PHONY : CMakeFiles/searchengine.dir/build

CMakeFiles/searchengine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/searchengine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/searchengine.dir/clean

CMakeFiles/searchengine.dir/depend:
	cd /home/ftpuser/wiser/wiser/wiser/trunk && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ftpuser/wiser/wiser/wiser/trunk /home/ftpuser/wiser/wiser/wiser/trunk /home/ftpuser/wiser/wiser/wiser/trunk /home/ftpuser/wiser/wiser/wiser/trunk /home/ftpuser/wiser/wiser/wiser/trunk/CMakeFiles/searchengine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/searchengine.dir/depend

