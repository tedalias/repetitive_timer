cmake_minimum_required(VERSION 3.5)

project(timer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(timer main.cpp mainwindow.cpp resources.qrc)

target_link_libraries(timer PRIVATE Qt5::Core)
target_link_libraries(timer PRIVATE Qt5::Widgets)
