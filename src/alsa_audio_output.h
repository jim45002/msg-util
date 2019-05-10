#ifndef ALSA_AUDIO_OUTPUT_H
#define ALSA_AUDIO_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#include <QDebug>
#include <QIODevice>

//////////////////////////////////////////////////
class alsa_audio_output : public QIODevice
{
    Q_OBJECT
public:
    alsa_audio_output(QObject* parent = nullptr);
    virtual ~alsa_audio_output();

    virtual bool open(QIODevice::OpenMode);
    virtual void close();
    virtual bool 	atEnd ()        const { return false; }
    virtual qint64 	bytesToWrite () const { return -1; }
    virtual bool 	canReadLine ()  const { return false; }
    virtual bool 	isSequential () const { return false; }

    virtual qint64 readData(char *, qint64 )
    {
        return -1;
    }
    virtual qint64 writeData(const char *, qint64 );

    virtual bool waitForReadyRead(int )
    {
        qDebug() << "ALSAAudioOutput::waitForReadyRead";
        return true;
    }
    virtual bool waitForBytesWritten(int)
    {
        qDebug() << "ALSAAudioOutput::waitForBytesWritten";
        return true;
    }
    virtual long long bytesAvailable() const
    {
        qDebug() << "AudioStream::bytesAvailable";
        return buffer_length;
    }

 private:
    snd_pcm_t           *playback_handle;
    snd_pcm_hw_params_t *hw_params;
    const unsigned int length       = 1;
    const unsigned int freq_per_sec = 8000;
    const unsigned int sample_size  = 16;
    const unsigned int num_channels = 1;
    const long long buffer_length = ( sample_size * freq_per_sec * num_channels * length ) / 8;
};


#endif // ALSAAUDIOOUTPUT_H
