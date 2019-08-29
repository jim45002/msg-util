#ifndef RF_CONTROLS_DIALOG_H
#define RF_CONTROLS_DIALOG_H

#include <QDialog>

namespace Ui {
class rf_controls_dialog;
}

class FrequencyDisplayPlot;
class QwtPlot;;
class Knob;

class rf_controls_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit rf_controls_dialog(QWidget *parent = nullptr);
    ~rf_controls_dialog();

private:
    Ui::rf_controls_dialog *ui;
    Knob *d_knbVolume;
    Knob *d_knbFreq;
    Knob *d_knbSquelch;
    QwtPlot* qwt_plot;
    FrequencyDisplayPlot* freq_plot;
};

#endif // RF_CONTROLS_DIALOG_H
