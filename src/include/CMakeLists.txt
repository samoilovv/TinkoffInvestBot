cmake_minimum_required(VERSION 3.11)

project(hevaainterfaces LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (${CMAKE_VERSION} VERSION_LESS 3.19.0)
    add_library(${PROJECT_NAME} INTERFACE)
else()
    add_library(${PROJECT_NAME}
        INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/imoduleplugin.h
            ${CMAKE_CURRENT_SOURCE_DIR}/test-plugin.h
    )
endif()

add_library(hevaa::interfaces ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
