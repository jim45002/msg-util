#ifndef MAP_MARKUP_POST_H
#define MAP_MARKUP_POST_H

#include <QString>

#include "map_markup_post_interface.h"

class map_widget_interface;

class map_markup_post : public map_markup_post_interface
{
    Q_OBJECT

public:
    map_markup_post(map_widget_interface* parent);
    virtual ~map_markup_post() { }
    virtual void set_data_location(const QString& data_path = "./incoming_map_markup_data");
    virtual void process_map_markup_data();
    virtual QList<scribble_manager::line_data>& lines_map_data();
    virtual QList<scribble_manager::text_data>& text_map_data();
    virtual int height() { return h; }
    virtual int width() { return w; }
    virtual qreal center_lat() { return lat; }
    virtual qreal center_lon() { return lon; }
    virtual int   zoom() { return map_zoom; }
    virtual void save_map_markup();
private:
    map_widget_interface* mwi_p;
    QString data_location_path;
    QList<scribble_manager::line_data> line_list;
    QList<scribble_manager::text_data> text_list;
    qreal lat;
    qreal lon;
    int h;
    int w;
    int map_zoom;
};

#endif // MAP_MARKUP_POST_H
