#ifndef INCOMING_AV_DATA_SYNC_H
#define INCOMING_AV_DATA_SYNC_H

#include "incoming_av_data_sync_interface.h"

class incoming_av_data_sync
        : public incoming_av_data_sync_interface
{
public:
    incoming_av_data_sync(QObject *parent = nullptr);
    virtual ~incoming_av_data_sync();
    virtual void set_identifier(int);
    virtual void set_audio_filename(QString);
    virtual void set_video_filename(QString);
    virtual QString get_video_filename();
    virtual QString get_audio_filename();
private:
    int identifier;
    QString audio_filename;
    QString video_filename;
};

#endif // INCOMING_AV_DATA_SYNC_H
