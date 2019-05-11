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
    Q_OBJECT
public:
    audio_file_player_thread(audio_buffer_device *abd, QObject *parent);
    virtual ~audio_file_player_thread();
    bool is_completed() { return (isRunning() == false); }
    virtual void run();

signals:
   void new_buffer_data(char* data, qint64 maxLen);

private:
    QDir directory;
    QFile file;
    audio_buffer_device* audio_device;
    std::shared_ptr<QAudioOutput> audio_output;
};

#endif // AUDIO_FILE_PLAYER_THREAD_H
