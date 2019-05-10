#ifndef MAP_WIDGET_H
#define MAP_WIDGET_H

#include <marble/MarbleWidget.h>
#include "map_widget_interface.h"

class QWidget;
class map_paint_layer;

using namespace Marble;

class map_widget : public MarbleWidget, public map_widget_interface
{
    friend class map_paint_layer;

    Q_OBJECT
public:
    map_widget(QWidget *parent);
    virtual ~map_widget();

    void drawPoint(const QPoint point);
    virtual void centerOn( const qreal lon, const qreal lat,
                           bool animated = false );

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *);
    virtual QWidget* map_dispaly_widget();
    virtual void map_enable_scibble(bool status = false);
    virtual void map_disable_scibble();


public slots:
    /**
     * @brief Signal that the zoom has changed, and to what.
     * @param zoom  The new zoom value.
     * @see  setZoom()
     */
    void on_zoomChanged( int zoom );
    void on_distanceChanged( const QString& distanceString );
    void on_tileLevelChanged( int level );

    /**
     * @brief Signal that the theme has changed
     * @param theme  Name of the new theme.
     */
    void on_themeChanged( const QString& theme );
    void on_projectionChanged( Projection );
    void on_mouseMoveGeoPosition( const QString& );
    void on_mouseClickGeoPosition( qreal lon, qreal lat, GeoDataCoordinates::Unit unit );
    void on_framesPerSecond( qreal fps );

    /** This signal is emit when a new rectangle region is selected over the map
     *  The list of double values include coordinates in degrees using this order:
     *  lon1, lat1, lon2, lat2 (or West, North, East, South) as left/top, right/bottom rectangle.
     */
    void on_regionSelected( const QList<double>& );

    /**
     * This signal is emit when the settings of a plugin changed.
     */
    void on_pluginSettingsChanged();

    /**
     * @brief Signal that a render item has been initialized
     */
    void on_renderPluginInitialized( RenderPlugin *renderPlugin );

    /**
     * This signal is emitted when the visible region of the map changes. This typically happens
     * when the user moves the map around or zooms.
     */
    void on_visibleLatLonAltBoxChanged( const GeoDataLatLonAltBox& visibleLatLonAltBox );

    /**
     * @brief Emitted when the layer rendering status has changed
     * @param status New render status
     */
    void on_renderStatusChanged( RenderStatus status );
    void on_renderStateChanged( const RenderState &state );
    void on_highlightedPlacemarksChanged( qreal lon, qreal lat, GeoDataCoordinates::Unit unit );

 protected:

     virtual bool event(QEvent *event);
    /**
     * @brief Reimplementation of the leaveEvent() function in QWidget.
     */
    virtual void leaveEvent( QEvent *event );

    /**
     * @brief Reimplementation of the paintEvent() function in QWidget.
     */
    virtual void paintEvent( QPaintEvent *event );

    /**
     * @brief Reimplementation of the resizeEvent() function in QWidget.
     */
    virtual void resizeEvent( QResizeEvent *event );

    virtual void connectNotify(const QMetaMethod &signal);
    virtual void disconnectNotify(const QMetaMethod &signal);

    /**
      * @brief Reimplementation of the changeEvent() function in QWidget to
      * react to changes of the enabled state
      */
    virtual void changeEvent( QEvent * event );

    /**
     * @brief Enables custom drawing onto the MarbleWidget straight after
     * @brief the globe and before all other layers has been rendered.
     * @param painter
     *
     * @deprecated implement LayerInterface and add it using @p addLayer()
     */
    virtual void customPaint( GeoPainter *painter );

private:
    int current_zoom;
    int current_distance;
    int current_tileLevel;
    Projection current_projection;
    QString geoposition;
    qreal unit_click_lat, unit_click_lon;


    QPoint lastPoint;
    QPoint endPoint;
    bool   scribbling;
    bool   modified;
    QColor myPenColor;
    float  myPenWidth;
    map_paint_layer* paint_layer;
    QWidget* parentWidget;

};

#endif // MAP_WIDGET_H
