#ifndef CAMERA_WIDGET_FACTORY_H
#define CAMERA_WIDGET_FACTORY_H

#include <mutex>
#include <memory>

class QWidget;
class camera_widget_interface;

class camera_widget_factory
{
public:
    camera_widget_factory();
    ~camera_widget_factory() = default;

    camera_widget_factory(const camera_widget_factory&) = delete;
    camera_widget_factory& operator=(const camera_widget_factory&) = delete;

    static std::shared_ptr<camera_widget_interface> create(QWidget *parent);
};

#endif // CAMERA_WIDGET_FACTORY_H
