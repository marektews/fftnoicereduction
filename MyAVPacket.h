#ifndef MYAVPACKET_H
#define MYAVPACKET_H

extern "C" {
    #include <libavcodec/avcodec.h>
}

class MyAVPacket
{
public:
    explicit MyAVPacket();
    ~MyAVPacket();

    operator AVPacket*() { return m_pPacket; }

private:
    AVPacket* m_pPacket = nullptr;
};

#endif // MYAVPACKET_H
