#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H


#include <memory>

#include "ui_camera_widget.h"
#include "camera_widget_interface.h"

class QVideoWidget;
class QMediaPlayer;
class QWidget;
class QString;

using namespace std;

class camera_widget
        : public QObject, public camera_widget_interface,
          private Ui::camera_widget
{
public:
    camera_widget(QWidget *parent);
    virtual ~camera_widget() {}

    virtual void pause() {}
    virtual void start();
    virtual void setMedia(shared_ptr<QMediaContent> media,
                          QIODevice* = nullptr);
    virtual void setMedia(const QString& media_path, QIODevice* = nullptr);
    virtual void setMuted(bool ) {}
    virtual void setVolume(int ){}
    virtual void stop() {}
private:
  shared_ptr<QMediaPlayer> player;
  QVideoWidget *videoWidget;
  shared_ptr<QMediaContent> media;
  QIODevice *stream;
};

#endif // CAMERA_WIDGET_H
