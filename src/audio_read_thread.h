#ifndef AUDIO_READ_THREAD_H
#define AUDIO_READ_THREAD_H

#include <memory>

#include <QThread>

class QProcess;

class audio_read_thread : public QThread
{
    Q_OBJECT
public:
    audio_read_thread(unsigned int, QObject *parent);
    virtual ~audio_read_thread();

    virtual void run();
    void set_should_stop_running(bool val);

    QProcess* get_audio_process();
signals:
   void new_buffer_data(char* data, qint64 maxLen);

public slots:

private:
    bool should_stop_running;
};

#endif // AUDIO_READ_THREAD_H
