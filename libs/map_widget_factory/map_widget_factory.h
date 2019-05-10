#ifndef MAP_WIDGET_FACTORY_H
#define MAP_WIDGET_FACTORY_H

#include <mutex>
#include <memory>

#include "map_widget_factory_global.h"


class QWidget;
class map_widget_interface;

class MAP_WIDGET_FACTORYSHARED_EXPORT map_widget_factory
{
 friend class __gnu_cxx::new_allocator<map_widget_factory>;

public:
    static std::shared_ptr<map_widget_interface> create(QWidget *parent);

private:
     map_widget_factory();
    ~map_widget_factory() = default;

    map_widget_factory(const map_widget_factory&) = delete;
    map_widget_factory& operator=(const map_widget_factory&) = delete;

};

#endif // MAP_WIDGET_FACTORY_H
