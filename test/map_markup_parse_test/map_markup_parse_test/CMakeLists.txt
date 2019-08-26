cmake_minimum_required (VERSION 2.6)
project(map_markup_parse_data_test)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

include_directories(
       ${QT_INCLUDES}
        ../../../libs/map_widget_factory
                   )

set(SOURCE_DIR ./)

find_package(Marble CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

#QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )


include_directories(
       ${QT_INCLUDES}
       /home/amnesia/Persistent/github/msg-util/msg-util/src
       )


set(test_SOURCES "main.cpp"
                 "mainwindow.h"
                 "mainwindow.cpp"
                 "../src/map_markup_post.cpp"
                 "../src/map_markup_post.h"
                 "../src/map_markup_post_interface.h"
                 "mainwindow.ui")

add_executable(map_markup_parse_data_test ${test_SOURCES})
target_link_libraries(map_markup_parse_data_test Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network
                                map_scribble_widget_factory
                                )
