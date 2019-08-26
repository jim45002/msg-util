#include <QSizePolicy>
#include <QDateTime>
#include <QDir>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QLine>
#include <QPoint>
#include <QLabel>
#include <QList>
#include <QColor>
#include <QFont>
#include <QLine>
#include <QPoint>
#include <QProcess>
#include <QDataStream>
#include <QUrl>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QString>

#include "scribble_manager.h"
#include "map_paint_layer.h"
#include "map_markup_post.h"
#include "map_widget_interface.h"


map_markup_post::map_markup_post(map_widget_interface *parent)
    : mwi_p(parent)
{

}

void map_markup_post::set_data_location(const QString &data_path)
{
    data_location_path = data_path;
}

void map_markup_post::save_map_markup()
{

  auto paint_layer = mwi_p->get_map_widget_paint_layer();
  auto scribble_mgr = paint_layer->get_scribble_manager();

  auto map_text_list_data = scribble_mgr->get_text_list_data();
  auto map_lines_list_data = scribble_mgr->get_lines_list_data();

  QByteArray map_lines_buffer, tmp;
  int count=0;
  for(auto iter : map_lines_list_data)
  {
      tmp += iter.get_packed_data_buffer();
      ++count;
  }

  map_lines_buffer.append(reinterpret_cast<char*>(&count),sizeof(int));
  map_lines_buffer.append(tmp);

  QByteArray map_text_buffer;
  count=0;
  int size;
  tmp.clear();
  for(auto iter : map_text_list_data)
  {
      size = iter.get_packed_data_buffer().size();
      tmp.append(reinterpret_cast<char*>(&size),sizeof(int));
      tmp += iter.get_packed_data_buffer();
      ++count;
  }
  map_text_buffer.append(reinterpret_cast<char*>(&count),sizeof(int));
  size = tmp.size();
  map_text_buffer.append(reinterpret_cast<char*>(&size),sizeof(int));
  map_text_buffer.append(tmp);

  QByteArray map_scale_data_buffer;
  qreal lat = mwi_p->centerLatitude();
  qreal lon = mwi_p->centerLongitude();
  int zoom = mwi_p->zoom();

  map_scale_data_buffer.append(reinterpret_cast<char*>(&lat),sizeof(qreal));
  map_scale_data_buffer.append(reinterpret_cast<char*>(&lon),sizeof(qreal));
  map_scale_data_buffer.append(reinterpret_cast<char*>(&zoom),sizeof(int));

  QByteArray complete_map_data_buffer = map_lines_buffer + map_text_buffer + map_scale_data_buffer;

  QString filename = "./outgoing_map_markup_data/map_markup_data_" +
                     (QDateTime::currentDateTime().toString().remove(' ')) +
                     ".mmd";
  QFile map_markup_file(filename);
  if(map_markup_file.open(QIODevice::WriteOnly))
  {
    if(map_markup_file.write(complete_map_data_buffer) ==
            complete_map_data_buffer.size())
    {
        map_markup_file.close();
        QString command = "bzip2";
        QStringList args;
        args << "-z" << filename;
        QProcess process;
        process.start(command,args);
        if(!process.waitForFinished())
        {
            process.kill();
            qDebug() << "killed process "
                     << process.program();
        }
    }
    else
    {
        qDebug() << "error writing to file " << filename;
    }
  }
  else
  {
      qDebug() << "unable to open file";
  }

}


