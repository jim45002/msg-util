
#include <QSizePolicy>
#include <QDateTime>
#include <QDir>
#include <QTimer>
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

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#include "camera_device_interface.h"
#include "camera_widget_interface.h"
#include "camera_widget_factory.h"
#include "image_data_types.h"
#include "image_data_packet.h"
#include "data_transmitter_factory_interface.h"
#include "scribble_manager.h"
#include "map_paint_layer.h"
#include "audio_file_player_thread.h"
#include "audio_buffer_device.h"
#include "data_receiver_interface.h"
#include "map_widget_interface.h"
#include "map_widget_factory.h"
#include "ui_messenger_dialog.h"
#include "messenger_dialog.h"

messenger_dialog::messenger_dialog(
        std::shared_ptr<data_transmitter_factory_interface> dtfi,
        data_receiver_interface* dri,
        QWidget *parent
        )
    : QDialog(parent),
      ui(new Ui::messenger_dialog),
      data_trans_f_inter(dtfi),
      data_recv_inter(dri)

{
    ui->setupUi(this);

    aud_file_player_thread =
            std::make_shared<audio_file_player_thread>
            (nullptr,nullptr);

    QDir dir;
    dir.mkdir(QString("./outgoing_voice_data"));
    dir.mkdir(QString("./outgoing_text_data"));
    dir.mkdir(QString("./incoming_voice_data"));
    dir.mkdir(QString("./incoming_text_data"));
    dir.mkdir(QString("./incoming_map_markup_data"));
    dir.mkdir(QString("./outgoing_map_markup_data"));
    dir.mkdir(QString("./incoming_image_data"));
    dir.mkdir(QString("./outgoing_image_data"));
    dir.mkdir(QString("./incoming_video_data"));
    dir.mkdir(QString("./outgoing_video_data"));
    dir.mkdir(QString("./outgoing_av_data"));
    dir.mkdir(QString("./incoming_av_data"));

    dir.mkdir(QString("./outgoing_verified_voice_data"));
    dir.mkdir(QString("./outgoing_verified_text_data"));
    dir.mkdir(QString("./outgoing_verified_map_markup_data"));
    dir.mkdir(QString("./outgoing_verified_image_data"));
    dir.mkdir(QString("./outgoing_verified_video_data"));
    dir.mkdir(QString("./outgoing_verified_av_data"));

    dir.mkdir(QString("./unverified_voice_data"));
    dir.mkdir(QString("./unverified_text_data"));
    dir.mkdir(QString("./unverified_map_markup_data"));
    dir.mkdir(QString("./unverified_image_data"));
    dir.mkdir(QString("./unverified_video_data"));
    dir.mkdir(QString("./unverified_av_data"));

    dir.mkdir(QString("./send_error_voice_data"));
    dir.mkdir(QString("./send_error_text_data"));
    dir.mkdir(QString("./send_error_map_markup_data"));
    dir.mkdir(QString("./send_error_image_data"));
    dir.mkdir(QString("./send_error_video_data"));
    dir.mkdir(QString("./send_error_av_data"));

    dir.mkdir(QString("./recv_error_voice_data"));
    dir.mkdir(QString("./recv_error_text_data"));
    dir.mkdir(QString("./recv_error_map_markup_data"));
    dir.mkdir(QString("./recv_error_image_data"));
    dir.mkdir(QString("./recv_error_video_data"));
    dir.mkdir(QString("./recv_error_av_data"));

    connect(ui->voice_transmit_pushButton,
            SIGNAL(pressed()),
            this,
            SLOT(voice_transmit_button_pressed()));

    connect(ui->voice_transmit_pushButton,
            SIGNAL(released()),
            this,
            SLOT(voice_transmit_button_released()));

    connect(ui->text_transmit_pushButton,
            SIGNAL(pressed()),
            this,
            SLOT(text_transmit_button_pressed()));

    connect(ui->text_transmit_pushButton,
            SIGNAL(released()),
            this,
            SLOT(text_transmit_button_released()));

    connect(ui->video_transmit_pushButton,
            SIGNAL(pressed()),
            this,
            SLOT(video_transmit_button_pressed()));

    connect(ui->video_transmit_pushButton,
            SIGNAL(released()),
            this,
            SLOT(video_transmit_button_released()));


    connect(ui->enable_scribble_checkBox,
            SIGNAL(clicked(bool)),
            this,
            SLOT(enable_scribble_clicked(bool)));

    connect(ui->next_image_pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(next_image_pushButton_clicked(bool)));

    connect(ui->add_image_pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(add_image_pushButton_clicked(bool)));

    connect(ui->image_transmit_pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(image_transmit_button_clicked(bool)));

    connect(ui->image_remove_pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(image_remove_button_clicked(bool)));

    connect(ui->image_clear_pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(image_clear_button_clicked(bool)));

    connect(ui->video_on_radioButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(video_on_button_clicked(bool)));

    connect(ui->video_off_radioButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(video_off_button_clicked(bool)));

    connect(ui->stream1_start__pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stream1_start_push_button_clicked(bool)));

    connect(ui->stream1_stop_pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stream1_stop_push_button_clicked(bool)));

    connect(ui->ghz_radioButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(radio_button_clicked(bool)));

    connect(ui->mhz_radioButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(radio_button_clicked(bool)));

    connect(ui->khz_radioButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(radio_button_clicked(bool)));

    connect(ui->hz_radioButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(radio_button_clicked(bool)));

    connect(ui->freq_spinBox,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(freq_slider_moved(int)));

    ui->freq_spinBox->setSingleStep(1000000);
    ui->freq_spinBox->setMaximum(2000000000);
    ui->freq_spinBox->setMinimum(300000000);
    ui->freq_spinBox->setFocusPolicy(Qt::StrongFocus);

    cdi = camera_widget_factory::
            create(cdi.get(),
                   ui->outgoing_video_graphicsView);

    csi = camera_widget_factory::
            create(csi.get(),
                   camera_widget_factory::remote,
                   ui->stream1_graphicsView);


    incoming_plot = create_plot_widget(ui->incoming_plot_widget);
    QSizePolicy incoming_sizePolicy(QSizePolicy::Preferred,
                                    QSizePolicy::Preferred);
    incoming_plot->setSizePolicy(incoming_sizePolicy);
    incoming_plot->setCanvasBackground( Qt::black );

    outgoing_plot = create_plot_widget(ui->outgoing_plot_widget);
    QSizePolicy outgoing_sizePolicy(QSizePolicy::Preferred,
                                    QSizePolicy::Preferred);
    outgoing_plot->setSizePolicy(outgoing_sizePolicy);
    outgoing_plot->setCanvasBackground( Qt::white );

    ui->incoming_plot_widget->setSizePolicy(outgoing_sizePolicy);
    ui->outgoing_plot_widget->setSizePolicy(outgoing_sizePolicy);

    mwfi = map_widget_factory::create(this);
    mwfi->map_enable_scibble(false);
    auto l = new QHBoxLayout;
    ui->map_widget->setLayout(l);
    l->addWidget(mwfi->map_dispaly_widget());

    streams_mwfi = map_widget_factory::create(this);
    streams_mwfi->map_enable_scibble(false);
    auto l2 = new QHBoxLayout;
    ui->streams_map_widget->setLayout(l2);
    l2->addWidget(streams_mwfi->map_dispaly_widget());

    audio_buffer =
            std::make_shared<audio_buffer_device>(outgoing_plot,
                                                  ui->squelch_doubleSpinBox,
                                                  ui->squelch_doubleSpinBox,
                                                  nullptr);
    audio_buffer->open(QIODevice::WriteOnly);

    incoming_audio_buffer =
    std::make_shared<audio_buffer_device>(incoming_plot,
                                          ui->squelch_doubleSpinBox,
                                          ui->squelch_doubleSpinBox,
                                          nullptr);
    connect(aud_file_player_thread.get(),
            SIGNAL(new_buffer_data(char*,qint64)),
            incoming_audio_buffer.get(),
            SLOT(new_buffer_data(char*,qint64)));

    incoming_audio_buffer->open(QIODevice::ReadOnly);

    timer = new QTimer(this);
    timer->setInterval(10000);
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_timedout()));
    timer->start();

    connect(ui->insert_connections_pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(insert_connections_button(bool)));

    connect(ui->transmit_scribble_pushButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(transmit_sribble_clicked(bool)));

    clear_outgoing_plot();
    clear_incoming_plot();
}

