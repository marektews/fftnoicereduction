#include <QDebug>
#include "AudioFileLoader.h"
#include "MyAVFormatContext.h"
#include "MyAVCodec.h"
#include "MyAVFrame.h"
#include "MySwrContext.h"
#include "MyAVPacket.h"
#include "MyAVSamplesBuffer.h"

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
 *
 * https://stackoverflow.com/questions/76083629/extracting-audio-samples-using-libavcodec
 * https://rodic.fr/blog/libavcodec-tutorial-decode-audio-file/
 * https://steemit.com/programming/@targodan/decoding-audio-files-with-ffmpeg
 */
void AudioFileLoader::doLoadAudioFile(QUrl filename)
{
    MyAVFormatContext avFormat;
    if(!avFormat.OpenFile(filename.toLocalFile()))
        return;

    AVStream* pStream = avFormat.GetStream(AVMEDIA_TYPE_AUDIO);
    if(pStream == nullptr)
        return;

    MyAVCodec avDecoder(pStream);

    MySwrContext converter;
    // converter.SetChannelCount(avDecoder.GetChannelsCount(), avDecoder.GetChannelsCount());
    converter.SetChannelLayout(avDecoder.GetChannelLayout(), avDecoder.GetChannelLayout());
    converter.SetSampleRate(avDecoder.GetSampleRate(), avDecoder.GetSampleRate());
    converter.SetSampleFormat(avDecoder.GetSampleFormat(), AV_SAMPLE_FMT_DBLP);
    if(!converter.Initialize())
        return;

    MyAVPacket avPacket;
    MyAVFrame avS16Frame;
    QList<MyAVFrame::Ptr> result;
    while(av_read_frame(avFormat, avPacket) >= 0)
    {
        // decode audio
        int sendResult = avcodec_send_packet(avDecoder, avPacket);
        Q_ASSERT(sendResult == 0);
        int recvResult = avcodec_receive_frame(avDecoder, avS16Frame);
        Q_ASSERT(recvResult == 0);

        // resample frame
        MyAVFrame::Ptr pDblFrame(new MyAVFrame());
        if(pDblFrame)
        {
            pDblFrame->SetChannelLayout(avS16Frame.GetChannelLayout());
            pDblFrame->SetSampleRate(avS16Frame.GetSampleRate());
            pDblFrame->SetSampleFormat(AV_SAMPLE_FMT_DBLP);

            converter.Convert(avS16Frame, *pDblFrame);
            result.append(pDblFrame);
        }
    }

    emit resultReady(result);
}


