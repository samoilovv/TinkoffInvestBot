cmake_minimum_required(VERSION 3.11)

project(movingAverage)

find_package(Qt5 REQUIRED COMPONENTS Core)

add_library(${PROJECT_NAME} MODULE
    movingAveragePlugin.h
    movingAveragePlugin.cpp
)

generate_export_header(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    hevaa::interfaces
    hevaa::core
    hw_grpc_proto
    TinkoffInvestSDK
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../TinkoffInvestSDK)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../TinkoffInvestSDK/services)

set_robots_dir(${PROJECT_NAME})


