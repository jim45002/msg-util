#ifndef PACKET_TYPES_H
#define PACKET_TYPES_H

enum packet_type : int { t_text = 16, t_voice = 32, t_markup = 64,
                         t_video = 128, t_image = 256, t_av_packet = 512,
                         t_recv_verified = 1024, t_send_error = 2048, t_recv_error = 4096,
                         t_text_verfication = 8092, t_voice_verfication = 16184, t_map_markup_verification = 22278,
                         t_recv_text_error = 44556, t_send_text_error = 49222, t_map_marpup_error = 68444,
                         t_recv_voice_error = 136888, t_send_voice_error = 273776
                       };


#endif // PACKET_TYPES_H