void map_markup_post::process_map_markup_data()
{
    QDir directory;
    directory.setFilter(QDir::Files);
    directory.setPath(QString("./incoming_map_markup_data"));
    directory.setSorting(QDir::Time);
    QStringList name_filter;
    name_filter << "*.bz2";
    directory.setNameFilters(name_filter);
    QStringList files =
            directory.entryList(QDir::Files,QDir::Time);

    if(files.count())
    {
        emit log_data("incoming map markup");
    }

    for(auto file : files)
    {
        QString filename(QString("./incoming_map_markup_data/")+file);

        QString command = "bzip2";
        QStringList args;
        args << "-d" << filename;
        QProcess process;
        process.start(command,args);
        if(!process.waitForFinished())
        {
            qDebug() << "killing process "
                     << process.program();
            process.kill();
        }
        else
        {
            filename = filename.remove(".bz2");

            QFile map_markup_file(filename);
            if(map_markup_file.open(QIODevice::ReadOnly))
            {
                QByteArray complete_map_data_buffer =
                        map_markup_file.readAll();

                if(complete_map_data_buffer.size())
                {
                    map_markup_file.close();
                    QDataStream data_stream(complete_map_data_buffer);

                    int red;
                    int green;
                    int blue;
                    char int_bytes[sizeof(int)];

                    unsigned int myPenWidth;
                    char unsigned_int_bytes[sizeof(unsigned int)];

                    int x1;
                    int x2;
                    int y1;
                    int y2;

                    while(!data_stream.atEnd())
                    {
                        data_stream.readRawData(int_bytes,sizeof(int_bytes));
                        int number_of_lines =
                                *reinterpret_cast<int*>(int_bytes);

                        for(int num_lines=0;num_lines<number_of_lines;
                            ++num_lines)
                        {
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            red =  *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            green = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            blue = *reinterpret_cast<int*>(int_bytes);

                            data_stream.readRawData(unsigned_int_bytes,
                                                    sizeof(unsigned_int_bytes));
                            myPenWidth = *reinterpret_cast<unsigned int*>
                                    (unsigned_int_bytes);

                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            x1 =  *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            x2 = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            y1 = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            y2 = *reinterpret_cast<int*>(int_bytes);

                            QColor color(red,green,blue);
                            QLine line(x1,y1,x2,y2);

                            scribble_manager::line_data
                                    map_line(myPenWidth,color,line);

                            line_list.push_back(map_line);
                        }

                        data_stream.readRawData(int_bytes,sizeof(int_bytes));
                        int num_text_data_items =
                                *reinterpret_cast<int*>(int_bytes);

                        data_stream.readRawData(int_bytes,sizeof(int_bytes));
                        int total_size_text_data_size =
                                *reinterpret_cast<int*>(int_bytes);

                        int text_size;
                        QString text;
                        QString font_family;
                        int rx,ry,x,y;

                        for(int num_text_items=0;num_text_items<
                            num_text_data_items;++num_text_items)
                        {
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            int this_text_item_size = *reinterpret_cast<int*>(int_bytes);

                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            text_size = *reinterpret_cast<int*>(int_bytes);

                            QByteArray text_bytes;
                            text_bytes.resize(text_size);
                            data_stream.readRawData(text_bytes.data(),text_size);
                            text = text_bytes.trimmed();


                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            rx = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            ry = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            x = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            y = *reinterpret_cast<int*>(int_bytes);

                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            red = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            green = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));
                            blue = *reinterpret_cast<int*>(int_bytes);
                            data_stream.readRawData(int_bytes,sizeof(int_bytes));

                            text_bytes.clear();
                            text_size = *reinterpret_cast<int*>(int_bytes);
                            text_bytes.resize(text_size);
                            data_stream.readRawData(text_bytes.data(),text_size);
                            font_family = text_bytes.trimmed();

                            data_stream.readRawData(unsigned_int_bytes,
                                                    sizeof(unsigned_int_bytes));
                            myPenWidth = *reinterpret_cast<unsigned int*>
                                    (unsigned_int_bytes);

                            QPoint point;
                            point.setX(x);
                            point.setX(y);

                            scribble_manager::text_data
                                    map_text(text,
                                             point,
                                             myPenWidth,
                                             QColor(red,green,blue),
                                             QFont(font_family));

                            text_list.push_back(map_text);

                        }

                        char qreal_bytes[sizeof(qreal)];
                        data_stream.readRawData(qreal_bytes,
                                                sizeof(qreal));
                        lat = *reinterpret_cast<qreal*>(qreal_bytes);

                        data_stream.readRawData(qreal_bytes,
                                                sizeof(qreal));
                        lon = *reinterpret_cast<qreal*>(qreal_bytes);

                        data_stream.readRawData(int_bytes,
                                                sizeof(int));
                        map_zoom = *reinterpret_cast<int*>(int_bytes);
                    }
                }
                else
                {
                    qDebug() << "no data in buffer after read from "
                             << map_markup_file.fileName();
                }
            }
            else
            {
                qDebug() << "error opeining file "
                         << map_markup_file.fileName();
            }
        }
    }
}

QList<scribble_manager::line_data>& map_markup_post::lines_map_data()
{
   return line_list;
}

QList<scribble_manager::text_data>& map_markup_post::text_map_data()
{
   return text_list;
}

