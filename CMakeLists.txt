cmake_minimum_required (VERSION 2.6)
project(msg_util)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

include_directories(
       ${QT_INCLUDES}
        ../../libs/qwt/qwt-6.1.3/src
        ./libs/map_widget_factory
        ./libs/camera_widget_factory/
                   )

link_directories(
                  ../../libs/speex-1.2
                  ../../libs/speex-1.2/libspeex/.libs
                 )

set(SOURCE_DIR ./src)

find_package(Marble CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)


#QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )

set(msg_util_SOURCES "./src/main.cpp"
                      "./src/data_receiver.h"
                      "./src/data_receiver.cpp"
                      "./src/data_receiver_interface.h"
                      "./src/data_transmitter.h"
                      "./src/data_transmitter.cpp"
                      "./src/data_transmitter_interface.h"
                      "./src/reader_work_thread.h"
                      "./src/reader_work_thread.cpp"
                      "./src/reader_work_thread_interface.h"
                      "./src/writer_work_thread.h"
                      "./src/writer_work_thread.cpp"
                      "./src/writer_work_thread_interface.h"
                      "./src/packet_types.h"
                      "./src/text_data_packet.h"
                      "./src/text_data_packet.cpp"
                      "./src/voice_data_packet.h"
                      "./src/voice_data_packet.cpp"
                      "./src/markup_data_packet.h"
                      "./src/markup_data_packet.cpp"
                      "./src/messenger_dialog.h"
                      "./src/messenger_dialog.cpp"
                      "./src/messenger_dialog.ui"
                      "./src/audio_file_player_thread.h"
                      "./src/audio_file_player_thread.cpp"
                      "./src/audio_buffer_device.h"
                      "./src/audio_buffer_device.cpp"
                      "./src/Encoder.h"
                      "./src/Encoder.cpp"
                      "./src/Decoder.h"
                      "./src/Decoder.cpp"
                      "./src/audio_read_thread.h"
                      "./src/audio_read_thread.cpp"
                      "./src/data_transmitter_factory.h"
                      "./src/data_transmitter_factory.cpp"
                      "./src/data_transmitter_factory_interface.h"
                      "./src/data_receiver_factory.h"
                      "./src/data_receiver_factory_interface.h"
                      "./src/data_receiver_factory.cpp"
                      "./src/image_data_packet.h"
                      "./src/image_data_packet.cpp"
                      "./src/image_data_types.h"
                      "./src/incoming_av_data_sync.h"
                      "./src/incoming_av_data_sync.cpp"
                      "./src/incoming_av_data_sync_interface.h"
                      "./src/video_data_packet.h"
                      "./src/video_data_packet.cpp"
                      "./src/map_markup_post_interface.h"
                      "./src/map_markup_post.h"
                      "./src/map_markup_post.cpp")
                       
add_executable(msg_util ${msg_util_SOURCES})
target_link_libraries(msg_util Qt5::Core Qt5::Network Qt5::Gui Qt5::Widgets Qt5::Multimedia
                                map_scribble_widget_factory qwt speex speexdsp
                                cameraWidget)
