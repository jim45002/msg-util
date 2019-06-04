#ifndef VIDEO_FRAME_HANDLER_H
#define VIDEO_FRAME_HANDLER_H

#include "video_frame_handler_interface.h"

class video_frame_handler
        : public video_frame_handler_interface
{
    Q_OBJECT

public:
    video_frame_handler(QObject* parent = nullptr );
    virtual ~video_frame_handler() { }
};

#endif // VIDEO_FRAME_HANDLER_H
