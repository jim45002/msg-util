#ifndef CAMERA_DEVICE_H
#define CAMERA_DEVICE_H

#include <memory>

#include <QVideoEncoderSettings>

#include "camera_device_interface.h"

class QCamera;
class QMediaRecorder;

class camera_widget;

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

private:
  std::shared_ptr<QCamera> cam_dev_sptr;
  camera_widget* cam_widget;
  QMediaRecorder* mediaRecorder;
  QVideoEncoderSettings videoSettings;
  QString videoContainerFormat;

};

#endif // CAMERA_DEVICE_H
