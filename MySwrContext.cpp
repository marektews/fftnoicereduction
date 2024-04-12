#include "MySwrContext.h"

/**
 * @brief MySwrContext::MySwrContext
 * @param parent
 */
MySwrContext::MySwrContext(QObject *parent) : QObject{parent}
{
    m_pSwr = swr_alloc();
}

/**
 * @brief MySwrContext::~MySwrContext
 */
MySwrContext::~MySwrContext()
{
    if(m_pSwr)
        swr_free(&m_pSwr);
}

/**
 * @brief MySwrContext::SetChannelCount
 * @param in
 * @param out
 */
void MySwrContext::SetChannelCount(int in, int out)
{
    if(m_pSwr)
    {
        av_opt_set_int(m_pSwr, "in_channel_count", in, 0);
        av_opt_set_int(m_pSwr, "out_channel_count", out, 0);
    }
}

/**
 * @brief MySwrContext::SetChannelLayout
 * @param in
 * @param out
 */
void MySwrContext::SetChannelLayout(uint64_t in, uint64_t out)
{
    if(m_pSwr)
    {
        av_opt_set_int(m_pSwr, "in_channel_layout", in, 0);
        av_opt_set_int(m_pSwr, "out_channel_layout", out, 0);
    }
}

/**
 * @brief MySwrContext::SetSampleRate
 * @param in
 * @param out
 */
void MySwrContext::SetSampleRate(int in, int out)
{
    if(m_pSwr)
    {
        av_opt_set_int(m_pSwr, "in_sample_rate", in, 0);
        av_opt_set_int(m_pSwr, "out_sample_rate", out, 0);
    }
}

/**
 * @brief MySwrContext::SetSampleFormat
 * @param in
 * @param out
 */
void MySwrContext::SetSampleFormat(int in, int out)
{
    if(m_pSwr)
    {
        av_opt_set_int(m_pSwr, "in_sample_fmt", in, 0);
        av_opt_set_int(m_pSwr, "out_sample_fmt", out, 0);
    }
}

/**
 * @brief MySwrContext::Initialize
 * @return
 */
bool MySwrContext::Initialize()
{
    if(m_pSwr) swr_init(m_pSwr);
    return IsInitialized();
}

/**
 * @brief MySwrContext::IsInitialized
 * @return
 */
bool MySwrContext::IsInitialized() const
{
    return m_pSwr ? swr_is_initialized(m_pSwr) : false;
}
