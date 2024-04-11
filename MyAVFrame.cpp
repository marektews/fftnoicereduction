#include "MyAVFrame.h"

/**
 * @brief MyAVFrame::MyAVFrame
 * @param parent
 */
MyAVFrame::MyAVFrame(QObject *parent) : QObject{parent}
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
