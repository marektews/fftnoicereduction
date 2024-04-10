#include <QDebug>
#include "MyAVFormatContext.h"

MyAVFormatContext::MyAVFormatContext(QObject *parent) : QObject{parent}
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

    ...

    return true;
}
