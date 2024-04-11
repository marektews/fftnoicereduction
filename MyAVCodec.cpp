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
            if(avcodec_open2(m_pCodecContext, pCodec, nullptr) != -1)
            {
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
