cmake_minimum_required(VERSION 3.22.1)
project(test_gtk)


include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})


add_executable(
    test_gtk
    main.cpp
)
target_link_libraries(
    test_gtk
    matheval
    ${GTK4_LIBRARIES}
)