messenger_dialog::~messenger_dialog()
{
    delete ui;
}

void messenger_dialog::radio_button_clicked(bool)
{
    if(ui->hz_radioButton->isChecked())
    {
       ui->freq_spinBox->setSingleStep(1);
    }
    else
    if(ui->khz_radioButton->isChecked())
    {
        ui->freq_spinBox->setSingleStep(1000);
    }
    else
    if(ui->mhz_radioButton->isChecked())
    {
        ui->freq_spinBox->setSingleStep(1000000);
    }
    else
    if(ui->ghz_radioButton->isChecked())
    {
        ui->freq_spinBox->setSingleStep(1000000000);
    }
}

void messenger_dialog::freq_slider_moved(int)
{
  if(ui->freq_spinBox->value()<1000)
      ui->freq_spinBox->setSuffix("Hz");
  else
  if(ui->freq_spinBox->value()>=1000 && ui->freq_spinBox->value()<=999999)
      ui->freq_spinBox->setSuffix("khz");
  else
  if(ui->freq_spinBox->value()>999999 && ui->freq_spinBox->value()<1000000000)
      ui->freq_spinBox->setSuffix("Mhz");
  else
  if(ui->freq_spinBox->value()>=1000000000)
      ui->freq_spinBox->setSuffix("Ghz");
}

