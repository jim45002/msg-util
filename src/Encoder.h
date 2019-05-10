#ifndef DATACOMPRESSOR_H
#define DATACOMPRESSOR_H

#include <QObject>

class QDataStream;
class QByteArray;

class Encoder : public QObject
{
    Q_OBJECT
public:
    explicit Encoder(QDataStream& inputFrames, QObject *parent = 0);
    ~Encoder();
    const QByteArray& OutputBuffer() const { return outputBuffer; }
private:
    QByteArray outputBuffer;
};

#endif // DATACOMPRESSOR_H
