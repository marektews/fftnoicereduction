#ifndef FFTPLAN_H
#define FFTPLAN_H

#include <fftw3.h>
#include <QObject>
#include <FFTRealBuffer.h>
#include <FFTComplexBuffer.h>

class FFTPlan : public QObject
{
    Q_OBJECT

public:
    explicit FFTPlan(QObject *parent = nullptr);
    ~FFTPlan();

    bool Create_R2C_1D(int n, FFTRealBuffer::Ptr in, FFTComplexBuffer::Ptr out, int flags = FFTW_MEASURE);
    bool Create_C2R_1D(int n, FFTComplexBuffer::Ptr in, FFTRealBuffer::Ptr out, int flags = FFTW_MEASURE);

    void Execute();

signals:

private:
    fftw_plan   m_plan = nullptr;
};

#endif // FFTPLAN_H
