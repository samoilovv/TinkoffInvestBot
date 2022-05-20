cmake_minimum_required(VERSION 3.11)

project(core)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core)

file(GLOB_RECURSE TARGET_PRIVATE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE TARGET_HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

add_library(${PROJECT_NAME} SHARED ${TARGET_PRIVATE_SRC} ${TARGET_HDR})

add_library(hevaa::core ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    hevaa::interfaces
    )
