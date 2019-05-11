
#include <QSizePolicy>
#include <QDateTime>
#include <QDir>
#include <QTimer>
#include <QFileDialog>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

#include "audio_file_player_thread.h"
#include "audio_buffer_device.h"
#include "data_receiver.h"
#include "map_widget_interface.h"
#include "map_widget_factory.h"
#include "data_transmitter.h"
#include "ui_messenger_dialog.h"
#include "messenger_dialog.h"


messenger_dialog::messenger_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messenger_dialog)
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

//    ui->incoming_plot_label->hide();
//    ui->outgoing_plot_label->hide();
//    ui->outgoing_plot_widget->hide();
//    ui->incoming_plot_widget->hide();

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

    connect(ui->enable_scribble_checkBox,
            SIGNAL(clicked(bool)),
            this,
            SLOT(enable_scribble_clicked(bool)));

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
    auto l = new QHBoxLayout;
    ui->map_widget->setLayout(l);
    l->addWidget(mwfi->map_dispaly_widget());

    data_recv_inter = std::make_shared<data_receiver>(nullptr);

    audio_buffer =
            std::make_shared<audio_buffer_device>(outgoing_plot,
                                                  ui->outgoing_doubleSpinBox,
                                                  ui->incoming_doubleSpinBox,
                                                  nullptr);
    audio_buffer->open(QIODevice::WriteOnly);

    incoming_audio_buffer =
    std::make_shared<audio_buffer_device>(incoming_plot,
                                          ui->outgoing_doubleSpinBox,
                                          ui->incoming_doubleSpinBox,                                                                                   
                                          nullptr);
    connect(aud_file_player_thread.get(),
            SIGNAL(new_buffer_data(char*,qint64)),
            incoming_audio_buffer.get(),
            SLOT(new_buffer_data(char*,qint64)));

    incoming_audio_buffer->open(QIODevice::ReadOnly);

    QTimer* timer = new QTimer(this);
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


void messenger_dialog::transmit_sribble_clicked(bool)
{
    qDebug() << "scribble transmit clicked";
    auto items = ui->connections_listwidget->selectedItems();
    if(items.count()==1)
    {
      data_transmitter* dt = new data_transmitter(items[0]->text());
      data_trans_list.push_back(dt);
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
            QByteArray line = connections_file.readLine(256).trimmed();
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

    ui->statusbar_label->clear();

    outgoing_text_check();
    incoming_voice_check();
    outgoing_voice_check();
    post_text_data();
    aud_file_player_thread->start();
}

void messenger_dialog::voice_transmit_button_pressed()
{
   qDebug() << "voice_transmit pressed";
   audio_buffer->start_audio_read();
}

void messenger_dialog::voice_transmit_button_released()
{
   qDebug() << "voice_transmit released";
   clear_outgoing_plot();
   audio_buffer->stop_audio_write();
   auto items = ui->connections_listwidget->selectedItems();
   if(items.count()==1)
   {
     data_transmitter* dt = new data_transmitter(items[0]->text());
     data_trans_list.push_back(dt);
     ui->statusbar_label->setText("transmitting voice message");
   }
   else
   {     
     qDebug() << "unable to determine receiver address";
      ui->statusbar_label->setText
              ("unable to determine receiver address - select a connection");
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
     data_transmitter* dt = new
             data_transmitter(items[0]->text().trimmed());
     data_trans_list.push_back(dt);
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
