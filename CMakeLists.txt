cmake_minimum_required(VERSION 3.22.1)
project(test_gtk)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})

# Set the C++ standard to the latest version (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    test_gtk
    main.cpp
)

target_link_libraries(
    test_gtk
    matheval
    ${GTK4_LIBRARIES}
)
