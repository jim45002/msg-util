#ifndef MESSENGER_DIALOG_H
#define MESSENGER_DIALOG_H

#include <memory>

#include <qwt_plot_curve.h>

#include <QFile>
#include <QDialog>

class QMutex;
class QwtPlot;
class QFile;
class QListWidget;
class QTimer;
class QGraphicsScene;
class QListWidgetItem;

class camera_device_interface;
class camera_widget_interface;
class map_widget_interface;
class tor_config_options_interface;
class audio_buffer_device;
class data_transmitter;
class data_receiver_interface;
class audio_file_player_thread;
class data_transmitter_factory_interface;
class data_transmitter_interface;
class rf_controls_dialog;


namespace Ui {
class messenger_dialog;
}


class messenger_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit messenger_dialog(std::shared_ptr<data_transmitter_factory_interface> dtfi,
            data_receiver_interface* dri,
            QWidget *parent = nullptr
            );
    ~messenger_dialog();

    QwtPlot *create_plot_widget(QWidget *);
    void clear_outgoing_plot();
    void clear_incoming_plot();
    void save_map_markup();
    void save_image_data(QString selected_image_file);

public slots:
    void image_transmit_button_clicked(bool);
    void add_image_pushButton_clicked(bool);
    void voice_transmit_button_pressed();
    void voice_transmit_button_released();
    void text_transmit_button_pressed();
    void text_transmit_button_released();
    void timer_timedout();
    void enable_scribble_clicked(bool);
    void insert_connections_button(bool);
    void transmit_sribble_clicked(bool);

    void next_image_pushButton_clicked(bool);
    void image_remove_button_clicked(bool);
    void image_clear_button_clicked(bool);
    void video_transmit_button_released();
    void video_transmit_button_pressed();
    void video_off_button_clicked(bool);
    void video_on_button_clicked(bool);
    void stream1_start_push_button_clicked(bool);
    void stream1_stop_push_button_clicked(bool);
    void freq_slider_moved(int val);
    void radio_button_clicked(bool);
    void on_recv_data_error(QString);
    void on_send_verification(QString);
    void on_send_completed(QString);
    void on_rf_control_button_clicked(bool);
    void on_show_views_clicked(bool);
    void on_view_list_clicked(QListWidgetItem *);
    void on_map_markup_page_enable_scribble_checkbox(bool);
    void on_map_markup_page_transmit_button(bool b);
    void on_radio_button_op25(bool);
private:
    unsigned short int current_graphics_scene_index;
    Ui::messenger_dialog *ui;
    std::shared_ptr<camera_device_interface> cdi;
    std::shared_ptr<camera_widget_interface> cwi;
    std::shared_ptr<camera_widget_interface> csi;
    std::shared_ptr<data_transmitter_factory_interface> data_trans_f_inter;
    data_receiver_interface*  data_recv_inter;
    QList<data_transmitter_interface*> data_trans_list;
    QList<QGraphicsScene*> graphics_scene_list;
    std::shared_ptr<map_widget_interface> mwfi;
    std::shared_ptr<map_widget_interface> streams_mwfi;
    std::shared_ptr<map_widget_interface>  large_mwfi;
    std::shared_ptr<audio_buffer_device> audio_buffer;
    std::shared_ptr<audio_buffer_device> incoming_audio_buffer;
    std::shared_ptr<audio_file_player_thread> aud_file_player_thread;
    QwtPlot* incoming_plot;
    QwtPlot* outgoing_plot;
    QwtPlotCurve curve;
    QFile incoming_voice_file;
    QTimer* timer;
    rf_controls_dialog* rf_controls;

};

#endif // MESSENGER_DIALOG_H
