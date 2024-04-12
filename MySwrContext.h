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
    void SetChannelLayout(uint64_t in, uint64_t out);
    void SetSampleRate(int in, int out);
    void SetSampleFormat(int in, int out);

    bool Initialize();
    bool IsInitialized() const;

private:
    SwrContext* m_pSwr = nullptr;
};

#endif // MYSWRCONTEXT_H
