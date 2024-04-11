#ifndef MYSWRCONTEXT_H
#define MYSWRCONTEXT_H

#include <QObject>
extern "C" {
    #include <libswresample/swresample.h>
    #include <libavutil/opt.h>
}

class MySwrContext : public QObject
{
    Q_OBJECT
public:
    explicit MySwrContext(QObject *parent = nullptr);
    ~MySwrContext();

    void SetChannelCount(int in, int out);
    void SetChannelLayout(unsigned long long in, unsigned long long out);
    void SetSampleRate(int in, int out);

    bool IsInitialized() const;

private:
    SwrContext* m_pSwr = nullptr;
};

#endif // MYSWRCONTEXT_H
