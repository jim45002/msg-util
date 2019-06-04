
#include <chrono>
#include <thread>

#include <QCamera>
#include <QCameraInfo>
#include <QVideoSurfaceFormat>
#include <QDebug>
#include <QAudioEncoderSettings>
#include <QMediaRecorder>
#include <QUrl>
#include <QMediaMetaData>
#include <QVariant>
#include <QTimer>
#include <QVideoProbe>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>

#include "detect_filter.h"
#include "video_buffer_device.h"
#include "video_widget.h"
#include "camera_info.h"
#include "camera_widget.h"
#include "camera_device.h"

camera_device::camera_device(QWidget *parent)
    : camera_device_interface (parent)
{
    detector = new object_detect_filter;
    filter = new detect_filter_runnable(detector);

    video_probe = new QVideoProbe;
    connect(video_probe,
            SIGNAL(videoFrameProbed(const QVideoFrame&)),
            this,
            SLOT(video_frame_probed(const QVideoFrame&)));

    cam_dev_sptr =
            std::make_shared<QCamera>(
                QCameraInfo::defaultCamera()
                );

    video_probe->setSource(cam_dev_sptr.get());

    cam_widget = new camera_widget(parent);
    cam_dev_sptr->
            setViewfinder(cam_widget->video_surface_widget());
    mediaRecorder = new QMediaRecorder(cam_dev_sptr.get());
    cam_dev_sptr->setCaptureMode(QCamera::CaptureVideo);
}

camera_device::~camera_device()
{
   cam_dev_sptr.reset();
   cam_dev_sptr = nullptr;

   delete mediaRecorder;
   delete cam_widget;  
   delete filter;
   delete detector;
}

void camera_device::video_frame_probed(const QVideoFrame &frame)
{
   const QVideoSurfaceFormat surface_format(frame.size(),
                                      frame.pixelFormat(),
                                      frame.handleType());
   QVideoFrame input = frame;
   filter->run(&input,
               surface_format,
               QVideoFilterRunnable::LastInChain);
}

void camera_device::start_record(QUrl url)
{
   mediaRecorder->setMetaData(QMediaMetaData::Title,
                              QVariant(QLatin1String("-")));
   mediaRecorder->setOutputLocation(url);
   mediaRecorder->record();
}

void camera_device::stop_record()
{
   mediaRecorder->stop();
}

void camera_device::start()
{
   cam_dev_sptr->start();
}

void camera_device::stop()
{
   cam_dev_sptr->stop();
}

void camera_device::load()
{
   cam_dev_sptr->load();
}

QCamera* camera_device::get_camera_device()
{
   return cam_dev_sptr.get();
}

QList<camera_info_interface*> camera_device::get_available_cameras()
{
    QList<camera_info_interface*> cams;

    const QList<QCameraInfo> availableCameras =
            QCameraInfo::availableCameras();

    camera_info* cam;
    for (const QCameraInfo &cameraInfo : availableCameras)
    {
        cam = new camera_info;
        cam->descrip = cameraInfo.description();
        cam->dev_name = cameraInfo.deviceName();
        cam->orient = cameraInfo.orientation();
        cam->pos = cameraInfo.position();

        cams.push_back(cam);
    }
    return cams;
}
