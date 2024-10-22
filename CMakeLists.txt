cmake_minimum_required(VERSION 3.29)
project(accountManagement)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/qt6")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(accountManagement main.cpp
        User.cpp
        User.h
        UserList.cpp
        UserList.h
        StaticVariables.h)
target_link_libraries(accountManagement
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

