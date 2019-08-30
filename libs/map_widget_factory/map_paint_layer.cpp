
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QFontDialog>
#include "map_paint_layer.h"
#include "map_widget.h"
#include "scribble_manager.h"

map_paint_layer::map_paint_layer(map_widget *parent)
    : QWidget(parent),
      parentWidget(parent),
      myPenWidth (4),
      scribble_mgr(std::make_shared<scribble_manager>()),
      map_layer_menu(std::make_shared<QMenu>(this))
{
    QSizePolicy sizePolicy;
    sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);

    setContextMenuPolicy(Qt::CustomContextMenu);

    scribble_submenu = map_layer_menu->addMenu( "Scribble" );

    action_scribble_enable  = scribble_submenu->addAction( "Enable/Disable" );
    action_scribble_enable->setCheckable (true);
    action_scribble_enable->setChecked (true);
    action_scribble_clear = scribble_submenu->addAction( "Clear" );
    action_scribble_save = scribble_submenu->addAction( "Save" );
    action_scribble_color = scribble_submenu->addAction( "Pen Color" );
    action_scribble_size = scribble_submenu->addAction( "Pen Size" );
    action_scribble_erase = scribble_submenu->addAction( "Eraser Pen" );
    action_scribble_text = scribble_submenu->addAction( "Add Text" );
    action_scribble_font = scribble_submenu->addAction( "Set Font" );

    menu_scribble_history = scribble_submenu->addMenu( "History" );
    action_scribble_history = menu_scribble_history->addAction("Setup");

    QObject::connect(action_scribble_enable,SIGNAL(triggered(bool)),this,
                     SLOT(on_scribble_enable_triggered(bool)));
    QObject::connect(action_scribble_color,SIGNAL(triggered(bool)),this,
                     SLOT(on_scribble_color_triggered(bool)));
    QObject::connect(action_scribble_size,SIGNAL(triggered(bool)),this,
                     SLOT(on_scribble_size_triggered(bool)));
    QObject::connect(action_scribble_history,SIGNAL(triggered(bool)),this,
                     SLOT(on_scribble_history_triggered(bool)));
    QObject::connect(action_scribble_erase,SIGNAL(triggered(bool)),this,
                     SLOT(on_scribble_erase_triggered(bool)));
    QObject::connect(action_scribble_clear,SIGNAL(triggered(bool)),this,
                     SLOT(on_scribble_clear_triggered(bool)));
    QObject::connect(action_scribble_text,SIGNAL(triggered(bool)),this,
                     SLOT(on_scribble_text_triggered(bool)));
    QObject::connect(action_scribble_font,SIGNAL(triggered(bool)),this,
                     SLOT(on_scribble_font_triggered(bool)));
}

void map_paint_layer::penText_dialog()
{
   bool ok;
   QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                        tr("Enter text"), QLineEdit::Normal,
                                        "", &ok);
   if (ok && !text.isEmpty())
   {
       drawText(text,last_right_click_point,myPenWidth,myPenColor,my_font);

   }
}

void map_paint_layer::penFont_dialog()
{
    bool ok;
    my_font = QFontDialog::getFont(
                    &ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
        // the user clicked OK and font is set to the font the user selected
    } else {
        // the user canceled the dialog; font is set to the initial
        // value, in this case Helvetica [Cronyx], 10
    }
}

void map_paint_layer::penWidth_dialog()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        myPenWidth = newWidth;
}

void map_paint_layer::penColor_dialog()
{
   QColor newColor = QColorDialog::getColor(penColor());
   if (newColor.isValid())
         myPenColor = newColor;
}

void map_paint_layer::on_scribble_font_triggered(bool checked)
{
    penFont_dialog();
}

void map_paint_layer::on_scribble_color_triggered(bool checked)
{
    penColor_dialog();
}

void map_paint_layer::on_scribble_text_triggered(bool checked)
{
    penText_dialog();
}

void map_paint_layer::on_scribble_size_triggered(bool checked)
{
    penWidth_dialog();
}

void map_paint_layer::on_scribble_erase_triggered(bool checked)
{

}

void map_paint_layer::on_scribble_history_triggered(bool checked)
{

}

