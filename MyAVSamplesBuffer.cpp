#include <QDebug>
#include <QtCore/QtAssert>
#include "MyAVSamplesBuffer.h"

/**
 * @brief MyAVSamplesBuffer::MyAVSamplesBuffer
 * @param parent
 */
MyAVSamplesBuffer::MyAVSamplesBuffer()
{}

/**
 * @brief MyAVSamplesBuffer::MyAVSamplesBuffer
 * @param channels
 * @param samples
 * @param sample_fmt
 * @param parent
 */
MyAVSamplesBuffer::MyAVSamplesBuffer(size_t samples, int channels, AVSampleFormat sampleFormat)
    : m_channels{channels}, m_samples{samples}, m_sampleFormat{sampleFormat}
{
    /*int res =*/ av_samples_alloc_array_and_samples(&m_pp, nullptr, channels, samples, sampleFormat, 0);
}

/**
 * @brief MyAVSamplesBuffer::~MyAVSamplesBuffer
 */
MyAVSamplesBuffer::~MyAVSamplesBuffer()
{
    if(m_pp)
    {
        av_freep(&m_pp[0]);
        av_freep(&m_pp);
    }
}

/**
 * @brief MyAVSamplesBuffer::Prepare
 * @param channels
 * @param samples
 * @param sampleFormat
 * @return
 */
int MyAVSamplesBuffer::Prepare(size_t samples, int channels, AVSampleFormat sampleFormat)
{
    m_channels = channels;
    m_samples = samples;
    m_sampleFormat = sampleFormat;
    int linesize = 0;
    int res = av_samples_alloc_array_and_samples(&m_pp, &linesize, channels, samples, sampleFormat, 0);
    return res;
}

/**
 * @brief MyAVSamplesBuffer::CopyFrom
 * @param src
 * @return
 */
int MyAVSamplesBuffer::CopyFrom(const MyAVSamplesBuffer& src)
{
    Q_ASSERT(m_channels == src.m_channels);
    Q_ASSERT(m_samples == src.m_samples);
    Q_ASSERT(m_sampleFormat == src.m_sampleFormat);
    return av_samples_copy(m_pp, src.m_pp, 0, 0, m_channels, m_samples, m_sampleFormat);
}

/**
 * @brief MyAVSamplesBuffer::Dump
 */
void MyAVSamplesBuffer::Dump()
{
    int planar = av_sample_fmt_is_planar(m_sampleFormat);

    double **p = (double**) m_pp;
    for(int ch = 0; ch < m_channels; ++ch)
    {
        QDebug dbg = qDebug();
        dbg << "Channel" << ch << ':';
        double* pch = p[ch];
        for(int i = 0; i < 8; ++i)
            dbg << pch[i] << '|';
    }
}
