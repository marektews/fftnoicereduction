#ifndef AUDIOFILELOADER_H
#define AUDIOFILELOADER_H

#include <QObject>
#include <QThread>
#include "FFTRealBuffer.h"

/**
 * @brief The AudioFileLoader class
 * Worker pracujący w wątku.
 * Ładuje wskazany plik i tworzy z niego bufor danych audio do dalszego przetwarzania.
 */
class AudioFileLoader : public QObject
{
    Q_OBJECT

public:
    explicit AudioFileLoader(QObject *parent = nullptr);

    void doLoadAudioFile(QString filename);

signals:
    void resultReady(FFTRealBuffer::Ptr pBuffer);
};

#endif // AUDIOFILELOADER_H
