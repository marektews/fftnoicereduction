#include "AudioFileSourcer.h"
#include "AudioFileLoader.h"

/**
 * @brief AudioFileSourcer::AudioFileSourcer
 * @param parent
 */
AudioFileSourcer::AudioFileSourcer(QObject *parent) : QObject{parent}
{}

/**
 * @brief AudioFileSourcer::~AudioFileSourcer
 */
AudioFileSourcer::~AudioFileSourcer()
{
    m_thread.quit();
    m_thread.wait();
}

/**
 * @brief AudioFileSourcer::filename
 * @return
 */
QUrl AudioFileSourcer::filename() const
{
    return m_filename;
}

/**
 * @brief AudioFileSourcer::setFilename
 * @param fn
 */
void AudioFileSourcer::setFilename(QUrl fn)
{
    if(m_filename == fn) return;
    m_filename = fn;
    emit filenameChanged();
    startFileWorker();
}

/**
 * @brief AudioFileSourcer::audioRealBuffer
 * @return
 */
FFTRealBuffer::Ptr AudioFileSourcer::audioRealBuffer() const
{
    return m_pAudioRealBuffer;
}

/**
 * @brief AudioFileSourcer::startFileWorker
 */
void AudioFileSourcer::startFileWorker()
{
    AudioFileLoader* pWorker = new AudioFileLoader();
    if(pWorker)
    {
        pWorker->moveToThread(&m_thread);
        connect(&m_thread, &QThread::finished, pWorker, &AudioFileLoader::deleteLater);
        connect(this, &AudioFileSourcer::loadAudioFile, pWorker, &AudioFileLoader::doLoadAudioFile);
        connect(pWorker, &AudioFileLoader::resultReady, this, &AudioFileSourcer::onAudioFileLoaded);
        m_thread.start();
        emit loadAudioFile(m_filename);
    }
}

/**
 * @brief AudioFileSourcer::onAudioFileLoaded
 */
void AudioFileSourcer::onAudioFileLoaded(FFTRealBuffer::Ptr pBuffer)
{
    m_pAudioRealBuffer = pBuffer;
    emit audioRealBufferChanged();
}
