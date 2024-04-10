#ifndef MYAVFORMATCONTEXT_H
#define MYAVFORMATCONTEXT_H

#include <QObject>
extern "C" {
    #include <libavformat/avformat.h>
}

class MyAVFormatContext : public QObject
{
    Q_OBJECT
public:
    explicit MyAVFormatContext(QObject *parent = nullptr);
    ~MyAVFormatContext();

    bool OpenFile(QString filename);

    operator AVFormatContext*() const { return m_pFormat; }


private:
    AVFormatContext* m_pFormat = nullptr;
};

#endif // MYAVFORMATCONTEXT_H
