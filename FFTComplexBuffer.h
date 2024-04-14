#ifndef FFTCOMPLEXBUFFER_H
#define FFTCOMPLEXBUFFER_H

#include <fftw3.h>
#include <QObject>
#include <QSharedPointer>

class FFTComplexBuffer : public QObject
{
    Q_OBJECT

public:
    using Ptr = QSharedPointer<FFTComplexBuffer>;

    explicit FFTComplexBuffer(size_t n, QObject *parent = nullptr);
    ~FFTComplexBuffer();

    fftw_complex* data() { return m_pBuffer; }
    size_t GetDataSize() const { return m_size; }

signals:

private:
    size_t          m_size = 0;
    fftw_complex*   m_pBuffer = nullptr;
};

#endif // FFTCOMPLEXBUFFER_H
