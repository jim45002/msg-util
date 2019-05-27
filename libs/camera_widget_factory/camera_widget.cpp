
#include <QWidget>
#include <QString>
#include <QUrl>
#include <QDebug>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QLayout>
#include <QHBoxLayout>
#include <QCamera>
#include <QMediaRecorder>
#include <QMediaObject>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QCameraViewfinder>

#include "video_widget.h"
#include "video_buffer_device.h"
#include "camera_device.h"
#include "camera_device_interface.h"
#include "camera_widget.h"
#include "ui_camera_widget.h"

camera_widget::camera_widget(QWidget* parent)
    : parent(parent)
{
  setupUi (parent);
}

camera_widget::~camera_widget() {  }

QWidget *camera_widget::parent_widget()
{
    return parent;
}

void camera_widget::start()
{
    player->play();
}

void camera_widget::setMedia(QUrl &url, QIODevice *stream)
{
   auto media_content =
           std::make_shared<QMediaContent>(url);
   setMedia(media_content,stream);
}

void camera_widget::setMedia(shared_ptr<QMediaContent> media,
                             QIODevice *stream)
{
  this->media = media;
  this->stream = stream;
  player->setMedia(*this->media,stream);
}

void camera_widget::setMedia(const QString &media_path, QIODevice *stream)
{
    *this->media = QMediaContent(QUrl::fromLocalFile(media_path));
    this->stream = stream;
    player->setMedia(*this->media,stream);
}

QCameraViewfinder* camera_widget::video_surface_widget()
{
    return viewfinder;
}
