cmake_minimum_required(VERSION 4.1)
project(test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(test MACOSX_BUNDLE
        main.cpp
)

target_link_libraries(test
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

