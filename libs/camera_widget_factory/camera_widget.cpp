
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
#include <QVideoProbe>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>

#include "detect_filter.h"
#include "video_frame_handler.h"
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

camera_widget::camera_widget(camera_widget_interface*,
                             QWidget* parent)
    : parent(parent)
{
    setupUi (parent);

    player = std::make_shared<QMediaPlayer>(this,
                                            QMediaPlayer::
                                            StreamPlayback);
    player->setVideoOutput(viewfinder);

    detector = new object_detect_filter;
    filter = new detect_filter_runnable(detector);

    video_probe = new QVideoProbe;
    video_probe->setSource(player.get());

    connect(video_probe,
            SIGNAL(videoFrameProbed(const QVideoFrame&)),
            this,
            SLOT(video_frame_probed(const QVideoFrame&)));

}


camera_widget::~camera_widget()
{

}


QWidget *camera_widget::parent_widget()
{
    return parent;
}


void camera_widget::video_frame_probed(const QVideoFrame &frame)
{
    const QVideoSurfaceFormat surface_format(frame.size(),
                                       frame.pixelFormat(),
                                       frame.handleType());
    QVideoFrame input = frame;
    filter->run(&input,
                surface_format,
                QVideoFilterRunnable::LastInChain);

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


