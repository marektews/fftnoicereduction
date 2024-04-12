#include <QDebug>
#include "MyAVCodec.h"

/**
 * @brief MyAVCodec::MyAVCodec
 * @param parent
 */
MyAVCodec::MyAVCodec(QObject* parent): QObject{parent}
{}

/**
 * @brief MyAVCodec::MyAVCodec
 * @param pFormat
 * @param parent
 */
MyAVCodec::MyAVCodec(AVStream* pStream, QObject *parent) : QObject{parent}
{
    const AVCodec* pCodec = avcodec_find_decoder(pStream->codecpar->codec_id);
    if(pCodec)
    {
        m_pCodecContext = avcodec_alloc_context3(pCodec);
        if(m_pCodecContext)
        {
            avcodec_parameters_to_context(m_pCodecContext, pStream->codecpar);
            av_channel_layout_default(&m_pCodecContext->ch_layout, pStream->codecpar->ch_layout.nb_channels);

            if(avcodec_open2(m_pCodecContext, pCodec, nullptr) != -1)
            {
                qDebug() << Q_FUNC_INFO << "Audio decoder opened:" << pCodec->name;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << "Could not open decoder:" << pCodec->name;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "Could not alloc decoder context:" << pCodec->name;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Could not find decoder from stream:" << pStream;
    }
}

/**
 * @brief MyAVCodec::~MyAVCodec
 */
MyAVCodec::~MyAVCodec()
{
    if(m_pCodecContext)
        avcodec_close(m_pCodecContext);
}

/**
 * @brief MyAVCodec::GetChannelsCount
 * @return
 */
int MyAVCodec::GetChannelsCount() const
{
    return m_pCodecContext ? m_pCodecContext->ch_layout.nb_channels : 0;
}

/**
 * @brief MyAVCodec::GetChannelLayout
 * @return
 */
uint64_t MyAVCodec::GetChannelLayout() const
{
    return m_pCodecContext ? m_pCodecContext->ch_layout.u.mask: 0;
}

/**
 * @brief MyAVCodec::GetSampleRate
 * @return
 */
int MyAVCodec::GetSampleRate() const
{
    return m_pCodecContext ? m_pCodecContext->sample_rate : 0;
}

/**
 * @brief MyAVCodec::GetSampleFormat
 * @return
 */
int MyAVCodec::GetSampleFormat() const
{
    return m_pCodecContext ? m_pCodecContext->sample_fmt : AV_SAMPLE_FMT_NONE;
}
