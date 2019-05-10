cmake_minimum_required (VERSION 2.6)
project(data_receiver_test)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})

set ( RESOURCES
  resources.qrc
)

enable_testing()
find_package(GTest REQUIRED)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

include_directories(${QT_INCLUDES} ../../../../messenger)

QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )

set(data_receiver_test_SOURCES "main.cpp" 
			       "test_data_transmitter.h" 
                               "test_data_transmitter.cpp"
                               "../../../../messenger/data_receiver.h"
                               "../../../../messenger/data_receiver.cpp"
                               "../../../../messenger/data_receiver_interface.h"
                               "../../../../messenger/reader_work_thread"
                               "../../../../messenger/reader_work_thread_interface.h"
                               "../../../../messenger/packet_types.h"
                               "../../../../messenger/text_data_packet.h"
                               "../../../../messenger/text_data_packet.cpp"
                               "../../../../messenger/voice_data_packet.h"
                               "../../../../messenger/voice_data_packet.cpp"
                               "../../../../messenger/markup_data_packet.h"
                               "../../../../messenger/markup_data_packet.cpp"
                               ${RES_SOURCES})

add_executable(data_receiver_test ${data_receiver_test_SOURCES})
target_link_libraries(data_receiver_test Qt5::Core Qt5::Network GTest::GTest GTest::Main)

