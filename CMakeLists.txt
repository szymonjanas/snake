cmake_minimum_required(VERSION 2.8)

project(snake CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_INCLUDE_DIR "/home/szymon/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/szymon/SFML-2.5.1/lib")
set(SFML_DIR "/home/szymon/SFML-2.5.1/lib/cmake/SFML")
link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_compile_options(-c
        -Wall
        -Wextra
        -Winit-self
        -Wold-style-cast
        -Woverloaded-virtual
        -Wuninitialized
        -pedantic
        -pedantic-errors
        -g
)

set (SRC_LIST
    snake/main.cpp
    snake/model-snake.cpp
    snake/model-board.cpp
    snake/controler.cpp
    snake/view.cpp
    snake/err_msg.cpp
    )

add_library(${PROJECT_NAME}-lib ${SRC_LIST})
add_executable(${PROJECT_NAME} snake/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

target_link_libraries (${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
