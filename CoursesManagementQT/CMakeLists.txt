cmake_minimum_required(VERSION 3.25)
project(CoursesManagementQT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/ultra/Qt/6.5.1/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(QTlab main.cpp console.cpp Contract.cpp export.cpp Repo.cpp Service.cpp Studii.cpp validator.cpp Headers/console.h Headers/Contract.h Headers/export.h Headers/Repo.h Headers/Service.h Headers/Studii.h Headers/undo.h Headers/validator.h Headers/VektorTemplate.h GUI.h GUI.cpp StudiiGUI.h SudiiGUI.cpp)
target_link_libraries(QTlab
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

