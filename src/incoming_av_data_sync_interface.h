#ifndef INCOMING_AV_DATA_SYNC_INTERFACE_H
#define INCOMING_AV_DATA_SYNC_INTERFACE_H

#include <QObject>

class incoming_data_sync_interface : public QObject
{
    Q_OBJECT
public:
    incoming_data_sync_interface(QObject* parent)
        : QObject(parent) { }
    virtual ~incoming_data_sync_interface() { }
    virtual void set_identifier(int) = 0;
    virtual void set_audio_filename(QString) = 0;
    virtual void set_video_filename(QString) = 0;
    virtual QString get_video_filename() = 0;
    virtual QString get_audio_filename() = 0;
signals:

public slots:
};

#endif // INCOMING_AV_DATA_SYNC_INTERFACE_H
