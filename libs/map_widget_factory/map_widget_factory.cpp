
#include <memory>
#include <mutex>

#include "map_widget.h"
#include "map_widget_factory.h"
#include "map_widget_interface.h"

map_widget_factory::map_widget_factory()

{
}

std::shared_ptr<map_widget_interface> map_widget_factory::create(QWidget* parent)
{
    return std::make_shared<map_widget>(parent);
}

