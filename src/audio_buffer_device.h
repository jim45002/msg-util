#ifndef AUDIO_BUFFER_DEVICE_H
#define AUDIO_BUFFER_DEVICE_H

#include <memory>

#include <QDoubleSpinBox>
#include <QIODevice>
#include <QFile>

#include <qwt_plot_curve.h>

class QAudioInput;
class QwtPlot;

class audio_read_thread;

class audio_buffer_device : public QIODevice
{
    Q_OBJECT
public:
    audio_buffer_device(QwtPlot* plot,
                        QDoubleSpinBox* outgoing_spinbox,
                        QDoubleSpinBox* incoming_spinbox,
                        QObject *parent);

    virtual ~audio_buffer_device();

    virtual bool  open(OpenMode mode);
    virtual void  close();
    virtual qint64 writeData(const char *data, qint64 maxSize);
    virtual qint64 readData(char *data, qint64 maxSize);
    virtual qint64 readLineData(char *, qint64);

    void stop_audio_write();
    void save_voice_message();

    void start_audio_read();

public slots:
    void new_buffer_data(char* data, qint64 maxLen);

private:
    std::shared_ptr<QAudioInput> audio_input_ptr;
    std::shared_ptr<audio_read_thread> audio_reader;
    QwtPlot* plot_widget;
    QwtPlotCurve curve;
    QDoubleSpinBox* in_spinbox;
    QDoubleSpinBox* out_spinbox;
    QByteArray audio_data;
    double average;
    double sum;
    double counter;
    const unsigned int data_size;
};

#endif // AUDIO_BUFFER_DEVICE_H
