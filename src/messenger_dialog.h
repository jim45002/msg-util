#ifndef MESSENGER_DIALOG_H
#define MESSENGER_DIALOG_H

#include <memory>

#include <QFile>
#include <QDialog>

class QwtPlot;
class QFile;
class QListWidget;
class map_widget_interface;
class tor_config_options_interface;
class audio_buffer_device;
class data_transmitter;
class data_receiver_interface;
class audio_file_player_thread;
class QMutex;

namespace Ui {
class messenger_dialog;
}

class QTimer;

class messenger_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit messenger_dialog(QWidget *parent = nullptr);
    ~messenger_dialog();

    QwtPlot *create_plot_widget(QWidget *);
public slots:
    void voice_transmit_button_pressed();
    void voice_transmit_button_released();
    void text_transmit_button_pressed();
    void text_transmit_button_released();
    void timer_timedout();

    void enable_scribble_clicked(bool);
private:
    Ui::messenger_dialog *ui;    
    QList<data_transmitter*> data_trans_list;
    std::shared_ptr<data_receiver_interface> data_recv_inter;
    std::shared_ptr<map_widget_interface> mwfi;
    std::shared_ptr<audio_buffer_device> audio_buffer;
    std::shared_ptr<audio_buffer_device> incoming_audio_buffer;
    std::shared_ptr<audio_file_player_thread> audio_file_thread;
    QwtPlot* incoming_plot;
    QwtPlot* outgoing_plot;
    QFile incoming_voice_file;

};

#endif // MESSENGER_DIALOG_H
