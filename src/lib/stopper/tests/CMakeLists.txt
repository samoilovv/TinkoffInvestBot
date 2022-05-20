project(hevaatest LANGUAGES CXX)

find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

set(PREFIX_TESTS utest_)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE PROJECT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(${PREFIX_TESTS}${PROJECT_NAME})

generate_export_header(${PREFIX_TESTS}${PROJECT_NAME})

target_include_directories(${PREFIX_TESTS}${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/..
        ${CMAKE_CURRENT_SOURCE_DIR}/..
    )

target_sources(${PREFIX_TESTS}${PROJECT_NAME} PRIVATE
    ${PROJECT_SRC}
    "../stopper.h"
    "../stopper.cpp"
    )

target_link_libraries(${PREFIX_TESTS}${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Test
)


