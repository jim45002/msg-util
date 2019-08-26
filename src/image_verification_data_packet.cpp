#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "image_verification_data_packet.h"

image_verification_data_packet::image_verification_data_packet()
{

}

void image_verification_data_packet::set_identifier(QByteArray &id)
{
   identifier = id;
   QString filename = QString("./outgoing_verified_image_data") + QString(identifier) + ".id";
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