void messenger_dialog::stream1_start_push_button_clicked(bool)
{
    QUrl url(QString("http://localhost:8000/theora.ogg"));
    csi->setMedia(url);
    csi->start();
}

void messenger_dialog::stream1_stop_push_button_clicked(bool)
{
    csi->stop();
}

void messenger_dialog::video_on_button_clicked(bool)
{
    cdi->start();
}

void messenger_dialog::video_off_button_clicked(bool)
{
    cdi->stop();
}

void messenger_dialog::image_transmit_button_clicked(bool)
{
    qDebug() << "image transmit pressed";
    timer->stop();
    auto items = ui->connections_listwidget->selectedItems();
    if(items.count()==1)
    {
       data_transmitter_interface* dti =
              data_trans_f_inter->create(items[0]->text());
       data_trans_list.push_back(dti);
       ui->statusbar_label->setText("transmitting image");
    }
    else
    {
       qDebug() << "unable to determine receiver address";
       ui->statusbar_label->setText
               ("unable to determine receiver address - select a connection");
    }
    timer->start();
}

void messenger_dialog::add_image_pushButton_clicked(bool)
{
    QString filename
            = QFileDialog::getOpenFileName(
               this,
               "Open Image",
               ".",
               "Images (*.png *.gif *.jpg *.jpeg)"
               );

    QPixmap* pixmap = new QPixmap;

    if(pixmap->load(filename))
    {
       QGraphicsScene* graphics_scene =
               new QGraphicsScene(nullptr);

       graphics_scene->addPixmap(*pixmap);
       ui->outgoing_image_graphics_view->
               setScene(graphics_scene);
       ui->outgoing_image_graphics_view->show();
       save_image_data(filename);
    }
    else
    {
       ui->statusbar_label->setText(
                   QString("unable to open selected image file")
                   );
    }
}

void messenger_dialog::image_clear_button_clicked(bool)
{
    qDebug() << "clear image button clicked";
    ui->outgoing_image_graphics_view->setScene(nullptr);
    ui->outgoing_image_graphics_view->show();
}

void messenger_dialog::image_remove_button_clicked(bool)
{
   qDebug() << "remove image button clicked";
   if(current_graphics_scene_index<graphics_scene_list.count())
   {
       ui->incoming_image_graphics_view->setScene(nullptr);
       ui->incoming_image_graphics_view->show();
       graphics_scene_list.removeAt(current_graphics_scene_index);
   }
}

void messenger_dialog::next_image_pushButton_clicked(bool)
{
    qDebug() << "next image button clicked ";
    static unsigned short int index=0;
    if(index < graphics_scene_list.count())
    {
       qDebug() << "adding scene to image view";
       ui->incoming_image_graphics_view->
              setScene(graphics_scene_list[index]);
       ui->incoming_image_graphics_view->show();

       QString text = "Incoming Image #" +
               QString::number(index);
       ui->incoming_image_label->setText(text);
       current_graphics_scene_index=index;
       ++index;
    }
    else
    {
       qDebug() << "setting index back to zero";
       index=0;
    }
}

