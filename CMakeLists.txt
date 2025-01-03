# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and specify it's a C project
project(snake VERSION 1.0 LANGUAGES C)

# Set the C standard (optional, but good practice)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -Wpedantic -g)
# Add source files to the project
#add_executable(my_ncurses_game ${PROJECT_SOURCE_DIR}/src/pacman.c)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(snake ${SOURCES})

# Find the ncurses library and set it up
find_package(Curses REQUIRED)

# Link the ncurses library to the project
target_link_libraries(snake PRIVATE ${CURSES_LIBRARIES})

# Include the header directory (if needed)
target_include_directories(snake PRIVATE ${CURSES_INCLUDE_DIR})

#Mis include
target_include_directories(snake PRIVATE ${PROJECT_SOURCE_DIR}/include)

#file(GLOB HASH_TABLE_SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)
#file(GLOB TEST_GENERAL_SOURCES ${PROJECT_SOURCE_DIR}/test/*.c)
#add_executable(TestExecutable ${TEST_SOURCES} ${TEST_GENERAL_SOURCES})
#target_include_directories(TestExecutable PRIVATE ${PROJECT_SOURCE_DIR}/include)