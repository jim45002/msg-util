
#include <mutex>
#include <memory>

#include "camera_widget_interface.h"
#include <memory>
#include "camera_widget_factory.h"
#include "camera_widget.h"


camera_widget_factory::camera_widget_factory()
{

}

std::shared_ptr<camera_widget_interface>
camera_widget_factory::create(QWidget* parent)
{
    return std::make_shared<camera_widget>(parent);
}

