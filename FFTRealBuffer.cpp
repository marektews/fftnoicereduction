#include <cstring>
#include "FFTRealBuffer.h"

/**
 * @brief FFTRealBuffer::FFTRealBuffer
 * @param parent
 */
FFTRealBuffer::FFTRealBuffer(QObject* parent) : QObject{parent}
{}

/**
 * @brief FFTRealBuffer::FFTRealBuffer
 * @param n
 * @param parent
 */
FFTRealBuffer::FFTRealBuffer(size_t n, QObject *parent) : QObject{parent}, m_allocated{n}, m_size{0}
{
    m_pBuffer = alloc(n);
}

/**
 * @brief FFTRealBuffer::~FFTRealBuffer
 */
FFTRealBuffer::~FFTRealBuffer()
{
    if(m_pBuffer) fftw_free(m_pBuffer);
}

/**
 * @brief FFTRealBuffer::Append
 * @param avBuffer
 */
// void FFTRealBuffer::Append(const MyAVSamplesBuffer& avBuffer)
// {
//     if(avBuffer.GetSamplesCount() + m_size > m_allocated)
//     {
//         size_t newSize = avBuffer.GetSamplesCount() * 2 + m_allocated;
//         double* pTmp = alloc(newSize);
//         if(pTmp)
//         {
//             m_allocated = newSize;
//             if(m_pBuffer)
//             {
//                 std::memcpy(pTmp, m_pBuffer, sizeof(double) * m_size);
//                 fftw_free(m_pBuffer);
//             }
//             m_pBuffer = pTmp;
//         }
//     }

//     std::memcpy(m_pBuffer + sizeof(double) * m_size, avBuffer.m_pp[0], sizeof(double) * avBuffer.m_samples);
//     m_size += avBuffer.m_samples;
// }

/**
 * @brief FFTRealBuffer::alloc
 * @param n
 */
double* FFTRealBuffer::alloc(size_t n)
{
    return fftw_alloc_real(n);
}
