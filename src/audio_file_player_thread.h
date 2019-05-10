#ifndef AUDIO_FILE_PLAYER_THREAD_H
#define AUDIO_FILE_PLAYER_THREAD_H

#include <memory>

#include <QThread>
#include <QFileInfoList>
#include <QFileInfo>
#include <QFile>
#include <QDir>

class audio_buffer_device;
class QAudioOutput;

class audio_file_player_thread : public QThread
{
public:
    audio_file_player_thread(audio_buffer_device *abd, QObject *parent);
    virtual ~audio_file_player_thread();
    bool is_completed() { return (isRunning() == false); }
    virtual void run();

private:
    QDir directory;
    QFile file;
    audio_buffer_device* audio_device;
    std::shared_ptr<QAudioOutput> audio_output;
};

#endif // AUDIO_FILE_PLAYER_THREAD_H
