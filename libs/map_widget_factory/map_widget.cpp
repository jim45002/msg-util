#include "map_widget.h"
#include <QWidget>
#include <QColor>
#include <marble/GeoPainter.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoPainter.h>
#include <QMouseEvent>
#include <QHBoxLayout>
#include "map_paint_layer.h"
#include "scribble_manager.h"

using namespace Marble;

map_widget::map_widget(QWidget* parent)
    : Marble::MarbleWidget(parent), parentWidget(parent)
{
    QSizePolicy sizePolicy;
    sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);

    paint_layer = new map_paint_layer(this);
    QHBoxLayout *layout = new QHBoxLayout;
    setLayout (layout);
    layout->addWidget (paint_layer);
    paint_layer->show ();
    setProjection(Marble::Mercator);
    setMapThemeId("earth/openstreetmap/openstreetmap.dgml");

    QObject::connect(this,SIGNAL(zoomChanged(int)),this,SLOT(on_zoomChanged(int)));
    QObject::connect(this,SIGNAL(distanceChanged(QString)),this, SLOT(on_distanceChanged(QString)));
    QObject::connect(this,SIGNAL(tileLevelChanged(int)),this,SLOT(on_tileLevelChanged( int )));
    QObject::connect(this,SIGNAL(themeChanged(QString)),this,SLOT(on_themeChanged(QString)));
    QObject::connect(this,SIGNAL(projectionChanged(Projection)),this,
                     SLOT(on_projectionChanged(Projection)));
    QObject::connect(this,SIGNAL(mouseMoveGeoPosition(const QString)),this,
                     SLOT(on_mouseMoveGeoPosition (const QString)));
    QObject::connect(this,SIGNAL(mouseClickGeoPosition(qreal,qreal,GeoDataCoordinates::Unit)),this,
                     SLOT(on_mouseClickGeoPosition(qreal,qreal,GeoDataCoordinates::Unit)));
    QObject::connect(this,SIGNAL(framesPerSecond(qreal)),this,SLOT(on_framesPerSecond(qreal)));
    QObject::connect(this,SIGNAL(regionSelected(QList<double>)),this,
                     SLOT(on_regionSelected(QList<double>)));
    QObject::connect(this,SIGNAL(pluginSettingsChanged ()),this,SLOT(on_pluginSettingsChanged ()));
    QObject::connect(this,SIGNAL(renderPluginInitialized(RenderPlugin*)),this,
                     SLOT(on_renderPluginInitialized(RenderPlugin*)));
    QObject::connect(this,SIGNAL(visibleLatLonAltBoxChanged(GeoDataLatLonAltBox)),this,
                     SLOT(on_visibleLatLonAltBoxChanged(GeoDataLatLonAltBox)));
    QObject::connect(this,SIGNAL(renderStatusChanged(RenderStatus)),this,
                     SLOT(on_renderStatusChanged(RenderStatus)));
    QObject::connect(this,SIGNAL(renderStateChanged(RenderState)),this,
                     SLOT(on_renderStateChanged(RenderState)));
    QObject::connect(this,SIGNAL(highlightedPlacemarksChanged(qreal,qreal,GeoDataCoordinates::Unit)),this,
                     SLOT(on_highlightedPlacemarksChanged(qreal,qreal,GeoDataCoordinates::Unit)));
}

map_widget::~map_widget()
{

}

void map_widget::centerOn( const qreal lon, const qreal lat,
                           bool animated)
{
   Marble::MarbleWidget::centerOn(lon,lat,animated);
}


void map_widget::on_zoomChanged(int zoom)
{
   current_zoom = zoom;
}

void map_widget::on_distanceChanged(const QString &distanceString)
{

}

void map_widget::on_tileLevelChanged(int level)
{

}

void map_widget::on_themeChanged(const QString &theme)
{

}

void map_widget::on_projectionChanged(Projection)
{

}

void map_widget::mouseMoveEvent(QMouseEvent *event)
{
   Marble::MarbleWidget::mouseMoveEvent (event);
 //   qDebug() << "void map_widget::mouseMoveEvent(QMouseEvent *event)";
}

void map_widget::mousePressEvent(QMouseEvent *event)
{
  Marble::MarbleWidget::mousePressEvent (event);
 //   qDebug() << "void map_widget::mousePressEvent(QMouseEvent *event)";
}

void map_widget::mouseReleaseEvent (QMouseEvent *event)
{

}

void map_widget::wheelEvent(QWheelEvent *)
{

}

QWidget* map_widget::map_dispaly_widget()
{
    return this;
}

void map_widget::map_enable_scibble(bool status)
{
    if(status)
    {
        setShowScaleBar (false);
        //       QObjectList obj_list = children ();
        //       for(auto obj : obj_list)
        //       {
        //         if(obj->isWindowType ())
        //            dynamic_cast<QWidget*>(obj)->setEnabled (false);
        //       }
        paint_layer->show();
        paint_layer->setEnabled (true);
    }
    else
    {
        paint_layer->hide();
        paint_layer->setEnabled (false);
        setShowScaleBar (true);

    }
}

void map_widget::map_disable_scibble()
{
    setEnabled (false);
}

void map_widget::on_mouseMoveGeoPosition(const QString &)
{

}



void map_widget::on_mouseClickGeoPosition(qreal lon, qreal lat, GeoDataCoordinates::Unit unit)
{
  qDebug() << "lat " << lat << ":" << "lon " << lon ;
}

void map_widget::on_framesPerSecond(qreal fps)
{

}

void map_widget::on_regionSelected(const QList<double> &)
{

}

void map_widget::on_pluginSettingsChanged()
{

}

void map_widget::on_renderPluginInitialized(RenderPlugin *renderPlugin)
{

}

void map_widget::on_visibleLatLonAltBoxChanged(const GeoDataLatLonAltBox &visibleLatLonAltBox)
{

}

void map_widget::on_renderStatusChanged(RenderStatus status)
{

}

void map_widget::on_renderStateChanged(const RenderState &state)
{

}

void map_widget::on_highlightedPlacemarksChanged(qreal lon, qreal lat, GeoDataCoordinates::Unit unit)
{

}

bool map_widget::event(QEvent *event)
{
    Marble::MarbleWidget::event (event);
}

void map_widget::leaveEvent(QEvent *event)
{
    MarbleWidget::leaveEvent (event);
}

void map_widget::paintEvent(QPaintEvent *event)
{
    MarbleWidget::paintEvent (event);
}

void map_widget::resizeEvent(QResizeEvent *event)
{
    MarbleWidget::resizeEvent (event);
}

void map_widget::connectNotify(const QMetaMethod &signal)
{
    MarbleWidget::connectNotify (signal);
}

void map_widget::disconnectNotify(const QMetaMethod &signal)
{
    MarbleWidget::disconnectNotify (signal);
}

void map_widget::changeEvent(QEvent *event)
{
    MarbleWidget::changeEvent (event);
}

void map_widget::customPaint(GeoPainter *painter)
{
    MarbleWidget::customPaint (painter);
}

void map_widget::drawPoint(const QPoint point)
{

}
