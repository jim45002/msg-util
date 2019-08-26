#ifndef MAP_MARKUP_POST_INTERFACE_H
#define MAP_MARKUP_POST_INTERFACE_H

#include <QObject>

#include "scribble_manager.h"

class QString;

class map_markup_post_interface : public QObject
{
    Q_OBJECT

public:
    map_markup_post_interface() {}
    virtual ~map_markup_post_interface() {}

    virtual void set_data_location(const QString& data_path = "./incoming_map_markup_data") = 0;
    virtual void process_map_markup_data() = 0;
    virtual QList<scribble_manager::line_data>& lines_map_data() = 0;
    virtual QList<scribble_manager::text_data>& text_map_data() = 0;
    virtual int height() = 0;
    virtual int width() = 0;
    virtual qreal center_lat() = 0;
    virtual qreal center_lon() = 0;
    virtual int   zoom() = 0;
    virtual void save_map_markup() = 0;

signals:
    emit void log_data(QString);
};

#endif // MAP_MARKUP_POST_INTERFACE_H
