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

    template<typename T> T GetSample(int channel, size_t offset)
    {
        Q_ASSERT(channel < 8);
        if(av_sample_fmt_is_planar(AVSampleFormat(m_pFrame->format)) == 1)
        {
            // planar
            T* p = (T*)m_pFrame->data[channel];
            return p[offset];
        }
        else
        {
            T* p = (T*)m_pFrame->data[0];
            return p[offset * m_pFrame->ch_layout.nb_channels];
        }
    }

    uint8_t** GetSamplesData() const;
    size_t GetSamplesCount() const;

    operator AVFrame*() { return m_pFrame; }

protected:
    AVFrame* m_pFrame = nullptr;
};

#endif // MYAVFRAME_H
