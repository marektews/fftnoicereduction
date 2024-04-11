#ifndef MYAVPACKET_H
#define MYAVPACKET_H

#include <QObject>
extern "C" {
    #include <libavcodec/avcodec.h>
}

class MyAVPacket : public QObject
{
    Q_OBJECT
public:
    explicit MyAVPacket(QObject *parent = nullptr);
    ~MyAVPacket();

    operator AVPacket*() { return m_pPacket; }

private:
    AVPacket* m_pPacket = nullptr;
};

#endif // MYAVPACKET_H
