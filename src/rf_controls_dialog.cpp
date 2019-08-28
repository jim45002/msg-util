#include <qwt_knob.h>
#include <qwt_thermo.h>
#include <qwt_round_scale_draw.h>
#include <qwt_math.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qfont.h>
#include <qpen.h>
#include <qevent.h>
#include <qwt_plot.h>

#include "rf_controls_dialog.h"
#include "ui_rf_controls_dialog.h"


class Knob: public QWidget
{
public:
    Knob( const QString &title, double min, double max, QWidget *parent ):
        QWidget( parent )
    {
        d_knob = new QwtKnob( this );
        d_knob->setScale( min, max );
        d_knob->setTotalSteps( 0 ); // disable
        d_knob->setScaleMaxMajor( 10 );

        d_knob->setKnobStyle( QwtKnob::Raised );
        d_knob->setKnobWidth( 150 );
        d_knob->setBorderWidth( 2 );
        d_knob->setMarkerStyle( QwtKnob::Notch );
        d_knob->setMarkerSize( 8 );

        d_knob->scaleDraw()->setTickLength( QwtScaleDiv::MinorTick, 4 );
        d_knob->scaleDraw()->setTickLength( QwtScaleDiv::MediumTick, 4 );
        d_knob->scaleDraw()->setTickLength( QwtScaleDiv::MajorTick, 6 );

        d_label = new QLabel( title, this );
        d_label->setFont(QFont(QString("New Times Roman"),16));

        d_label->setAlignment( Qt::AlignTop | Qt::AlignHCenter );

        setSizePolicy( QSizePolicy::Expanding,
            QSizePolicy::Expanding );
    }

    virtual QSize sizeHint() const
    {
        QSize sz1 = d_knob->sizeHint();
        QSize sz2 = d_label->sizeHint();

        const int w = qMax( sz1.width(), sz2.width() );
        const int h = sz1.height() + sz2.height();

        int off = qCeil( d_knob->scaleDraw()->extent( d_knob->font() ) );
        off -= 10; // spacing

        return QSize( w, h - off);
    }

    void setValue( double value )
    {
        d_knob->setValue( value );
    }

    double value() const
    {
        return d_knob->value();
    }

protected:
    virtual void resizeEvent( QResizeEvent *e )
    {
        const QSize sz = e->size();

        int h = d_label->sizeHint().height();

        d_label->setGeometry( 0, sz.height() - h, sz.width(), h );

        h = d_knob->sizeHint().height();
        int off = qCeil( d_knob->scaleDraw()->extent( d_knob->font() ) );
        off -= 10; // spacing

        d_knob->setGeometry( 0, d_label->pos().y() - h + off,
            sz.width(), h );
    }

private:
    QwtKnob *d_knob;
    QLabel *d_label;
};

rf_controls_dialog::rf_controls_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rf_controls_dialog)
{
    ui->setupUi(this);

    QwtPlot* plot = new QwtPlot(parent);
    plot->setAxisScale( QwtPlot::yLeft, -128,128 );
    plot->setAxisScale( QwtPlot::xBottom, 0.0, 128);
    plot->setFont(QFont("New Times Roman",11));
    plot->setAxisTitle(QwtPlot::xBottom,QString("Frequency"));
    plot->setAxisScale(QwtPlot::xBottom,-3000,3000);
    plot->setAxisScale(QwtPlot::yLeft,0,256);
    QVBoxLayout *layout = new QVBoxLayout( this );
    parent->setLayout(layout);
    layout->addWidget(plot);
    plot->show();

    QWidget* w = new QWidget(this);
    QHBoxLayout *widget_layout = new QHBoxLayout( w );
    w->setLayout(widget_layout);

    d_knbVolume = new Knob( "Volume", 0.0, 10.0, this );
    d_knbFreq = new Knob( "Frequency", 300.0, 3000.0, this );
    d_knbSquelch = new Knob( "Squelch", -10.0, 10.0, this );

    widget_layout->setSpacing( 0 );
    widget_layout->setMargin( 3 );
    widget_layout->addWidget( d_knbVolume );
    widget_layout->addSpacing( 3 );
    widget_layout->addStretch( 10 );
    widget_layout->addSpacing( 3 );
    widget_layout->addWidget( d_knbFreq );
    widget_layout->addSpacing( 3 );
    widget_layout->addStretch( 10 );
    widget_layout->addSpacing( 3 );
    widget_layout->addWidget( d_knbSquelch );
    widget_layout->addSpacing( 3 );
    widget_layout->addStretch( 10 );

    layout->addWidget(w);

    d_knbVolume->setValue( 7.0 );
}

rf_controls_dialog::~rf_controls_dialog()
{
    delete ui;
}
