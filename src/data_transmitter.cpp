
#include <QDir>

#include "writer_work_thread_interface.h"
#include "writer_work_thread.h"
#include "data_transmitter.h"

data_transmitter::data_transmitter(QString receiving_peer, QObject *parent)
    : data_transmitter_interface(parent),
      receiving_peer_address(receiving_peer)

{
    network_proxy = new QNetworkProxy(QNetworkProxy::Socks5Proxy,
                                      QString("127.0.0.1"),
                                      9054);
    tcp_socket = std::make_shared<QTcpSocket>();

    connect(tcp_socket.get(),SIGNAL(connected()),
            this,
            SLOT(connected_to_host_completed()));

    tcp_socket->setProxy(*network_proxy);

    qDebug() << "creating " << std::thread::hardware_concurrency()
             << " threads";
    for(unsigned int i=0;i<std::thread::hardware_concurrency()-1;++i)
    {
       auto thr = std::make_shared<writer_work_thread>(nullptr);
       thr->quit();
       work_thread_list.
               push_back(thr);

    }
    qDebug() << "connecting to host";
    tcp_socket->connectToHost(receiving_peer_address,80);
}


std::shared_ptr<writer_work_thread_interface>
data_transmitter::find_worker_thread()
{
  std::shared_ptr<writer_work_thread_interface> r = nullptr;
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

void data_transmitter::connected_to_host_completed()
{
    std::shared_ptr<writer_work_thread_interface> wwti_ptr;

    wwti_ptr = find_worker_thread();
    if(wwti_ptr)
    {
        wwti_ptr->set_params(tcp_socket.get());
        qDebug() << "starting write thread";
        wwti_ptr->start();
    }
    else
    {
        qDebug() << "no threads available";
        tcp_socket->close();
    }
}
