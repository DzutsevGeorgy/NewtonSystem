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

qt5_wrap_ui(UI_HEADERS src/mainwindow/mainwindow.ui)
add_executable(NewtonSystem src/main.cpp ${UI_HEADERS} src/mainwindow/mainwindow.h src/mainwindow/mainwindow.cpp src/chartview/chartview.cpp src/chartview/chartview.h src/chart/chart.cpp src/chart/chart.h)

target_link_libraries(NewtonSystem Qt5::Core)
target_link_libraries(NewtonSystem Qt5::Widgets)
target_link_libraries(NewtonSystem Qt5::Charts)