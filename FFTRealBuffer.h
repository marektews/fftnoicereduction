#ifndef FFTREALBUFFER_H
#define FFTREALBUFFER_H

#include <fftw3.h>
#include <QObject>
#include <QSharedPointer>

class FFTRealBuffer : public QObject
{
    Q_OBJECT

public:
    using Ptr = QSharedPointer<FFTRealBuffer>;

    explicit FFTRealBuffer(size_t n, QObject *parent = nullptr);
    ~FFTRealBuffer();

    double* ptr() { return m_pBuffer; }

signals:

private:
    size_t      m_size = 0;
    double*     m_pBuffer = nullptr;
};

Q_DECLARE_METATYPE(FFTRealBuffer::Ptr);

#endif // FFTREALBUFFER_H
