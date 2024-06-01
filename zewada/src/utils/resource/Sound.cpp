#include "Sound.h"
#include <zpch.h>

#include <stb_vorbis.c>

namespace Zewada
{
    Sound::Sound(const std::string& filepath, bool loops)
    {
        m_filepath = std::filesystem::current_path().string() + "/" + filepath;

        int channelsBuffer;
        ALsizei sampleRateBuffer;
        short* rawAudioBuffer = nullptr;

        m_dataLength = stb_vorbis_decode_filename(m_filepath.c_str(), &channelsBuffer, &sampleRateBuffer, &rawAudioBuffer);
        //if noise at the end with stereo sound change channelsbuffer to 2
        m_dataLength = m_dataLength*channelsBuffer*sizeof(short);
        if(rawAudioBuffer == nullptr)
        {
            Z_ERROR()<< "Could not load sound: " << m_filepath;
            return;
        }

        ALenum format;
        if(channelsBuffer == 1)
        {
            format = AL_FORMAT_MONO16;
        }
        else if(channelsBuffer == 2)
        {
            format = AL_FORMAT_STEREO16;
        }

        alGenBuffers(1, &m_bufferId);
        alBufferData(m_bufferId, format, rawAudioBuffer, m_dataLength, sampleRateBuffer);

        alGenSources(1, &m_sourceId);
        alSourcei(m_sourceId, AL_BUFFER, m_bufferId);
        alSourcei(m_sourceId, AL_LOOPING, loops ? 1 : 0);
        alSource3f(m_sourceId, AL_POSITION, 0, 0, 0);
        alSourcef(m_sourceId, AL_GAIN, 0.3f);
    
        free(rawAudioBuffer);
    }

    void Sound::Delete()
    {
        alDeleteSources(1, &m_sourceId);
        alDeleteBuffers(1, &m_bufferId);
    }

    void Sound::Play()
    {
        ALenum state;
        alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);
        if(state == AL_STOPPED)
        {
            m_isPlaying = false;
            alSource3f(m_sourceId, AL_POSITION, 0, 0, 0);
        }

        if(!m_isPlaying)
        {
            alSourcePlay(m_sourceId);
            m_isPlaying = true;
        }
    }

    void Sound::Stop()
    {
        if(m_isPlaying)
        {
            alSourceStop(m_sourceId);
            m_isPlaying = false;
        }
    }

    const bool Sound::IsPlaying()
    {
        ALenum state;
        alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);
        if(state == AL_STOPPED)
        {
            m_isPlaying = false;
        }
        return m_isPlaying;
    } 
}