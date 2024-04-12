#include "AudioFileLoader.h"
#include "MyAVFormatContext.h"
#include "MyAVCodec.h"
#include "MyAVFrame.h"
#include "MySwrContext.h"
#include "MyAVPacket.h"

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

    MySwrContext resampler;
    resampler.SetChannelCount(avDecoder.GetChannelsCount(), avDecoder.GetChannelsCount());
    resampler.SetChannelLayout(avDecoder.GetChannelLayout(), avDecoder.GetChannelLayout());
    resampler.SetSampleRate(avDecoder.GetSampleRate(), avDecoder.GetSampleRate());
    resampler.SetSampleFormat(avDecoder.GetSampleFormat(), AV_SAMPLE_FMT_DBL);
    if(!resampler.Initialize())
        return;

    MyAVPacket avPacket;
    MyAVFrame avFrame;

    FFTRealBuffer::Ptr pBuffer(new FFTRealBuffer(10));

    while(av_read_frame(avFormat, avPacket) >= 0)
    {
        // decode audio
        int sendResult = avcodec_send_packet(avDecoder, avPacket);
        int recvResult = avcodec_receive_frame(avDecoder, avFrame);

        // resample frame

    }

    emit resultReady(pBuffer);
}


