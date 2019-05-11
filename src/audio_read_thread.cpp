
#include <QStringList>
#include <QProcess>
#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "audio_read_thread.h"

audio_read_thread::audio_read_thread(unsigned int, QObject* parent)
    : QThread(parent)
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

    QProcess audio_process;
    audio_process.start(commamd,args);
    audio_process.waitForStarted();
    audio_process.waitForFinished(500);

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray buff;
        while(1)
        {
            if(should_stop_running == true)
            {
                audio_process.terminate();
                if(!audio_process.waitForFinished())
                {
                    audio_process.kill();
                }
                break;
            }
            buff += file.read(128-buff.length());
            if(buff.length()<128)
                continue;
            emit new_buffer_data(buff.data(),buff.length());
            buff.clear();
        }
    }
    else
    {
        qDebug() << "unable to open " << filename;
        while(audio_process.waitForFinished(500))
        {
            if(should_stop_running == true)
            {
                audio_process.terminate();
                if(!audio_process.waitForFinished())
                {
                    audio_process.kill();
                }
                break;
            }
        }
    }
}

void audio_read_thread::set_should_stop_running(bool val)
{
    should_stop_running = val;
}

QProcess *audio_read_thread::get_audio_process()
{
    return nullptr;
}
