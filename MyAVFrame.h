#ifndef MYAVFRAME_H
#define MYAVFRAME_H

#include <QSharedPointer>
extern "C" {
    #include <libavcodec/avcodec.h>
}

class MyAVFrame
{
    friend class MySwrContext;

public:
    using Ptr = QSharedPointer<MyAVFrame>;

    explicit MyAVFrame();
    ~MyAVFrame();

    AVChannelLayout GetChannelLayout() const;
    void SetChannelLayout(AVChannelLayout ch_layout);

    int GetSampleRate() const;
    void SetSampleRate(int sample_rate);

    AVSampleFormat GetSampleFormat() const;
    void SetSampleFormat(AVSampleFormat format);

    uint8_t** GetSamplesData() const;
    size_t GetSamplesCount() const;

    operator AVFrame*() { return m_pFrame; }

protected:
    AVFrame* m_pFrame = nullptr;
};

#endif // MYAVFRAME_H
