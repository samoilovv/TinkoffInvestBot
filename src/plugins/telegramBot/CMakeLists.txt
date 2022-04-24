cmake_minimum_required(VERSION 3.11)

project(TelegramBotPlugin)

find_package(Qt5 REQUIRED COMPONENTS Core Sql)

add_library(${PROJECT_NAME} MODULE
    telegramBotPlugin.h
    telegramBotPlugin.cpp
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
    Qt5::Sql
    hevaa::interfaces
    hevaa::core
    TgBot
    )

set_plugin_dir(${PROJECT_NAME})

