#ifndef PACKET_TYPES_H
#define PACKET_TYPES_H

enum packet_type : int { t_text = 16, t_voice = 32, t_markup = 64,
                         t_video = 128, t_image = 256, t_av_packet = 512,
                         t_recv_verified = 1024, t_send_error = 2048, t_recv_error = 4096 };


#endif // PACKET_TYPES_H
