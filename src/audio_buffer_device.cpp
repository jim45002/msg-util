
#include <QDebug>
#include <QDir>
#include <QByteArray>
#include <QDateTime>

#include <qwt_symbol.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "audio_read_thread.h"
#include "audio_buffer_device.h"

namespace {
const unsigned int length       = 1;
const unsigned int freq_per_sec = 8000;
const unsigned int sample_size  = 16;
const unsigned int num_channels = 1;
}

const unsigned long buffer_length =
        ( sample_size * freq_per_sec * num_channels * length ) / 8;


audio_buffer_device::audio_buffer_device(QwtPlot *plot,
                                         QDoubleSpinBox* outgoing_spinbox,
                                         QDoubleSpinBox* incoming_spinbox,                                                                                  
                                         QObject* parent)
    : QIODevice(parent),
      plot_widget(plot),
      in_spinbox(incoming_spinbox),
      out_spinbox(outgoing_spinbox),     
      data_size(128)
{
   audio_reader = std::make_shared<audio_read_thread>(
               buffer_length,nullptr);

   connect(audio_reader.get(),
           SIGNAL(new_buffer_data(char*,qint64)),
           this,
           SLOT(new_buffer_data(char*,qint64)));
}

audio_buffer_device::~audio_buffer_device()
{

}

bool audio_buffer_device::open(QIODevice::OpenMode mode)
{
  setOpenMode(mode);
  return true;
}

void audio_buffer_device::close()
{
  QIODevice::close();
}

void audio_buffer_device::start_audio_read()
{
  audio_reader->start();
}

void audio_buffer_device::new_buffer_data(char *data, qint64 maxLen)
{
   writeData(data,maxLen);
}

qint64 audio_buffer_device::readData(char *data, qint64 maxSize)
{
   double x[data_size],y[data_size];
   if(maxSize>data_size)
       maxSize=data_size;
   memset(x,'\0',sizeof(x));
   memset(y,'\0',sizeof(y));
   for(int i=0;i<maxSize;++i)
   {
       x[i] = i;
       y[i] = abs(*data);
       ++data;
   }
   curve.setRawSamples(x,y,maxSize);
   curve.setPen( QPen(Qt::black,1));
   curve.setRenderHint(QwtPlotItem::RenderAntialiased,true);
   curve.attach(plot_widget);
   plot_widget->replot();
   audio_data.clear();
   return maxSize;
}

qint64 audio_buffer_device::writeData(const char *data, qint64 maxSize)
{

//    double x[data_size],y[data_size];
//    if(maxSize>data_size)
//        maxSize=data_size;
//    memset(x,'\0',sizeof(x));
//    memset(y,'\0',sizeof(y));
//    for(int i=0;i<maxSize;++i)
//    {
//        x[i] = i;
//        y[i] = abs(*data);
//        ++data;
//    }
//    curve.setRawSamples(x,y,maxSize);
//    curve.setPen( QPen(Qt::black,1));
//    curve.setRenderHint(QwtPlotItem::RenderAntialiased,true);
//    curve.attach(plot_widget);
//    plot_widget->replot();
//    audio_data.clear();
    return maxSize;
}


qint64 audio_buffer_device::readLineData(char *, qint64 )
{
    return 0;
}

void audio_buffer_device::stop_audio_write()
{
    audio_reader->set_should_stop_running(true);
    audio_reader->wait();
}

void audio_buffer_device::save_voice_message()
{    

}


