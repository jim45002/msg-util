#include "camera_widget.h"

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QLayout>
#include <QHBoxLayout>

camera_widget::camera_widget(QWidget* parent)
    : player(make_shared<QMediaPlayer>(this)),
      media(make_shared<QMediaContent>())
{
  setupUi (parent);

  QHBoxLayout *hbox_layout = new QHBoxLayout(frame);
  frame->setLayout (hbox_layout);
  videoWidget = new QVideoWidget(frame);
  hbox_layout->addWidget (videoWidget);
  player->setVideoOutput(videoWidget);
  videoWidget->show ();
}

void camera_widget::start()
{
  player->play();
}

void camera_widget::setMedia(shared_ptr<QMediaContent> media, QIODevice *stream)
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

