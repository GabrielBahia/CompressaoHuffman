cmake_minimum_required (VERSION 3.14)

# Define the project
project(book_read)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add definitiion for huffman_coding library
add_library(huffmancoding src/HuffmanCoding.cpp)

# Add definitiion for node_queue library
add_library(nodequeue src/NodeQueue.cpp)

# Add definitiion for node_tree library
add_library(nodetree src/NodeTree.cpp)

# Add definitiion for priority_queue library
add_library(priorityqueue src/PriorityQueue.cpp)

# Add definition for the book_read binary
add_executable(book_read src/main.cpp)
target_link_libraries(book_read huffmancoding)
target_link_libraries(book_read nodequeue)
target_link_libraries(book_read nodetree)
target_link_libraries(book_read priorityqueue)

# Include Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Third-party library
include(ExternalProject)
ExternalProject_Add(googletest
    PREFIX "${CMAKE_BINARY_DIR}/lib"
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "release-1.12.0"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/installed
)

# Prevent build on all targets build
set_target_properties(googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)

# Define ${CMAKE_INSTALL_...} variables
include(GNUInstallDirs)

# Specify where third-party libraries are located
link_directories(${CMAKE_BINARY_DIR}/lib/installed/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/installed/${CMAKE_INSTALL_INCLUDEDIR})

# This is required for googletest
find_package(Threads REQUIRED)

enable_testing()

# Tests
add_executable(huffman_test tests/huffman_test.cpp)

target_link_libraries(huffman_test huffmancoding nodequeue nodetree priorityqueue gtest Threads::Threads)

add_dependencies(huffman_test googletest)


