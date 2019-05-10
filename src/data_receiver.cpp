
#include <thread>

#include <QTcpServer>
#include <QTcpSocket>
#include <QBitArray>
#include <QDir>

#include "reader_work_thread.h"
#include "data_receiver.h"

data_receiver::data_receiver(QObject* p) : data_receiver_interface (p)
{  
    tcp_server = std::make_shared<QTcpServer>();
    tcp_server->listen(QHostAddress::Any,1024);

    qDebug() << "creating " << std::thread::hardware_concurrency() << " threads";
    for(unsigned int i=0;i<std::thread::hardware_concurrency()-1;++i)
    {
        auto thr = std::make_shared<reader_work_thread>(nullptr);
        thr->quit();
        work_thread_list.
                push_back(thr);
    }

    connect(tcp_server.get(),
            SIGNAL(newConnection()),
            this,
            SLOT(newConnection()));
}

data_receiver::~data_receiver()
{

}

std::shared_ptr<reader_work_thread_interface>
data_receiver::find_worker_thread()
{
  std::shared_ptr<reader_work_thread_interface> r = nullptr;
  for(auto iter : work_thread_list)
  {
      if(!iter->isRunning())//connection_is_null())
      {
          r = iter;
          break;
      }
  }
  return r;
}

void data_receiver::newConnection()
{
    qDebug() << "On new connection()";
    QTcpSocket* s = tcp_server->nextPendingConnection();

    std::shared_ptr<reader_work_thread_interface> rwti_ptr;

    rwti_ptr = find_worker_thread();
    if(rwti_ptr)
    {
        rwti_ptr->set_params(s);
        qDebug() << "starting read thread";
        rwti_ptr->start();
    }
    else
    {
        qDebug() << "no threads available";
        s->close();
    }
}
