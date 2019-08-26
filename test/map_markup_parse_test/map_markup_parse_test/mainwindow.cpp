
#include <QHBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "map_paint_layer.h"
#include "map_widget_interface.h"
#include "map_widget_factory.h"
#include "map_markup_post_interface.h"
#include "map_markup_post.h"

namespace {
   std::shared_ptr<map_widget_interface> mwfi = nullptr;
   map_markup_post_interface* mmpi = nullptr;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mwfi = map_widget_factory::create(this);
    mwfi->map_enable_scibble(true);
    auto l = new QHBoxLayout;
    ui->widget->setLayout(l);
    l->addWidget(mwfi->map_dispaly_widget());

    mmpi = new map_markup_post(mwfi.get());
    mmpi->set_data_location();

    mmpi->process_map_markup_data();

    auto text_list = mmpi->text_map_data();
    auto line_list = mmpi->lines_map_data();

    mwfi->get_map_widget_paint_layer()->
          get_scribble_manager()->
          set_lines_list_data(line_list);

    mwfi->get_map_widget_paint_layer()->
          get_scribble_manager()->
          set_text_list_data(text_list);

    mwfi->setZoom(mmpi->zoom());
    mwfi->centerOn(mmpi->center_lon(),mmpi->center_lat());

    mwfi->get_map_widget_paint_layer()->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
