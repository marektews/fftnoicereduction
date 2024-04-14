#include "MyAVPacket.h"

/**
 * @brief MyAVPacket::MyAVPacket
 * @param parent
 */
MyAVPacket::MyAVPacket()
{
    m_pPacket = av_packet_alloc();
}

/**
 * @brief MyAVPacket::~MyAVPacket
 */
MyAVPacket::~MyAVPacket()
{
    if(m_pPacket)
        av_packet_free(&m_pPacket);
}
