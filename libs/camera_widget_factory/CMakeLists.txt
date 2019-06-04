cmake_minimum_required (VERSION 2.6)
project(cameraWidget)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS}
                ${Qt5Widgets_INCLUDE_DIRS}
                ${Qt5Multimedia_INCLUDE_DIRS})

include_directories( ${QT_INCLUDES} )

link_directories( /usr/local/lib )

set(SOURCE_DIR ./)

find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)
find_package(Qt5MultimediaWidgets CONFIG REQUIRED)


#QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )

set(cameraWidget_SOURCES "./camera_widget.h"
                         "./camera_widget.cpp"
                         "./camera_widget_factory.h"
                         "./camera_widget_factory.cpp"
                         "./camera_widget_interface.h"
                         "./camera_widget.ui"
                         "./camera_device.h"
                         "./camera_device.cpp"
                         "./video_buffer_device.h"
                         "./video_buffer_device.cpp"
                         "./video_widget.h"
                         "./video_widget.cpp"
                         "./camera_device_interface.h"
                         "./camera_info_interface.h"
                         "./camera_info.h"
                         "./camera_info.cpp"
                         "./video_frame_handler.h"
                         "./video_frame_handler.cpp"
                         "./video_frame_handler_interface.h"
                         "./detect_filter.h"
                         "./detect_filter.cpp")

add_library(cameraWidget SHARED ${cameraWidget_SOURCES})
target_link_libraries(cameraWidget Qt5::Core Qt5::Network Qt5::Gui Qt5::Widgets Qt5::Multimedia Qt5::MultimediaWidgets opencv_core opencv_objdetect opencv_imgproc opencv_ml opencv_highgui)

include(GNUInstallDirs)

install(TARGETS cameraWidget
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
