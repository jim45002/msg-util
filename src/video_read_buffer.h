#ifndef VIDEO_READ_BUFFER_H
#define VIDEO_READ_BUFFER_H

#include <QIODevice>

class video_read_buffer : public QIODevice
{
public:
    video_read_buffer();
};

#endif // VIDEO_READ_BUFFER_H
