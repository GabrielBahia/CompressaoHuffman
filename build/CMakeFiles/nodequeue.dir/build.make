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
CMAKE_SOURCE_DIR = "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build"

# Include any dependencies generated for this target.
include CMakeFiles/nodequeue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nodequeue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nodequeue.dir/flags.make

CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.o: CMakeFiles/nodequeue.dir/flags.make
CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.o: ../src/NodeQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.o -c "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/src/NodeQueue.cpp"

CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/src/NodeQueue.cpp" > CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.i

CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/src/NodeQueue.cpp" -o CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.s

# Object files for target nodequeue
nodequeue_OBJECTS = \
"CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.o"

# External object files for target nodequeue
nodequeue_EXTERNAL_OBJECTS =

libnodequeue.a: CMakeFiles/nodequeue.dir/src/NodeQueue.cpp.o
libnodequeue.a: CMakeFiles/nodequeue.dir/build.make
libnodequeue.a: CMakeFiles/nodequeue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libnodequeue.a"
	$(CMAKE_COMMAND) -P CMakeFiles/nodequeue.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nodequeue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nodequeue.dir/build: libnodequeue.a

.PHONY : CMakeFiles/nodequeue.dir/build

CMakeFiles/nodequeue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nodequeue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nodequeue.dir/clean

CMakeFiles/nodequeue.dir/depend:
	cd "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/CMakeFiles/nodequeue.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/nodequeue.dir/depend
