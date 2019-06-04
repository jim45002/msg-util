#ifndef VIDEO_BUFFER_DEVICE_H
#define VIDEO_BUFFER_DEVICE_H

#include <QAbstractVideoSurface>

class video_buffer_device : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    video_buffer_device(QObject *parent);
    virtual ~video_buffer_device();


};

#endif // VIDEO_BUFFER_DEVICE_H
