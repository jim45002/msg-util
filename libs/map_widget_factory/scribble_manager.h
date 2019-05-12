#ifndef SCRIBBLE_MANAGER_H
#define SCRIBBLE_MANAGER_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QColorDialog>
#include <QPaintEvent>
#include <QList>
#include <QLine>
#include <QPoint>
#include <QDebug>
#include <QMenu>
#include <marble/MarbleWidget.h>

class scribble_manager
{

public:
    struct text_data
    {
    public:
        text_data(QString t, QPoint p, int width, QColor pen_color, QFont f)
            : text(t),
              point(p),
              myPenWidth(width),
              myPenColor(pen_color),
              font(f)
        {
        }

        QColor get_color() { return myPenColor; }
        QString get_text() { return text; }
        QPoint get_point() { return point; }
        QFont get_font() { return font; }
        unsigned int get_width() { return myPenWidth; }
        QByteArray get_packed_data_buffer()
        {
            QByteArray buff;
            int text_size = text.length();
            buff.append(reinterpret_cast<char*>(&text_size),sizeof (int));
            buff.append(text.toStdString().c_str(),text.length());

            int rx = point.rx();
            int ry = point.ry();
            int x = point.x();
            int y = point.y();
            buff.append(reinterpret_cast<char*>(&rx),sizeof (int));
            buff.append(reinterpret_cast<char*>(&ry),sizeof (int));
            buff.append(reinterpret_cast<char*>(&x),sizeof (int));
            buff.append(reinterpret_cast<char*>(&y),sizeof (int));

            int red = myPenColor.red();
            int green = myPenColor.green();
            int blue = myPenColor.blue();
            buff.append(reinterpret_cast<char*>(&red),sizeof (int));
            buff.append(reinterpret_cast<char*>(&green),sizeof (int));
            buff.append(reinterpret_cast<char*>(&blue),sizeof (int));

            QString font_family = font.family();
            text_size = font_family.size();
            buff.append(reinterpret_cast<char*>(&text_size),sizeof (int));
            buff.append(font_family.toStdString().c_str(),font_family.size());

            buff.append(reinterpret_cast<char*>(&myPenWidth),
                        sizeof(unsigned int));
            return buff;
        }
   private:
        QString text;
        QPoint point;
        QColor myPenColor;
        QFont font;
        unsigned int myPenWidth;
    };

    struct line_data
    {
     public:
        line_data(int width, QColor pen_color, QLine l)
            : myPenWidth(width),
              modified(false),
              scribbling(false),
              myPenColor(pen_color),
              line(l)
        {
        }

        QColor get_color() { return myPenColor; }
        QLine get_line() { return line; }
        unsigned int get_width() { return myPenWidth; }
        QByteArray get_packed_data_buffer()
        {
            QByteArray buff;

            int red = myPenColor.red();
            int green = myPenColor.green();
            int blue = myPenColor.blue();
            buff.append(reinterpret_cast<char*>(&red),sizeof (int));
            buff.append(reinterpret_cast<char*>(&green),sizeof (int));
            buff.append(reinterpret_cast<char*>(&blue),sizeof (int));

            buff.append(reinterpret_cast<char*>(&myPenWidth),
                        sizeof(unsigned int));

            int x1 = line.x1();
            int x2 = line.x2();
            int y1 = line.y1();
            int y2 = line.y2();
            buff.append(reinterpret_cast<char*>(&x1),sizeof (int));
            buff.append(reinterpret_cast<char*>(&x2),sizeof (int));
            buff.append(reinterpret_cast<char*>(&y1),sizeof (int));
            buff.append(reinterpret_cast<char*>(&y2),sizeof (int));

            return buff;
        }

     private:
        unsigned int myPenWidth;
        bool modified;
        bool scribbling;
        QColor myPenColor;
        QLine line;
    };

    scribble_manager();
    ~scribble_manager();

    void add_line(int width, QColor pen_color, QLine l)
    {
        linesList.push_back (line_data(width,pen_color,l));
    }

    void add_text(QString t, QPoint p,int width, QColor pen_color, QFont f)
    {
        textList.push_back (text_data(t,p,width,pen_color,f));
    }

    void clear() { linesList.clear (); textList.clear(); }

    const QList<line_data> get_lines() { return linesList; }
    const QList<text_data> get_text() { return textList; }

    int get_current_zoom() { return current_zoom; }
    int get_current_distance() { return current_distance; }
    int get_current_tileLevel() { return current_tileLevel; }
    Marble::Projection get_current_projection() { return current_projection; }
    QString get_geoposition() { return geoposition; }
    qreal get_unit_click_lat() { return unit_click_lat; }
    qreal get_unit_click_lon() { return unit_click_lon; }
    qreal get_centerLatitude() { return centerLatitude; }
    qreal get_centerLongitude() { return centerLongitude; }
    QList<line_data> get_lines_list_data()
    {
        return linesList;
    }
    QList<text_data> get_text_list_data()
    {
        return textList;
    }
    void set_lines_list_data(QList<line_data>& l)
    {
        linesList = l;
    }
    void set_text_list_data(QList<text_data>& t)
    {
        textList = t;
    }
    void set_current_zoom(int zoom) { current_zoom = zoom; }
    void set_current_distance(int distance) { current_distance = distance; }
    void set_current_tileLevel(int tileLevel) { current_tileLevel = tileLevel; }
    void set_current_projection(Marble::Projection projection) { current_projection = projection; }
    void set_geoposition(QString position) { geoposition = position; }
    void set_unit_click_lat(qreal lat) { unit_click_lat = lat; }
    void set_unit_click_lon(qreal lon) { unit_click_lon = lon; }
    void set_centerLatitude(qreal lat) { centerLatitude = lat; }
    void set_centerLongitude(qreal lon) { centerLongitude = lon; }

private:
    QList<line_data> linesList;
    QList<text_data> textList;

    int current_zoom;
    int current_distance;
    int current_tileLevel;
    Marble::Projection current_projection;
    QString geoposition;
    qreal unit_click_lat, unit_click_lon, centerLongitude, centerLatitude;
};

#endif // SCRIBBLE_MANAGER_H
