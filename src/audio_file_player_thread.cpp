
#include <thread>
#include <chrono>

#include <QDebug>
#include <QProcess>
#include <QFile>

#include "audio_buffer_device.h"
#include "audio_file_player_thread.h"

audio_file_player_thread::audio_file_player_thread(audio_buffer_device* abd,
                                                   QObject* parent)
    : QThread(parent),
      audio_device(abd)
{

}

audio_file_player_thread::~audio_file_player_thread()
{

}

void audio_file_player_thread::run()
{ 
    QDir directory;
    directory.setFilter(QDir::Files);
    directory.setPath(QString("./incoming_voice_data"));
    directory.setSorting(QDir::Time);
    QStringList name_filter;
    name_filter << "*.voc";
    directory.setNameFilters(name_filter);
    QStringList files =
            directory.entryList(QDir::Files,QDir::Time);

    for(auto file : files)
    {
        QString commamd = "/usr/bin/aplay";
        QStringList args;
        args << "-f"
             << "S16_LE"
             << QString("./incoming_voice_data/")+file;
        QProcess audio_process;
        audio_process.start(commamd,args);

        QFile infile(args[2]);
        QByteArray buff;
        if(infile.open(QIODevice::ReadOnly))
        while(!infile.atEnd())
        {
            buff += infile.read(128-buff.length());
            if(buff.length()<128)
                continue;
            emit new_buffer_data(buff.data(),buff.length());
            buff.clear();
        }
        if(!audio_process.waitForFinished(3000))
        {
            audio_process.kill();
        }
        QFile::remove(QString("./incoming_voice_data/")+file);
    }
}
