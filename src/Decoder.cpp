#include "Decoder.h"
#include <speex/speex.h>
#include <QDataStream>
#include <QByteArray>
#include <QDebug>

Decoder::Decoder(QDataStream& inputFrames, QObject *parent) :
    QObject(parent)
{
    qDebug() << "started decoding ";

    int frameSize;

    inputFrames.readRawData(reinterpret_cast<char*>(&frameSize),sizeof(int));

    qDebug() << " frame size is : " << frameSize;

    //Holds the audio that will be written to file (16 bits per sample)
    QVector<short int> out;
    out.resize(frameSize);

    //Speex handle samples as float, so we need an array of floats
    QVector<float> output;
    output.resize(frameSize);

    QVector<char> cbits;
    cbits.resize(frameSize*1);

    //Holds the state of the decoder
    void *state;

    // Create a new decoder state in narrowband mode
    state = speex_decoder_init(&speex_nb_mode);

    // Set the perceptual enhancement on
    int tmp=1;
    speex_decoder_ctl(state, SPEEX_SET_ENH, &tmp);

    // Holds bits so they can be read and written to by the Speex routines
    SpeexBits bits;
    // Initialization of the structure that holds the bits
    speex_bits_init(&bits);

    int nbBytes;

    while(1)
    {
        //Read the size encoded by sampleenc, this part will likely be
        //different in your application

        inputFrames.readRawData(reinterpret_cast<char*>(&nbBytes),sizeof(int));

        if (inputFrames.atEnd() || !nbBytes)
        {
          qDebug() <<  " nbBytes != 38" << nbBytes;
          break;
        }

        //Read the "packet" encoded by sampleenc
        inputFrames.readRawData(cbits.data(),nbBytes);

        //Copy the data into the bit-stream struct
        speex_bits_read_from(&bits, cbits.data(), nbBytes);

        //Decode the data
        speex_decode(state, &bits, output.data());

        //Copy from float to short (16 bits) for output
        for (int i=0;i<frameSize;i++)
                    out[i]=output[i];

        //Write the decoded audio to file
        outputBuffer.append(reinterpret_cast<char*>(out.data()),
                            sizeof(short int)*frameSize);
    }

    //Destroy the decoder state
    speex_decoder_destroy(state);

    //Destroy the bit-stream struct
    speex_bits_destroy(&bits);

    qDebug() << "completed decoding";
}

//////////////////////////////////////////////////
Decoder::~Decoder()
{

}
