#ifndef MYAVFORMATCONTEXT_H
#define MYAVFORMATCONTEXT_H

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
}
#include <QString>

class MyAVFormatContext
{
public:
    explicit MyAVFormatContext();
    ~MyAVFormatContext();

    bool OpenFile(QString filename);
    AVStream* GetStream(AVMediaType mediaType = AVMEDIA_TYPE_AUDIO);

    operator AVFormatContext*() const { return m_pFormat; }


private:
    AVFormatContext* m_pFormat = nullptr;
};

#endif // MYAVFORMATCONTEXT_H
