#ifndef CAMERA_WIDGET_INTERFACE
#define CAMERA_WIDGET_INTERFACE

#include <memory>

class QFile;
class QMediaContent;
class QIODevice;
class QString;

class camera_widget_interface
{
public:
    camera_widget_interface() {}
    virtual ~camera_widget_interface() {}

    virtual void pause() = 0;
    virtual void start() = 0;
    virtual void setMedia(std::shared_ptr<QMediaContent> media, QIODevice * stream = 0) = 0;
    virtual void setMedia(const QString& media_path, QIODevice * stream = 0) = 0;
    virtual void setMuted(bool muted) = 0;
    virtual void setVolume(int volume) = 0;
    virtual void stop() = 0;
};

#endif // CAMERA_WIDGET_INTERFACE

