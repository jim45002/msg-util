#ifndef CAMERA_WIDGET_FACTORY_H
#define CAMERA_WIDGET_FACTORY_H

#include <memory>

class QWidget;
class camera_widget_interface;
class camera_device_interface;

class camera_widget_factory
{
public:
    camera_widget_factory();
    ~camera_widget_factory() = default;

    camera_widget_factory(const camera_widget_factory&) = delete;
    camera_widget_factory& operator=(const camera_widget_factory&) = delete;

     static std::shared_ptr<camera_device_interface>
     create(camera_device_interface*,
            QWidget *parent);

    static std::shared_ptr<camera_widget_interface>
    create(camera_widget_interface*,
           QWidget *parent);
};

#endif // CAMERA_WIDGET_FACTORY_H
