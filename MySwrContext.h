#ifndef MYSWRCONTEXT_H
#define MYSWRCONTEXT_H

extern "C" {
    #include <libswresample/swresample.h>
    #include <libavutil/opt.h>
}
#include "MyAVFrame.h"
#include "MyAVSamplesBuffer.h"

class MySwrContext
{
public:
    explicit MySwrContext();
    explicit MySwrContext(const AVChannelLayout *out_ch_layout, AVSampleFormat out_sample_fmt, int out_sample_rate,
                          const AVChannelLayout *in_ch_layout, AVSampleFormat in_sample_fmt, int in_sample_rate);
    ~MySwrContext();

    void SetChannelCount(int in, int out);
    void SetChannelLayout(const AVChannelLayout& in, const AVChannelLayout& out);
    void SetSampleRate(int in, int out);
    void SetSampleFormat(AVSampleFormat in, AVSampleFormat out);

    bool Initialize();
    bool IsInitialized() const;

    int Convert(const MyAVFrame& inFrame, MyAVSamplesBuffer& outBuffer);
    int Convert(const MyAVFrame& inFrame, MyAVFrame& outFrame);

private:
    void report_error(int error, const char* funcInfo);

private:
    SwrContext* m_pSwr = nullptr;
};

#endif // MYSWRCONTEXT_H
