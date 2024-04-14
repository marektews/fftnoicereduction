#ifndef MYAVSAMPLESBUFFER_H
#define MYAVSAMPLESBUFFER_H

extern "C" {
    #include <libavutil/avutil.h>
    #include <libavcodec/avcodec.h>
}

class MyAVSamplesBuffer
{
    friend class MySwrContext;
    friend class FFTRealBuffer;

public:
    explicit MyAVSamplesBuffer();
    explicit MyAVSamplesBuffer(size_t samples, int channels, AVSampleFormat sampleFormat);
    ~MyAVSamplesBuffer();

    size_t GetSamplesCount() const { return m_samples; }

    int Prepare(size_t samples, int channels, AVSampleFormat sampleFormat);
    int CopyFrom(const MyAVSamplesBuffer& src);

    void Dump();

protected:
    int m_channels = 0;
    size_t  m_samples = 0;
    AVSampleFormat m_sampleFormat;
    uint8_t** m_pp = nullptr;
};

#endif // MYAVSAMPLESBUFFER_H
