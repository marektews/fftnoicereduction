#ifndef MYAVCODEC_H
#define MYAVCODEC_H

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
}

class MyAVCodec
{
public:
    explicit MyAVCodec();
    explicit MyAVCodec(AVStream* pStream);
    ~MyAVCodec();

    int GetChannelsCount() const;
    int GetSampleRate() const;
    AVChannelLayout GetChannelLayout() const;
    AVSampleFormat GetSampleFormat() const;

    operator AVCodecContext*() { return m_pCodecContext; }

private:
    AVCodecContext* m_pCodecContext = nullptr;
};

#endif // MYAVCODEC_H
