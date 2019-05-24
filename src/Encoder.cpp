#include "Encoder.h"
#include <speex/speex.h>
#include <QDataStream>
#include <QByteArray>
#include <QDebug>

Encoder::Encoder(QDataStream& inputFrames, QObject *parent) :
    QObject(parent)
{
    qDebug() << "started encoding";

    /*Create a new encoder state in narrowband mode*/
    void *state = speex_encoder_init(&speex_nb_mode);

    int frameSize;
    speex_encoder_ctl(state,SPEEX_GET_FRAME_SIZE,&frameSize);

    QVector<float> input;
    input.resize(frameSize);

    QVector<short int> in;
    in.resize(frameSize);

    QVector<char> cbits;
    cbits.resize(frameSize*1);

    /*Set the quality to 8 (15 kbps)*/
    int tmp=8;
    speex_encoder_ctl(state, SPEEX_SET_QUALITY, &tmp);

    /*Initialization of the structure that holds the bits*/
    SpeexBits bits;
    speex_bits_init(&bits);

    outputBuffer.append(reinterpret_cast<char*>(&frameSize),sizeof(int));

    int nbBytes;

    while (1)
    {
        /* Read a 16 bits/sample audio frame */

        inputFrames.readRawData(reinterpret_cast<char*>(in.data()),
                                sizeof(short int)*frameSize);

        if(inputFrames.atEnd())
                           break;

        /*Copy the 16 bits values to float so Speex can work on them*/

        for (int i=0;i<frameSize;i++)
            input[i] = in[i];

        /*Flush all the bits in the struct so we can encode a new frame*/
        speex_bits_reset(&bits);

        /*Encode the frame*/
        speex_encode(state, input.data(), &bits);

        /*Copy the bits to an array of char that can be written*/
        nbBytes = speex_bits_write(&bits,cbits.data(),cbits.size());

        /*Write the size of the frame first. This is what sampledec expects */
        outputBuffer.append(reinterpret_cast<char*>(&nbBytes),sizeof(int));

        /*Write the compressed data*/
        outputBuffer.append(cbits.data(),nbBytes);
      }

      /*Destroy the encoder state*/
      speex_encoder_destroy(state);
      /*Destroy the bit-packing struct*/
      speex_bits_destroy(&bits);
      qDebug() << "completed encoding";
      return;
}

////////////////////////////////////////////////////
Encoder::~Encoder()
{

}
