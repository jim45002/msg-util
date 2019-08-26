#ifndef MAP_PAINT_LAYER_H
#define MAP_PAINT_LAYER_H

#include <memory>

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QFont>
#include <QColorDialog>
#include <QPaintEvent>
#include <QList>
#include <QLine>
#include <QPoint>
#include <QDebug>
#include <QInputDialog>
#include <QMenu>

class map_widget;
class scribble_manager;

class map_paint_layer : public QWidget
{
    Q_OBJECT

public:
    explicit map_paint_layer(map_widget *parent = nullptr);

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    bool isModified() const;
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    std::shared_ptr<scribble_manager> get_scribble_manager() { return scribble_mgr; }
    void penColor_dialog();
    void penWidth_dialog();
    void penText_dialog();
    void drawText(QString text, QPoint p, int width, QColor color, QFont font,
                  bool remember = true);
    void penFont_dialog();

public slots:
    void on_scribble_enable_triggered(bool checked );
    void on_scribble_save_triggered(bool checked );
    void on_scribble_color_triggered(bool checked);
    void on_scribble_size_triggered(bool checked);
    void on_scribble_erase_triggered(bool checked );
    void on_scribble_history_triggered(bool checked );
    void on_scribble_clear_triggered(bool checked);
    void on_scribble_text_triggered(bool checked);
    void on_scribble_font_triggered(bool checked);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    void drawLine(QLine line, int width, QColor color, bool remember = true);

    map_widget* parentWidget;

    int myPenWidth;
    bool modified;
    bool scribbling;
    QString map_text;
    QFont my_font;
    QColor myPenColor;
    QPoint lastPoint, last_right_click_point;

    std::shared_ptr<scribble_manager> scribble_mgr;

    std::shared_ptr<QMenu> map_layer_menu;
    QMenu* scribble_submenu;
    QAction* action_scribble_enable;
    QAction* action_scribble_font;
    QAction* action_scribble_clear;
    QAction* action_scribble_save;
    QAction* action_scribble_color;
    QAction* action_scribble_size;
    QAction* action_scribble_erase;
    QAction* action_scribble_text;
    QMenu*   menu_scribble_history;
    QAction* action_scribble_history;

};

#endif // MAP_PAINT_LAYER_H
