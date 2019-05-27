#ifndef CAMERA_DEVICE_INTERFACE_H
#define CAMERA_DEVICE_INTERFACE_H

#include <QList>
#include <QObject>

class QUrl;
class QCamera;

class camera_info_interface;

class camera_device_interface : public QObject
{
    Q_OBJECT
public:

    camera_device_interface(QObject* parent)
        : QObject(parent) { }
    virtual ~camera_device_interface() { }
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void load() = 0;
    virtual void start_record(QUrl url) = 0;
    virtual void stop_record() = 0;
    virtual QCamera* get_camera_device() = 0;
    virtual QList<camera_info_interface*> get_available_cameras() = 0;

};





#endif // CAMERA_DEVICE_INTERFACE_H
