#include "FFTRealBuffer.h"

/**
 * @brief FFTRealBuffer::FFTRealBuffer
 * @param n
 * @param parent
 */
FFTRealBuffer::FFTRealBuffer(size_t n, QObject *parent) : QObject{parent}, m_size(n)
{
    m_pBuffer = fftw_alloc_real(n);
}

/**
 * @brief FFTRealBuffer::~FFTRealBuffer
 */
FFTRealBuffer::~FFTRealBuffer()
{
    fftw_free(m_pBuffer);
}
