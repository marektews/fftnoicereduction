#include <QDebug>
#include "MyAVFormatContext.h"

MyAVFormatContext::MyAVFormatContext()
{
    m_pFormat = avformat_alloc_context();
    if(m_pFormat == nullptr)
    {
        qDebug() << Q_FUNC_INFO << "AVFormatContext allocate error";
        return;
    }
}

/**
 * @brief MyAVFormatContext::~MyAVFormatContext
 */
MyAVFormatContext::~MyAVFormatContext()
{
    if(m_pFormat) avformat_free_context(m_pFormat);
}

/**
 * @brief MyAVFormatContext::OpenFile
 * @param filename
 * @return
 */
bool MyAVFormatContext::OpenFile(QString filename)
{
    if(avformat_open_input(&m_pFormat, filename.toStdString().c_str(), nullptr, nullptr) != 0)
    {
        qDebug() << Q_FUNC_INFO << "Could not open file:" << filename;
        return false;
    }

    if(avformat_find_stream_info(m_pFormat, nullptr) < 0)
    {
        qDebug() << Q_FUNC_INFO << "Could not retrieve stream info from file:" << filename;
        return false;
    }

    return true;
}

/**
 * @brief MyAVFormatContext::GetStream
 * @return
 */
AVStream* MyAVFormatContext::GetStream(AVMediaType mediaType)
{
    AVStream* pStream = nullptr;
    for(int i = 0; i < m_pFormat->nb_streams; ++i)
    {
        if(m_pFormat->streams[i]->codecpar->codec_type == mediaType)
        {
            pStream = m_pFormat->streams[i];
            break;
        }
    }
    if(pStream == nullptr)
        qDebug() << Q_FUNC_INFO << "Could not retrieve stream from file:" << m_pFormat->url;

    return pStream;
}
