#ifndef DECODER_H
#define DECODER_H

#include <QByteArray>
#include <QObject>

class QDataStream;

class Decoder : public QObject
{
    Q_OBJECT
public:
    explicit Decoder(QDataStream& inputFrames, QObject *parent = 0);
    ~Decoder();
    const QByteArray& OutputBuffer() const { return outputBuffer; }
private:
    QByteArray outputBuffer;
};

#endif // DECODER_H
