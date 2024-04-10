#include "AudioFileLoader.h"
#include "MyAVFormatContext.h"

/**
 * @brief AudioFileLoader::AudioFileLoader
 * @param parent
 */
AudioFileLoader::AudioFileLoader(QObject *parent) : QObject{parent}
{}

/**
 * @brief AudioFileLoader::doLoadAudioFile
 * @param filename
 * Wykonywane w oddzielnym wątku ładowanie danych audio ze wskazanego pliku
 */
void AudioFileLoader::doLoadAudioFile(QString filename)
{
    MyAVFormatContext avFormat;

    FFTRealBuffer::Ptr pBuffer(new FFTRealBuffer(10));

    emit resultReady(pBuffer);
}


