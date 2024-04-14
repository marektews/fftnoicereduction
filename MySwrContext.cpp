#include <QDebug>
#include "MySwrContext.h"

/**
 * @brief MySwrContext::MySwrContext
 * @param parent
 */
MySwrContext::MySwrContext()
{
    m_pSwr = swr_alloc();
}

MySwrContext::MySwrContext(const AVChannelLayout *out_ch_layout, AVSampleFormat out_sample_fmt, int out_sample_rate,
                           const AVChannelLayout *in_ch_layout, AVSampleFormat in_sample_fmt, int in_sample_rate)
{
    int res = swr_alloc_set_opts2(&m_pSwr,
                                  out_ch_layout, out_sample_fmt, out_sample_rate,
                                  in_ch_layout, in_sample_fmt, in_sample_rate, 0, nullptr);
    if(res != 0) report_error(res, Q_FUNC_INFO);
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
        int res = av_opt_set_int(m_pSwr, "in_channel_count", in, 0);
        if(res != 0) report_error(res, Q_FUNC_INFO);
        res = av_opt_set_int(m_pSwr, "out_channel_count", out, 0);
        if(res != 0) report_error(res, Q_FUNC_INFO);
    }
}

/**
 * @brief MySwrContext::SetChannelLayout
 * @param in
 * @param out
 */
void MySwrContext::SetChannelLayout(const AVChannelLayout& in, const AVChannelLayout& out)
{
    if(m_pSwr)
    {
        int res = av_opt_set_chlayout(m_pSwr, "in_chlayout", &in, 0);
        if(res != 0) report_error(res, Q_FUNC_INFO);
        res = av_opt_set_chlayout(m_pSwr, "out_chlayout", &out, 0);
        if(res != 0) report_error(res, Q_FUNC_INFO);
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
        int res = av_opt_set_int(m_pSwr, "in_sample_rate", in, 0);
        if(res != 0) report_error(res, Q_FUNC_INFO);
        res = av_opt_set_int(m_pSwr, "out_sample_rate", out, 0);
        if(res != 0) report_error(res, Q_FUNC_INFO);
    }
}

/**
 * @brief MySwrContext::SetSampleFormat
 * @param in
 * @param out
 */
void MySwrContext::SetSampleFormat(AVSampleFormat in, AVSampleFormat out)
{
    if(m_pSwr)
    {
        int res = av_opt_set_sample_fmt(m_pSwr, "in_sample_fmt", in, 0);
        if(res != 0) report_error(res, Q_FUNC_INFO);
        res = av_opt_set_sample_fmt(m_pSwr, "out_sample_fmt", out, 0);
        if(res != 0) report_error(res, Q_FUNC_INFO);
    }
}

/**
 * @brief MySwrContext::Initialize
 * @return
 */
bool MySwrContext::Initialize()
{
    if(m_pSwr)
    {
        int err = swr_init(m_pSwr);
        if(err != 0)
            report_error(err, Q_FUNC_INFO);
    }
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

/**
 * @brief MySwrContext::Convert
 * @param inFrame
 * @param pOutBuffer
 * @return -1 w wypadku błędu lub liczba sampli na kanał
 */
int MySwrContext::Convert(const MyAVFrame& inFrame, MyAVSamplesBuffer& outBuffer)
{
    if(m_pSwr)
        return swr_convert(m_pSwr, outBuffer.m_pp, outBuffer.m_samples, inFrame.GetSamplesData(), inFrame.GetSamplesCount());
    else
        return -1;
}

/**
 * @brief MySwrContext::Convert
 * @param inFrame
 * @param outBuffer
 * @return
 */
int MySwrContext::Convert(const MyAVFrame& inFrame, MyAVFrame& outFrame)
{
    if(m_pSwr)
    {
        int res = swr_convert_frame(m_pSwr, outFrame.m_pFrame, inFrame.m_pFrame);
        if(res != 0)
            report_error(res, Q_FUNC_INFO);
        return res;
    }
    else
        return -1;
}

/**
 * @brief MySwrContext::report_error
 * @param error
 * @param funcInfo
 */
void MySwrContext::report_error(int error, const char* funcInfo)
{
    char tmp[512];
    av_strerror(error, tmp, 512);
    qDebug() << funcInfo << tmp;
}
