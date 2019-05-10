
#include <QStringList>
#include <QProcess>
#include <QDateTime>

#include "audio_read_thread.h"

audio_read_thread::audio_read_thread(unsigned int buffer_size, QObject* parent)
    : QThread(parent),
      buffer_length(buffer_size)
{

}

audio_read_thread::~audio_read_thread()
{

}

void audio_read_thread::run()
{
  should_stop_running = false;

  QString filename =
          QString("./outgoing_voice_data/voice_data_") +
          QDateTime::currentDateTime().toString().remove(' ') +
          QString(".voc");

  QString commamd = "/usr/bin/arecord";
  QStringList args;
  args << "-f" << "S16_LE" << filename;

  QProcess audio_process(this);
  audio_process.start(commamd,args);
  audio_process.waitForFinished(-1);
}

void audio_read_thread::set_should_stop_running(bool val)
{
    should_stop_running = val;
    terminate();
 }

QProcess *audio_read_thread::get_audio_process()
{
    return nullptr;
}