void messenger_dialog::transmit_sribble_clicked(bool)
{
    save_map_markup();

    auto items = ui->connections_listwidget->selectedItems();
    if(items.count()==1)
    {
      data_transmitter_interface* dti =
              data_trans_f_inter->create(items[0]->text());
      data_trans_list.push_back(dti);
      ui->statusbar_label->setText("transmitting scribble");
    }
    else
    {
      qDebug() << "unable to determine receiver address";
       ui->statusbar_label->setText
               ("unable to determine receiver address - select a connection");
    }
}

void messenger_dialog::save_map_markup()
{
  auto paint_layer = mwfi->get_map_widget_paint_layer();
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

  QByteArray complete_map_data_buffer = map_lines_buffer + map_text_buffer;

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

///////////////////
void messenger_dialog::save_image_data(QString selected_image_file)
{
  QFile image_data_file(selected_image_file);
  if(image_data_file.open(QIODevice::ReadOnly))
  {
    QByteArray data_buffer;
    data_buffer = image_data_file.readAll();
    if(data_buffer.size() == image_data_file.size())
    {
        image_data_file.close();

        image_data_type idt;
        if(selected_image_file.indexOf(".jpg")  > -1  ||
           selected_image_file.indexOf(".jpeg") > -1)
        {
           idt = t_jpg;
        }
        else
        if(selected_image_file.indexOf(".png") > -1)
        {
           idt = t_png;
        }
        else
        if(selected_image_file.indexOf(".gif") > -1)
        {
            idt = t_gif;
        }
        else
        {
            qDebug() << "unable to determine image type - not creating image";
            return;
        }

        qDebug() << "save image of type " << idt << "sizeof idt "
                 << sizeof(idt);

        QByteArray packet;
        packet.append(reinterpret_cast<char*>(&idt),sizeof(int));
        int size = data_buffer.size();
        packet.append(reinterpret_cast<char*>(&size),sizeof(int));
        packet.append(data_buffer.data(),size);

        QString outgoing_filename = "./outgoing_image_data/image_data_" +
                       (QDateTime::currentDateTime().toString().remove(' '));

        QFile outgoing_file(outgoing_filename);
        if(outgoing_file.open(QIODevice::WriteOnly))
        {
           if(outgoing_file.write(packet) == packet.size())
           {
              outgoing_file.close();
              QString command = "bzip2";
              QStringList args;
              args << "-z" << outgoing_filename;
              QProcess process;
              process.start(command,args);
              if(!process.waitForFinished())
              {
                 process.kill();
                 qDebug() << "killed compression process "
                          << process.program();
              }
              else
              {
                 qDebug() << "created outgoing file"
                          << outgoing_file.fileName();
              }
           }
           else
           {
              qDebug() << "error writing to file " << outgoing_file.fileName();
           }
        }
        else
        {
            qDebug() << "unable to open file " << outgoing_file.fileName();
        }
    }
    else
    {
        qDebug() << "error reading to file " << image_data_file.fileName();
    }
  }
  else
  {
      qDebug() << "unable to open file " << image_data_file.fileName();
  }

}


void messenger_dialog::insert_connections_button(bool)
{
    QFileDialog fileDialog(this);
    QString filename = fileDialog.getOpenFileName();
    QFile connections_file(filename);
    if(connections_file.open(QIODevice::ReadOnly))
    {
        ui->connections_listwidget->clear();
        while(!connections_file.atEnd())
        {
            QByteArray line =
                    connections_file.readLine(256).trimmed();
            if(line.length())
               ui->connections_listwidget->addItem(QString(line));
        }
    }
}

void messenger_dialog::enable_scribble_clicked(bool)
{
    if(ui->enable_scribble_checkBox->isChecked())
    {
        mwfi->map_enable_scibble(true);
    }
    else
    {
        mwfi->map_enable_scibble(false);
    }
}

void messenger_dialog::timer_timedout()
{
    auto post_map_markup_data = [this]() {

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
            ui->statusbar_label->setText("incoming map markup");
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

                        QList<scribble_manager::line_data> line_list;
                        QList<scribble_manager::text_data> text_list;

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


                            mwfi->get_map_widget_paint_layer()->
                                    get_scribble_manager()->
                                    set_lines_list_data(line_list);



                            mwfi->get_map_widget_paint_layer()->
                                    get_scribble_manager()->
                                    set_text_list_data(text_list);
                        }
                        mwfi->get_map_widget_paint_layer()->repaint();
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
    };

    auto process_image_data = [this] ()
    {
        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./incoming_image_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.bz2";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        if(files.count())
        {
            ui->statusbar_label->setText("incoming image data");
            ui->next_image_pushButton->setEnabled(true);
        }
        else
        {

        }

        for(auto file : files)
        {
            QString filename(QString("./incoming_image_data/")+file);

            QString command = "bzip2";
            QStringList args;
            args << "-d" << filename;
            QProcess process;
            process.start(command,args);
            if(!process.waitForFinished())
            {
                qDebug() << "killing decompression process "
                         << process.program();
                process.kill();
            }
            else
            {
                QFile::remove(filename);
                filename = filename.remove(".bz2");
                QFile image_data_file(filename);
                if(image_data_file.open(QIODevice::ReadOnly))
                {
                    QByteArray complete_image_data_buffer =
                            image_data_file.readAll();

                    if(complete_image_data_buffer.size() ==
                            image_data_file.size())
                    {
                        image_data_file.close();

                        QDataStream data_stream(complete_image_data_buffer);

                        QByteArray byte_data;
                        byte_data.resize(sizeof(int));
                        data_stream.readRawData(byte_data.data(),
                                                sizeof(int));
                        image_data_type image_type =
                                (image_data_type) *byte_data.data();

                        qDebug() << "image type is " << image_type;

                        byte_data.resize(sizeof(int));
                        data_stream.readRawData(byte_data.data(),sizeof(int));
                        int size = *reinterpret_cast<int*>(byte_data.data());

                        byte_data.resize(size);
                        data_stream.readRawData(byte_data.data(),size);
                            bool valid_image_type = true;
                            switch (image_type)
                            {
                              case t_png:
                              {
                                 QString file(filename);
                                 filename += ".png";
                              }
                                break;

                              case t_jpg:
                              {
                                QString file(filename);
                                filename += ".jpg";
                              }
                                break;
                              case t_gif:
                              {
                                QString file(filename);
                                filename += ".gif";
                              }
                                break;
                              default:
                              {
                                 valid_image_type = false;
                                 qDebug() << "invalid image type";
                              }
                            }

                            if(valid_image_type)
                            {
                              qDebug() << "new image filename is " << filename;
                              QFile final_image_file(filename);
                              if(final_image_file.open(QIODevice::WriteOnly))
                              {
                                 if(final_image_file.write(byte_data) ==
                                        byte_data.size())
                                 {
                                   final_image_file.close();

                                   QPixmap* pixmap = new QPixmap;
                                   QGraphicsScene* graphics_scene =
                                       new QGraphicsScene(nullptr);

                                   if(pixmap->load(filename))
                                   {
                                     qDebug() << "pushing scene on list";
                                     graphics_scene->addPixmap(*pixmap);
                                     graphics_scene_list.
                                             push_back(graphics_scene);
                                   }
                                   else
                                   {
                                      ui->statusbar_label->setText(
                                            QString("unable to open image file")
                                             );
                                   }
                               }
                               else
                               {
                                  qDebug() << "unable to write final image file"
                                           << final_image_file.fileName();
                               }
                            }
                            else
                            {
                               qDebug() << "unable to open final image file"
                                        << final_image_file.fileName();
                            }
                          }
                          else
                          {
                            qDebug() << "not creating file - invalid image type"
                                     << " for " << filename;
                          }
                       }
                       else
                       {
                         qDebug() << "buffer size error on image data ";
                       }
                   }
                   else
                   {
                       qDebug() << "unable to open image file"
                              << image_data_file.fileName();
                   }
               }
          }
      };

    auto post_text_data = [this]() {
        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./incoming_text_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.txt";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        if(files.count())
        {
            ui->statusbar_label->setText("incoming text message");
        }
        for(auto file : files)
        {
            QFile f(QString("./incoming_text_data/")+file);
            if(f.open(QIODevice::ReadOnly))
            {
                QByteArray bytes = f.readAll();
                ui->incoming_textEdit->append(QString(bytes));
                f.close();
                f.remove();
                ui->outgoing_textEdit->clear();
            }
            else
            {
                qDebug() << "unable to open file " << f.fileName();
            }
        }
    };

    auto outgoing_text_check = [this] {

        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./outgoing_text_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.txt";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        if(files.count())
        {
            if(files.count())
            {
                ui->statusbar_label->setText(
                            "pending text message transmissions"
                            );
            }
            else
            {
                ui->statusbar_label->setText
                        ("no pending text message transmissions");
            }
        }
    };

    auto outgoing_voice_check = [this] {

        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./outgoing_voice_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.voc";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        if(files.count())
        {
            ui->statusbar_label->setText("voice transmissionss pending");
        }
        else
        {
            ui->statusbar_label->setText(" ");
            clear_outgoing_plot();
        }
    };

    auto incoming_voice_check = [this] {

        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./incoming_voice_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.voc";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        if(files.count())
        {
            ui->statusbar_label->setText("incoming voice message");
        }
        else
        {
            clear_incoming_plot();
            ui->statusbar_label->setText(" ");
        }
    };

    auto destroy_transmitters = [this] ()
    {
       int num_active=0;
       for(auto iter : data_trans_list)
       {
          if(iter->is_finished())
          {
              qDebug() << "destroying transmitter";
             // data_trans_f_inter->destroy(iter);
          }
          else
          {
              ++num_active;
          }
       }
       if(0==num_active)
       {
           data_trans_list.clear();
       }
    };

    destroy_transmitters();
    process_image_data();
    post_map_markup_data();
    outgoing_text_check();
    incoming_voice_check();
    outgoing_voice_check();
    post_text_data();
    aud_file_player_thread->start();
}

