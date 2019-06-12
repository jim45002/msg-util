
#include <QPainter>
#include <QPaintEngine>
#include <QPixelFormat>

#include "detect_filter.h"

cv::CascadeClassifier classifier;

QVideoFilterRunnable* object_detect_filter::createFilterRunnable()
{
    return new detect_filter_runnable(this);
}

QVideoFrame detect_filter_runnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    Q_UNUSED(flags);
    input->map(QAbstractVideoBuffer::ReadOnly);

    if(surfaceFormat.handleType() == QAbstractVideoBuffer::NoHandle)
    {
        QByteArray frame_bytes;
        frame_bytes.resize((input->width()*input->height())*sizeof(uint32_t));

        yv12_to_rgb32(input->bits(),
                            frame_bytes.data(),
                            input->width(),
                            input->height());


        QImage image(reinterpret_cast<uchar*>(frame_bytes.data()),
                     input->width(),
                     input->height(),
                     QImage::Format_RGB32);

        if(image.width() == 0)
        {
            qDebug() << "frame format type is "<< input->pixelFormat();
            return *input;
        }

        image = image.convertToFormat(QImage::Format_RGB888);

        cv::Mat mat(image.height(),
                         image.width(),
                         CV_8UC3,
                         image.bits(),
                         image.bytesPerLine());

        cv::flip(mat, mat, 0);

        if(classifier.empty())
        {
            QFile xml("./cars.xml");
            if(xml.open(QFile::ReadOnly | QFile::Text))
            {
                QTemporaryFile temp;
                if(temp.open())
                {
                    temp.write(xml.readAll());
                    temp.close();
                    if(classifier.load(temp.fileName().toStdString()))
                    {
                        qDebug() << "loaded classifier!";
                    }
                    else
                    {
                        qDebug() << "unable load classifier.";
                    }
                }
                else
                {
                    qDebug() << "unable open temp file.";
                }
            }
            else
            {
                qDebug() << "unable to open XML.";
            }
        }
        else
        {
            std::vector<cv::Rect> detected;

            QSize resized = image.size().scaled(320, 240, Qt::KeepAspectRatio);
            cv::resize(mat, mat, cv::Size(resized.width(), resized.height()));

            classifier.detectMultiScale(mat,
                                        detected,
                                        1.5,
                                        1);

            if(detected.size() > 0)
            {
                emit filter->objectDetected(float(detected[0].x) / float(mat.cols),
                        float(detected[0].y) / float(mat.rows),
                        float(detected[0].width) / float(mat.cols),
                        float(detected[0].height) / float(mat.rows));
            }
            else
            {
                emit filter->objectDetected(0.0,
                                            0.0,
                                            0.0,
                                            0.0);
            }
        }
    }
    else
    {
        qDebug() << "format not supported";
    }

    input->unmap();

    return *input;
}


void yuv_420S_to_rgb32(const unsigned char* y,
                       const unsigned char* u,
                       const unsigned char* v,
                       int duv,
                       unsigned int* rgb,
                       int width,
                       int height)
{
    const unsigned char* u_pos = u;
    const unsigned char* v_pos = v;
    for (int ydex = 0;  ydex<height; ydex++) {
        for (int x = 0; x < width; x += 2, u += duv, v += duv) {
            const unsigned char nu = *u;
            const unsigned char nv = *v;
            *rgb = yuv_to_rgb32(*y, nu, nv);
            y++; rgb++;
            *rgb = yuv_to_rgb32(*y, nu, nv);
            y++; rgb++;
        }
        if (ydex & 0x1) {
            u_pos = u;
            v_pos = v;
        } else {
            u = u_pos;
            v = v_pos;
        }
    }
}
void yv12_to_rgb32(const void* yv12, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* Y = reinterpret_cast<const uint8_t*>(yv12);
    const uint8_t* V = Y + pix_total;
    const uint8_t* U = V + pix_total / 4;
    yuv_420S_to_rgb32(Y, U, V, 1, reinterpret_cast<uint32_t*>(rgb), width, height);
}
void yu12_to_rgb32(const void* yu12, void* rgb, int width, int height)
{
    const int pix_total = width * height;
    const uint8_t* Y = reinterpret_cast<const uint8_t*>(yu12);
    const uint8_t* U = Y + pix_total;
    const uint8_t* V = U + pix_total / 4;
    yuv_420S_to_rgb32(Y, U, V, 1, reinterpret_cast<uint32_t*>(rgb), width, height);
}

