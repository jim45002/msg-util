#include "incoming_av_data_sync.h"

incoming_av_data_sync::incoming_av_data_sync(QObject* parent)
    : incoming_av_data_sync_interface (parent)
{

}

incoming_av_data_sync::~incoming_av_data_sync()
{

}

void incoming_av_data_sync::set_identifier(int id)
{
    identifier = id;
}

void incoming_av_data_sync::set_audio_filename(QString)
{

}

void incoming_av_data_sync::set_video_filename(QString)
{

}

QString incoming_av_data_sync::get_video_filename()
{

}

QString incoming_av_data_sync::get_audio_filename()
{

}
