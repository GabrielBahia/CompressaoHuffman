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
CMAKE_SOURCE_DIR = "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build"

# Include any dependencies generated for this target.
include googlemock/CMakeFiles/gmock.dir/depend.make

# Include the progress variables for this target.
include googlemock/CMakeFiles/gmock.dir/progress.make

# Include the compile flags for this target's objects.
include googlemock/CMakeFiles/gmock.dir/flags.make

googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: googlemock/CMakeFiles/gmock.dir/flags.make
googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o: /mnt/c/Users/GC789/OneDrive/Área\ de\ Trabalho/huffmanNovo/build/lib/src/googletest/googlemock/src/gmock-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o"
	cd "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/googlemock" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gmock.dir/src/gmock-all.cc.o -c "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest/googlemock/src/gmock-all.cc"

googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock.dir/src/gmock-all.cc.i"
	cd "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/googlemock" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest/googlemock/src/gmock-all.cc" > CMakeFiles/gmock.dir/src/gmock-all.cc.i

googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock.dir/src/gmock-all.cc.s"
	cd "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/googlemock" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest/googlemock/src/gmock-all.cc" -o CMakeFiles/gmock.dir/src/gmock-all.cc.s

# Object files for target gmock
gmock_OBJECTS = \
"CMakeFiles/gmock.dir/src/gmock-all.cc.o"

# External object files for target gmock
gmock_EXTERNAL_OBJECTS =

lib/libgmock.a: googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
lib/libgmock.a: googlemock/CMakeFiles/gmock.dir/build.make
lib/libgmock.a: googlemock/CMakeFiles/gmock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../lib/libgmock.a"
	cd "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/googlemock" && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean_target.cmake
	cd "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/googlemock" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gmock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googlemock/CMakeFiles/gmock.dir/build: lib/libgmock.a

.PHONY : googlemock/CMakeFiles/gmock.dir/build

googlemock/CMakeFiles/gmock.dir/clean:
	cd "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/googlemock" && $(CMAKE_COMMAND) -P CMakeFiles/gmock.dir/cmake_clean.cmake
.PHONY : googlemock/CMakeFiles/gmock.dir/clean

googlemock/CMakeFiles/gmock.dir/depend:
	cd "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest/googlemock" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/googlemock" "/mnt/c/Users/GC789/OneDrive/Área de Trabalho/huffmanNovo/build/lib/src/googletest-build/googlemock/CMakeFiles/gmock.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : googlemock/CMakeFiles/gmock.dir/depend

