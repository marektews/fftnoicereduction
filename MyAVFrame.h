#ifndef MYAVFRAME_H
#define MYAVFRAME_H

#include <QObject>
extern "C" {
    #include <libavcodec/avcodec.h>
}

class MyAVFrame : public QObject
{
    Q_OBJECT
public:
    explicit MyAVFrame(QObject *parent = nullptr);
    ~MyAVFrame();

    operator AVFrame*() { return m_pFrame; }

private:
    AVFrame* m_pFrame = nullptr;
};

#endif // MYAVFRAME_H
