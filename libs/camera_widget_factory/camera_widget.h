#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H


#include <memory>

#include <QObject>

#include "ui_camera_widget.h"
#include "camera_widget_interface.h"

class QVideoWidget;
class QMediaPlayer;
class QWidget;
class QString;
class QCameraViewfinder;
class QMediaObject;
class QMediaRecorder;

class video_buffer_device;
class video_widget;

using namespace std;

class camera_widget
        : public QObject, public camera_widget_interface,
          private Ui::camera_widget
{
    Q_OBJECT

public:
    camera_widget(QWidget *parent);
    virtual ~camera_widget();
    virtual QWidget* parent_widget();
    virtual void pause() {}
    virtual void start();
    virtual void setMedia(QUrl& url, QIODevice* stream = nullptr);
    virtual void setMedia(shared_ptr<QMediaContent> media,
                          QIODevice* = nullptr);
    virtual void setMedia(const QString& media_path,
                          QIODevice* = nullptr);
    virtual QCameraViewfinder* video_surface_widget();
    virtual void setMuted(bool ) {}
    virtual void setVolume(int ){}
    virtual void stop() {}
private:
  QWidget* parent;
  shared_ptr<QMediaPlayer> player;
  video_widget *videoWidget;
  shared_ptr<QMediaContent> media;
  QIODevice *stream;
  QMediaObject*  media_object;
  QMediaRecorder* media_recorder;
  video_buffer_device* video_buff_device;
};

#endif // CAMERA_WIDGET_H
