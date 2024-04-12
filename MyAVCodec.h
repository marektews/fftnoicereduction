#ifndef MYAVCODEC_H
#define MYAVCODEC_H

#include <QObject>
extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
}

class MyAVCodec : public QObject
{
    Q_OBJECT

public:
    explicit MyAVCodec(QObject *parent = nullptr);
    explicit MyAVCodec(AVStream* pStream, QObject *parent = nullptr);
    ~MyAVCodec();

    int GetChannelsCount() const;
    uint64_t GetChannelLayout() const;
    int GetSampleRate() const;
    int GetSampleFormat() const;

    operator AVCodecContext*() { return m_pCodecContext; }

private:
    AVCodecContext* m_pCodecContext = nullptr;
};

#endif // MYAVCODEC_H
