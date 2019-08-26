#ifndef MAP_WIDGET_INTERFACE
#define MAP_WIDGET_INTERFACE

#include <QObject>
#include <marble/MarbleGlobal.h>

class QWidget;
class map_paint_layer;

class map_widget_interface
{
public:
    map_widget_interface() {}
    virtual ~map_widget_interface() {}

    virtual void centerOn( const qreal lon, const qreal lat,
                           bool animated = false ) = 0;
    /**
     * @brief Return the longitude of the center point.
     * @return The longitude of the center point in degree.
     */
    virtual qreal centerLongitude() const = 0;

    /**
     * @brief Return the latitude of the center point.
     * @return The latitude of the center point in degree.
     */
    virtual qreal centerLatitude() const = 0;
    /**
     * @brief Return the current zoom amount.
     */
    virtual int zoom()  = 0;

    /**
     * @brief  Zoom the view to a certain zoomlevel
     * @param  zoom  the new zoom level.
     *
     * The zoom level is an abstract value without physical
     * interpretation.  A zoom value around 1000 lets the viewer see
     * all of the earth in the default window.
     */
    virtual void setZoom( int zoom, Marble::FlyToMode mode = Marble::Instant ) = 0;

    /**
     * @brief Get the screen coordinates corresponding to geographical coordinates in the widget.
     * @param lon    the lon coordinate of the requested pixel position
     * @param lat    the lat coordinate of the requested pixel position
     * @param x      the x coordinate of the pixel is returned through this parameter
     * @param y      the y coordinate of the pixel is returned through this parameter
     * @return @c true  if the geographical coordinates are visible on the screen
     *         @c false if the geographical coordinates are not visible on the screen
     */
    virtual bool screenCoordinates( qreal lon, qreal lat,
                            qreal& x, qreal& y ) const = 0;

    virtual map_paint_layer* get_map_widget_paint_layer() = 0;
    virtual QWidget* map_dispaly_widget() = 0;
    virtual void map_enable_scibble(bool = false) = 0;
    virtual void map_disable_scibble() = 0;
};

#endif // MAP_WIDGET_INTERFACE

