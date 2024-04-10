#ifndef AUDIOFILELOADER_H
#define AUDIOFILELOADER_H

#include <QObject>
#include <QQmlEngine>

class AudioFileLoader : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AudioFileLoader(QObject *parent = nullptr);

signals:
};

#endif // AUDIOFILELOADER_H
