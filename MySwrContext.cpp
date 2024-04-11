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

void MySwrContext::SetChannelLayout(unsigned long long in, unsigned long long out)
{

}

void MySwrContext::SetSampleRate(int in, int out)
{

}

/**
 * @brief MySwrContext::IsInitialized
 * @return
 */
bool MySwrContext::IsInitialized() const
{
    return m_pSwr ? swr_is_initialized(m_pSwr) : false;
}
