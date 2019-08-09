#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "verification_data_packet.h"

verification_data_packet::verification_data_packet()
{

}

void verification_data_packet::set_identifier(QByteArray &id)
{
   identifier = id;
   QString filename = QString("./verify_data/") + QString(identifier) + ".id";
   QFile file(filename);
   if(file.open(QIODevice::WriteOnly))
   {
       if(file.write(identifier) == identifier.size())
       {

       }
       else
       {
           qDebug() << "file write error on " << file.fileName();
       }
   }
   else
   {
       qDebug() << "unable to open file " << file.fileName();
   }
}
