#ifndef DETECT_FILTER_H
#define DETECT_FILTER_H

#include <QAbstractVideoFilter>
#include <QDebug>
#include <QTemporaryFile>

#include <opencv2/opencv.hpp>

typedef union RGB32_t {
    uint32_t    color;
    struct {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint8_t r; uint8_t g; uint8_t b; uint8_t a;
#else   // __BYTE_ORDER
        uint8_t a; uint8_t b; uint8_t g; uint8_t r;
#endif
    };
} RGB32_t;


static __inline__ int
clamp(int x)
{
    if (x > 255) return 255;
    if (x < 0)   return 0;
    return x;
}

#define YUV2RO(C, D, E) clamp((298 * (C) + 409 * (E) + 128) >> 8)
#define YUV2GO(C, D, E) clamp((298 * (C) - 100 * (D) - 208 * (E) + 128) >> 8)
#define YUV2BO(C, D, E) clamp((298 * (C) + 516 * (D) + 128) >> 8)

#define YUV2R(y, u, v) clamp((298 * ((y)-16) + 409 * ((v)-128) + 128) >> 8)
#define YUV2G(y, u, v) clamp((298 * ((y)-16) - 100 * ((u)-128) - 208 * ((v)-128) + 128) >> 8)
#define YUV2B(y, u, v) clamp((298 * ((y)-16) + 516 * ((u)-128) + 128) >> 8)

static __inline__ uint32_t
yuv_to_rgb32(int y, int u, int v)
{
    y -= 16; u -= 128; v -= 128;
    RGB32_t rgb;
    rgb.r = YUV2RO(y,u,v) & 0xff;
    rgb.g = YUV2GO(y,u,v) & 0xff;
    rgb.b = YUV2BO(y,u,v) & 0xff;
    return rgb.color;
}


void yv12_to_rgb32(const void* yv12, void* rgb, int width, int height);
void yu12_to_rgb32(const void* yu12, void* rgb, int width, int height);


class object_detect_filter : public QAbstractVideoFilter
{
    Q_OBJECT
public:
    QVideoFilterRunnable *createFilterRunnable();

signals:
    void objectDetected(float x, float y, float w, float h);

public slots:

};

class detect_filter_runnable : public QVideoFilterRunnable
{
public:
    detect_filter_runnable(object_detect_filter *creator) {filter = creator;}
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);

private:
    void dft(cv::InputArray input, cv::OutputArray output);
    object_detect_filter *filter;
};

#endif // DETECT_FILTER_H
