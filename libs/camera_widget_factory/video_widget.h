#ifndef VIDEO_WIDGET_H
#define VIDEO_WIDGET_H

#include <QVideoWidget>

class video_widget : public QVideoWidget
{
    Q_OBJECT
public:
    video_widget(QWidget *parent);
    virtual ~video_widget() { }
};

#endif // VIDEO_WIDGET_H
