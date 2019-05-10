#ifndef ALSAAUDIOINPUT_H
#define ALSAAUDIOINPUT_H

#include <alsa/asoundlib.h>

#include <cstdio>
#include <cstdlib>

#include <QDebug>
#include <QObject>


class alsa_audio_input : public  QObject
{
    Q_OBJECT
public:
    alsa_audio_input(QObject* = nullptr )

    {
       open(0);
    }
    virtual ~alsa_audio_input() {}

    virtual bool open(int)
    {
        qDebug() << "ALSAAudioInput::Open() - Opening Alsa audio device for capture" ;
        int err;
        if ((err = snd_pcm_open (&capture_handle, "default", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
                fprintf (stderr, "cannot open audio device %s (%s) for Capture \n",
                         "default",
                         snd_strerror (err));
        } else {
                fprintf (stderr, "Opened Alsa audio device for Capture \n");
        }

        if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
                fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
                         snd_strerror (err));

        }

        if ((err = snd_pcm_hw_params_any (capture_handle, hw_params)) < 0) {
                fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
                         snd_strerror (err));

        }

        if ((err = snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
                fprintf (stderr, "cannot set access type (%s)\n",
                         snd_strerror (err));

        }

        if ((err = snd_pcm_hw_params_set_format (capture_handle, hw_params, SND_PCM_FORMAT_S16_LE )) < 0) {
                fprintf (stderr, "cannot set sample format (%s)\n",
                         snd_strerror (err));

        }

        unsigned int val = FREQ_PER_SEC;
        if ((err = snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &val, 0)) < 0) {

                fprintf (stderr, "cannot set sample rate (%s)\n",
                         snd_strerror (err));
                exit (1);
        }

        if ((err = snd_pcm_hw_params_set_channels (capture_handle, hw_params, NUM_CHANNELS)) < 0) {
                fprintf (stderr, "cannot set channel count (%s)\n",
                         snd_strerror (err));

        }

        if ((err = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
                fprintf (stderr, "cannot set parameters (%s)\n",
                         snd_strerror (err));

        }

        snd_pcm_hw_params_free (hw_params);

        if ((err = snd_pcm_prepare (capture_handle)) < 0) {
                fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
                         snd_strerror (err));
        }

      }

    virtual bool 	atEnd ()        const { return false; }
    virtual qint64 	bytesToWrite () const { return 0; }
    virtual bool 	canReadLine ()  const { return false; }
    virtual bool 	isSequential () const { return false; }

    virtual qint64 readData(char* data, qint64 maxLen)
    {

        qDebug() << "ALSAAudioInput::readData() - maxlen == " << maxLen;
        int err=0;
        int err2=0;
        if ((err = snd_pcm_readi (capture_handle, data, maxLen)) != maxLen)
        {
            fprintf (stderr, "read from audio interface failed (%s)\n", snd_strerror (err));
            //qDebug() << "err == " << err << " EPIPE " << EPIPE;
            if(err == -EPIPE || err == -EBADFD || err == -ESTRPIPE)
            {

            }
            else
            {
              qDebug() << "Capture - err == " << err ;
            }
            if ((err2 = snd_pcm_prepare(capture_handle)) < 0)
            {
                 fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
                          snd_strerror (err2));
            }

        }
        else
        {
            fprintf(stderr,"ALSAAudioInput Read %d bytes\n",err);

        }



        return err;
    }

    virtual void close()
    {
       qDebug() << "Calling close() ";
       snd_pcm_close (capture_handle);
    }

    virtual qint64 writeData(const char* data, qint64 maxLen)
    {
        return -1;
    }
    virtual bool waitForReadyRead(int msecs)
    {
        qDebug() << "ALSAAudioInput::readData() CALL ERROR";
        return true;
    }
    virtual bool waitForBytesWritten(int msecs)
    {
        qDebug() << "ALSAAudioInput::waitForBytesWritten()";
        return true;
    }

    virtual qint64 bytesAvailable() const
    {
        qDebug() << "ALSAAudioInput::bytesAvailable()";
        return BUFFER_LENGTH;
    }
 private:

    snd_pcm_t           *capture_handle;
    snd_pcm_hw_params_t *hw_params;
    const unsigned int LENGTH       = 1;
    const unsigned int FREQ_PER_SEC = 8000;
    const unsigned int SAMPLE_SIZE  = 16;
    const unsigned int NUM_CHANNELS = 1;

    const unsigned long BUFFER_LENGTH = ( SAMPLE_SIZE * FREQ_PER_SEC * NUM_CHANNELS * LENGTH ) / 8;

};
#endif // ALSAAUDIOINPUT_H
