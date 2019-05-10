
#include <thread>
#include <chrono>

#include <QDebug>
#include <QProcess>

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
        args << "-f" << "S16_LE" <<
                QString("./incoming_voice_data/")+file;
        QProcess audio_process(this);
        audio_process.start(commamd,args);
        audio_process.waitForFinished(-1);
        QFile::remove(QString("./incoming_voice_data/")+file);
    }
}
