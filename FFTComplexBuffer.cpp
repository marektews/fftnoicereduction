#include "FFTComplexBuffer.h"

/**
 * @brief FFTComplexBuffer::FFTComplexBuffer
 * @param n
 * @param parent
 */
FFTComplexBuffer::FFTComplexBuffer(size_t n, QObject *parent) : QObject{parent}, m_size(n)
{
    m_pBuffer = fftw_alloc_complex(n);
}

/**
 * @brief FFTComplexBuffer::~FFTComplexBuffer
 */
FFTComplexBuffer::~FFTComplexBuffer()
{
    fftw_free(m_pBuffer);
}
