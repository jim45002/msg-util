
#include <memory>

#include "camera_widget_interface.h"
#include "camera_device_interface.h"
#include "camera_widget.h"
#include "camera_device.h"
#include "camera_widget_factory.h"

camera_widget_factory::camera_widget_factory()
{

}

std::shared_ptr<camera_widget_interface>
camera_widget_factory::create(camera_widget_interface*,QWidget* parent)
{
    return std::make_shared<camera_widget>(parent);
}

std::shared_ptr<camera_device_interface>
camera_widget_factory::create(camera_device_interface*,QWidget *parent)
{
    return std::make_shared<camera_device>(parent);
}