void map_paint_layer::on_scribble_clear_triggered(bool checked)
{
    scribble_mgr->clear();
    repaint ();
}

void map_paint_layer::on_scribble_enable_triggered(bool checked)
{
    if(false == checked)
    {
        this->hide ();
    }
    else
    {
        this->show ();
    }
}

void map_paint_layer::on_scribble_save_triggered(bool checked)
{

}

void map_paint_layer::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

bool map_paint_layer::isModified() const
{
    return modified;
}

void map_paint_layer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawRect(dirtyRect);
    const QList<scribble_manager::line_data> l_data = scribble_mgr->get_lines ();
    const QList<scribble_manager::text_data> t_data = scribble_mgr->get_text ();

    for(auto l : l_data)
    {
       drawLine(l.get_line(),l.get_width(),l.get_color(),false);
    }
    for(auto t : t_data)
    {
       drawText(t.get_text(),t.get_point(),t.get_width(),t.get_color(),t.get_font (),false);
    }
}

void map_paint_layer::resizeEvent(QResizeEvent *event)
{
   QWidget::resizeEvent(event);
}

void map_paint_layer::drawLine(QLine line, int width, QColor color, bool remember)
{
    if(remember)
    {
        scribble_mgr->add_line (width,color,line);
        modified = true;
    }

     QPainter painter(this);
     QPen pen;
     pen.setWidth (width);
     pen.setColor (color);
     painter.setPen(pen);

     qreal center_lat = parentWidget->centerLatitude();
     qreal center_lon = parentWidget->centerLongitude();

     qreal x, y;
     parentWidget->screenCoordinates(center_lon,center_lat,x,y);

     QLine workLine(QPoint(line.p1().x()+x,line.p1().y()+y), QPoint(line.p2().x()+x,line.p2().y()+y));
     line.p1().setX(line.p1().x()+x);
     line.p1().setY(line.p1().y()+y);

     line.p2().setX(line.p2().x()+x);
     line.p2().setY(line.p2().y()+y);

     painter.drawLine(workLine);

     int rad = (myPenWidth / 2) + 2;
     update(QRect(workLine.p1 (), workLine.p2 ()).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));

}

void map_paint_layer::drawText(QString text, QPoint p, int width, QColor color, QFont font, bool remember)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth (width);
    pen.setColor (color);
    painter.setPen(pen);
    painter.setFont (font);
   // painter.drawText (p,text);

    if(remember)
       scribble_mgr->add_text (text,p,width,color,font);

    modified = true;

    update();
}


void map_paint_layer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();
        qreal lat=0,  lon=0;
        if(parentWidget->geoCoordinates(lastPoint.x(), lastPoint.y(), lon, lat))
        {
        }
        else
        {
        }
        scribbling = true;
    }
    else
    {
        if (event->button() == Qt::RightButton)
        {
            last_right_click_point = event->pos();
            map_layer_menu->exec(mapToGlobal(event->pos()));
        }
    }
}

void map_paint_layer::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void map_paint_layer::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
    {
        qreal center_lat = parentWidget->centerLatitude();
        qreal center_lon = parentWidget->centerLongitude();
        qreal x, y;
        parentWidget->screenCoordinates(center_lon,center_lat,x,y);

        QPoint curr = event->pos();

        curr.setX(curr.x()-x);
        curr.setY(curr.y()-y);

        lastPoint.setX(lastPoint.x()-x);
        lastPoint.setY(lastPoint.y()-y);

        drawLine(QLine(lastPoint,curr),myPenWidth,myPenColor);

        lastPoint = event->pos();
    }
    QWidget::mouseMoveEvent (event);
}

void map_paint_layer::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
    {
        qreal center_lat = parentWidget->centerLatitude();
        qreal center_lon = parentWidget->centerLongitude();

        qreal x, y;
        parentWidget->screenCoordinates(center_lon,center_lat,x,y);

        QPoint curr = event->pos();
        curr.setX(curr.x()-x);
        curr.setY(curr.y()-y);

        lastPoint.setX(lastPoint.x()-x);
        lastPoint.setY(lastPoint.y()-y);

        drawLine(QLine(lastPoint,curr),myPenWidth,myPenColor);

        lastPoint = event->pos();
    }
}
