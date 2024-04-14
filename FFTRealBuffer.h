#ifndef FFTREALBUFFER_H
#define FFTREALBUFFER_H

#include <fftw3.h>
#include <QObject>
#include <QSharedPointer>
#include "MyAVSamplesBuffer.h"

class FFTRealBuffer : public QObject
{
    Q_OBJECT

public:
    using Ptr = QSharedPointer<FFTRealBuffer>;

    explicit FFTRealBuffer(QObject *parent = nullptr);
    explicit FFTRealBuffer(size_t n, QObject *parent = nullptr);
    ~FFTRealBuffer();

    // void Append(const MyAVSamplesBuffer& avBuffer);

    double* data() { return m_pBuffer; }
    size_t GetDataSize() const { return m_size; }
    size_t GetBufferSize() const { return m_allocated; }
    size_t GetSamplesCount() const { return m_size / sizeof(double); }

private:
    double* alloc(size_t n);

private:
    size_t      m_allocated = 0;        // rozmiar pamięci zaalokowanej
    size_t      m_size = 0;             // rozmiar danych w buforze
    double*     m_pBuffer = nullptr;
};

Q_DECLARE_METATYPE(FFTRealBuffer::Ptr);

#endif // FFTREALBUFFER_H
