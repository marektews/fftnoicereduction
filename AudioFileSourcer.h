#ifndef AUDIOFILESOURCER_H
#define AUDIOFILESOURCER_H

#include <QObject>
#include <QThread>
#include <QList>
#include <QQmlEngine>
#include "MyAVFrame.h"

class AudioFileSourcer : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QUrl filename READ filename WRITE setFilename NOTIFY filenameChanged FINAL)
    Q_PROPERTY(QList<MyAVFrame::Ptr> audioRealBuffer READ audioRealBuffer NOTIFY audioRealBufferChanged FINAL)

public:
    explicit AudioFileSourcer(QObject *parent = nullptr);
    ~AudioFileSourcer();

    QUrl filename() const;
    void setFilename(QUrl fn);

    QList<MyAVFrame::Ptr> audioRealBuffer() const;

signals:
    void filenameChanged();
    void audioRealBufferChanged();

    void loadAudioFile(QUrl filename);

private:
    void startFileWorker();
    void onAudioFileLoaded(QList<MyAVFrame::Ptr> lst);

private:
    QUrl m_filename;
    QList<MyAVFrame::Ptr> m_lstAudioRealBuffer;
    QThread m_thread;
};

#endif // AUDIOFILESOURCER_H
