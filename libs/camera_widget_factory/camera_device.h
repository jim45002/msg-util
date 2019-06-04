#ifndef CAMERA_DEVICE_H
#define CAMERA_DEVICE_H

#include <memory>

#include <QVideoEncoderSettings>

#include "camera_device_interface.h"

class QCamera;
class QMediaRecorder;
class QVideoProbe;
class QVideoFrame;
class camera_widget;
class object_detect_filter;
class detect_filter_runnable;
class QVideoSurfaceFormat;

class camera_device : public camera_device_interface
{
public:
    camera_device(QWidget* parent);
    virtual ~camera_device();

    virtual void start();
    virtual void stop();
    virtual void start_record(QUrl url);
    virtual void stop_record();
    virtual void load();
    virtual QCamera* get_camera_device();
    virtual QList<camera_info_interface*>
    get_available_cameras();

public slots:
    void video_frame_probed(const QVideoFrame &);
private:
  std::shared_ptr<QCamera> cam_dev_sptr;
  camera_widget* cam_widget;
  QMediaRecorder* mediaRecorder;
  QVideoEncoderSettings videoSettings;
  QVideoProbe* video_probe;
  QString videoContainerFormat;
  object_detect_filter* detector;
  detect_filter_runnable* filter;
  QVideoSurfaceFormat* video_surface_format;

};

#endif // CAMERA_DEVICE_H
