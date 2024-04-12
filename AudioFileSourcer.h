#ifndef AUDIOFILESOURCER_H
#define AUDIOFILESOURCER_H

#include <QObject>
#include <QThread>
#include <QQmlEngine>
#include "FFTRealBuffer.h"

class AudioFileSourcer : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QUrl filename READ filename WRITE setFilename NOTIFY filenameChanged FINAL)
    Q_PROPERTY(FFTRealBuffer::Ptr audioRealBuffer READ audioRealBuffer NOTIFY audioRealBufferChanged FINAL)

public:
    explicit AudioFileSourcer(QObject *parent = nullptr);
    ~AudioFileSourcer();

    QUrl filename() const;
    void setFilename(QUrl fn);

    FFTRealBuffer::Ptr audioRealBuffer() const;

signals:
    void filenameChanged();
    void audioRealBufferChanged();

    void loadAudioFile(QUrl filename);

private:
    void startFileWorker();
    void onAudioFileLoaded(FFTRealBuffer::Ptr pBuffer);

private:
    QUrl m_filename;
    FFTRealBuffer::Ptr m_pAudioRealBuffer;

    QThread m_thread;
};

#endif // AUDIOFILESOURCER_H
