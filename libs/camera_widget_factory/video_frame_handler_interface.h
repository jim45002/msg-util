#ifndef VIDEO_FRAME_HANDLER_INTERFACE_H
#define VIDEO_FRAME_HANDLER_INTERFACE_H

#include <QObject>

class video_frame_handler_interface
        : public QObject
{
    Q_OBJECT
 public:

    video_frame_handler_interface(QObject* parent) : QObject(parent) { }
    virtual ~video_frame_handler_interface() { }

 private:

};

#endif // VIDEO_FRAME_HANDLER_INTERFACE_H