void messenger_dialog::voice_transmit_button_pressed()
{
   audio_buffer->start_audio_read();
}

void messenger_dialog::video_transmit_button_pressed()
{
   qDebug() << "video_transmit pressed";
   cdi->start_record(
               QUrl::fromLocalFile(QString("/tmp/outgoing_vid.ogg")
                                   ));
}

void messenger_dialog::video_transmit_button_released()
{
   qDebug() << "video_transmit released";
   cdi->stop_record();
   QString filename (
               "./outgoing_av_data/" +
               QDateTime::currentDateTime().toString().remove(' ') +
               ".ogg"
               );
   QFile::copy(QString("/tmp/outgoing_vid.ogg"),filename);
   QFile::remove(QString("/tmp/outgoing_vid.ogg"));
}

void messenger_dialog::voice_transmit_button_released()
{
   qDebug() << "voice_transmit released";
   clear_outgoing_plot();
   audio_buffer->stop_audio_write();
   auto items = ui->connections_listwidget->selectedItems();
   if(items.count()==1)
   {
     data_transmitter_interface* dti =
             data_trans_f_inter->create(items[0]->text());
     data_trans_list.push_back(dti);
     ui->statusbar_label->setText("transmitting voice message");
   }
   else
   {     
     qDebug() << "unable to determine receiver address";
      ui->statusbar_label->setText
              ("unable to determine receiver address - "
               "select a connection");
   }
}

