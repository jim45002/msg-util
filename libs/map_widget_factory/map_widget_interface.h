#ifndef MAP_WIDGET_INTERFACE
#define MAP_WIDGET_INTERFACE

#include <QObject>

class QWidget;
class map_paint_layer;

class map_widget_interface
{
public:
    map_widget_interface() {}
    virtual ~map_widget_interface() {}

    virtual void centerOn( const qreal lon, const qreal lat,
                           bool animated = false ) = 0;

    virtual map_paint_layer* get_map_widget_paint_layer() = 0;
    virtual QWidget* map_dispaly_widget() = 0;
    virtual void map_enable_scibble(bool = false) = 0;
    virtual void map_disable_scibble() = 0;
};

#endif // MAP_WIDGET_INTERFACE

