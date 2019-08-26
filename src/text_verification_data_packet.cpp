#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "text_verification_data_packet.h"

text_verification_data_packet::text_verification_data_packet()
{

}

void text_verification_data_packet::set_identifier(QByteArray &id)
{
   identifier = id;
   QString filename = QString("./outgoing_verified_text_data") + QString(identifier) + ".id";
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
