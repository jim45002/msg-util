#include "alsa_audio_output.h"


alsa_audio_output::alsa_audio_output(QObject* parent)
    : QIODevice (parent)
{

}

alsa_audio_output::~alsa_audio_output()
{

}

bool alsa_audio_output::open(OpenMode)
{
    qDebug() << "ALSAAudioInput::Open() - Opening Alsa audio device for playback" ;

    int err;
    if ((err = snd_pcm_open (&playback_handle,"default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
    {
        fprintf (stderr, "cannot open audio device %s (%s) for Playback\n",
                 "default",
                 snd_strerror (err));
    }
    else
    {
        fprintf (stderr, "Opened Alsa audio device for Playback\n");
    }

    if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0)
    {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
                 snd_strerror (err));

    }

    if ((err = snd_pcm_hw_params_any (playback_handle, hw_params)) < 0)
    {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
                 snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_set_access (playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
        fprintf (stderr, "cannot set access type (%s)\n",
                 snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_set_format (playback_handle, hw_params, SND_PCM_FORMAT_S16_LE )) < 0)
    {
        fprintf (stderr, "cannot set sample format (%s)\n",
                 snd_strerror (err));
    }
    unsigned int val = freq_per_sec;
    if ((err = snd_pcm_hw_params_set_rate_near (playback_handle, hw_params, &val, 0)) < 0)
    {
        fprintf (stderr, "cannot set sample rate (%s)\n",
                 snd_strerror (err));
    }

    if ((err = snd_pcm_hw_params_set_channels (playback_handle, hw_params, num_channels)) < 0)
    {
        fprintf (stderr, "cannot set channel count (%s)\n",
                 snd_strerror (err));

    }

    if ((err = snd_pcm_hw_params (playback_handle, hw_params)) < 0)
    {
        fprintf (stderr, "cannot set parameters (%s)\n",
                 snd_strerror (err));
    }

    snd_pcm_hw_params_free (hw_params);

    if ((err = snd_pcm_prepare (playback_handle)) < 0)
    {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
                 snd_strerror (err));
    }
}

void alsa_audio_output::close()
{
    qDebug() << "Calling close() ";
    snd_pcm_close (playback_handle);
}

qint64 alsa_audio_output::writeData(const char* data, qint64 maxLen)
{
    int err2=0;
    int err=0;
    if(snd_pcm_wait(playback_handle,-1))
    {
        if ((err = snd_pcm_writei (playback_handle, data, maxLen)) != maxLen)
        {
            fprintf (stderr, "write to audio interface failed (%s)\n",snd_strerror (err));

            if(err == -EPIPE || err == -EBADFD || err == -ESTRPIPE)
            {

            }
            else
            {
                qDebug() << "Playback - err == " << err;
            }
        }
        else
        {
            fprintf(stderr,"Wrote %d samples\n",err);


        }
        // snd_pcm_drain(playback_handle);
        if((err2 = snd_pcm_prepare (playback_handle)) < 0)
        {
            fprintf (stderr, "cannot prepare audio interface for use Playback (%s)\n",
                     snd_strerror (err2));
        }

    }
    return err;
}
