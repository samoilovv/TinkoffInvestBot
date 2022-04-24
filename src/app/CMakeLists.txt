cmake_minimum_required(VERSION 3.11)

project(hevaa_srv)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)

include("cmake/git-version-generator.cmake")

set(GITVERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/git-version")
set(VERSION_HEADER_FILE "${CMAKE_CURRENT_BINARY_DIR}/version.h")

generate_git_version(
        git_version
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${GITVERSION_FILE}"
)

add_custom_command(
        OUTPUT "${VERSION_HEADER_FILE}"
        COMMAND ${CMAKE_COMMAND}
                -D "GIT_VERSION=${GITVERSION_FILE}"
                -D "MY_VERSION_HEADER=${VERSION_HEADER_FILE}"
                -P "${CMAKE_CURRENT_LIST_DIR}/generate-version-header.cmake"
        DEPENDS
                "${GITVERSION_FILE}"
                "${CMAKE_CURRENT_LIST_DIR}/generate-version-header.cmake"
)

file(GLOB_RECURSE TARGET_PRIVATE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE TARGET_HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${TARGET_PRIVATE_SRC} ${TARGET_HDR} ${VERSION_HEADER_FILE})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
    )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    hevaa::interfaces
    hevaa::core
    Worker
    )

add_dependencies(${PROJECT_NAME} git_version)

if (EXISTS ${GITVERSION_FILE})
    file(READ ${GITVERSION_FILE} VER)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION_HEVAA="${VER}")

message("---------------------------------
Version = ${VER}
---------------------------------")
