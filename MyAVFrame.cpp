#include "MyAVFrame.h"

/**
 * @brief MyAVFrame::MyAVFrame
 * @param parent
 */
MyAVFrame::MyAVFrame()
{
    m_pFrame = av_frame_alloc();
}

/**
 * @brief MyAVFrame::~MyAVFrame
 */
MyAVFrame::~MyAVFrame()
{
    if(m_pFrame)
        av_frame_free(&m_pFrame);
}

/**
 * @brief MyAVFrame::GetChannelLayout
 * @return
 */
AVChannelLayout MyAVFrame::GetChannelLayout() const
{
    return m_pFrame ? m_pFrame->ch_layout : AVChannelLayout();
}

/**
 * @brief MyAVFrame::SetChannelLayout
 * @param ch_layout
 */
void MyAVFrame::SetChannelLayout(AVChannelLayout ch_layout)
{
    if(m_pFrame)
        m_pFrame->ch_layout = ch_layout;
}

/**
 * @brief MyAVFrame::GetSampleRate
 * @return
 */
int MyAVFrame::GetSampleRate() const
{
    return m_pFrame ? m_pFrame->sample_rate : 0;
}

/**
 * @brief MyAVFrame::SetSampleRate
 * @param sample_rate
 */
void MyAVFrame::SetSampleRate(int sample_rate)
{
    if(m_pFrame)
        m_pFrame->sample_rate = sample_rate;
}

/**
 * @brief MyAVFrame::GetSampleFormat
 * @return
 */
AVSampleFormat MyAVFrame::GetSampleFormat() const
{
    return m_pFrame ? AVSampleFormat(m_pFrame->format) : AV_SAMPLE_FMT_NONE;
}

/**
 * @brief MyAVFrame::SetSampleFormat
 * @param format
 */
void MyAVFrame::SetSampleFormat(AVSampleFormat format)
{
    if(m_pFrame)
        m_pFrame->format = format;
}

/**
 * @brief MyAVFrame::GetSamplesData
 * @return
 */
uint8_t** MyAVFrame::GetSamplesData() const
{
    return m_pFrame ? m_pFrame->data : nullptr;
}

/**
 * @brief MyAVFrame::GetSamplesCount
 * @return Liczba sampli lub zero.
 */
size_t MyAVFrame::GetSamplesCount() const
{
    return m_pFrame ? m_pFrame->nb_samples : 0;
}
