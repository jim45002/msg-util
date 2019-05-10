#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QObject>
#include <QFile>
#include <QBitArray>
#include <QDebug>

#include "data_receiver.h"
#include "test_data_transmitter.h"

using namespace std;


// The fixture for testing class tor_config_options.
class data_receiver_test : public ::testing::Test {
 protected:

  data_receiver_test() {
  }

  ~data_receiver_test() override {
  }

  void SetUp() override {

  }

  void TearDown() override {

  }

};

////////////////////////////////////
TEST_F(data_receiver_test, data_receiver_data_packet_reception_test)
{

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc,argv);
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