void messenger_dialog::clear_outgoing_plot()
{
    char y[128];
    memset(y,0,sizeof(y));
    audio_buffer->writeData(y,sizeof(y));
}

void messenger_dialog::clear_incoming_plot()
{
    char y[128];
    memset(y,0,sizeof(y));
    incoming_audio_buffer->writeData(y,sizeof(y));
}

////////////////
void messenger_dialog::text_transmit_button_pressed()
{
   qDebug() << "text_transmit pressed";

}

void messenger_dialog::text_transmit_button_released()
{
   qDebug() << "text_transmit released";
   QString text = ui->outgoing_textEdit->toPlainText();
   QString filename = QString("./outgoing_text_data/text_data_") +
           QDateTime::currentDateTime().toString() + QString(".txt");
   QFile file(filename);
   if(file.open(QIODevice::WriteOnly))
   {
       if(file.write(text.toStdString().c_str()) == text.length())
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
   auto items = ui->connections_listwidget->selectedItems();
   if(items.count()==1)
   {
     data_transmitter_interface* dti =
             data_trans_f_inter->create(items[0]->text().trimmed());
     data_trans_list.push_back(dti);
     ui->statusbar_label->setText("transmitting text message");
   }
   else
   {
     qDebug() << "unable to determine receiver address";
     ui->statusbar_label->setText(
                 "unable to determine receiver address - select a contact"
                 );
   }
}

/////////////
QwtPlot* messenger_dialog::create_plot_widget(QWidget* parent)
{
    QwtPlot* plot = new QwtPlot(parent);
    plot->setAxisScale( QwtPlot::yLeft, -128,128 );
    plot->setAxisScale( QwtPlot::xBottom, 0.0, 128);

    auto layout = new QHBoxLayout;
    parent->setLayout(layout);
    layout->addWidget(plot);
    plot->show();

    return plot;

}
