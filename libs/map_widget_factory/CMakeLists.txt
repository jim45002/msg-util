cmake_minimum_required (VERSION 2.6)
project(map_scribble_widget_factory)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

set ( RESOURCES
  resources.qrc
)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

include_directories(${QT_INCLUDES})
link_directories(/usr/local/lib)

QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )

set(map_scribble_widget_factory_SOURCES
    "map_widget_factory.cpp"
    "map_widget.cpp"
    "map_paint_layer.cpp"
    "scribble_manager.cpp"
    "map_widget_factory.h"
    "map_widget_factory_global.h"
    "map_widget.h"
    "map_widget_interface.h"
    "map_paint_layer.h"
    "scribble_manager.h"
    "marble_map_layer.h"
    "marble_map_layer.cpp"
    ${RES_SOURCES})

add_library(map_scribble_widget_factory SHARED
    ${map_scribble_widget_factory_SOURCES})
target_link_libraries(map_scribble_widget_factory
    Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network marblewidget-qt5)

include(GNUInstallDirs)

install(TARGETS map_scribble_widget_factory
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
