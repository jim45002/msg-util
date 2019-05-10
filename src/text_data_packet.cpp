
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "text_data_packet.h"

text_data_packet::text_data_packet(QByteArray& bytes)
{  
   filename = QString("./incoming_text_data/text_data_") +
           QDateTime::currentDateTime().toString() + QString(".txt");
   QFile file(filename);
   if(file.open(QIODevice::WriteOnly))
   {
       if(file.write(bytes) == bytes.size())
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
