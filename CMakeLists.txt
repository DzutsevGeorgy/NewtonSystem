cmake_minimum_required(VERSION 3.14)
project(NewtonSystem)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

qt5_wrap_ui(UI_HEADERS mainwindow.ui)
add_executable(NewtonSystem main.cpp ${UI_HEADERS} mainwindow.h mainwindow.cpp chartview.cpp chartview.h)

target_link_libraries(NewtonSystem Qt5::Core)
target_link_libraries(NewtonSystem Qt5::Widgets)
target_link_libraries(NewtonSystem Qt5::Charts)