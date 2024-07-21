#pragma once

#include <string>
#include <AL/al.h>
#include "../debug/Logger.h"

namespace Zewada
{
    class Sound
    {
    private:
        int m_dataLength;
        ALuint m_bufferId;
        ALuint m_sourceId;
        std::string m_filepath;

        bool m_isPlaying = false;
    public:
        Sound() = default;
        Sound(const std::string& filepath, bool loops);
        ~Sound();
        void Play();
        void Stop();
        void Delete();

        inline const std::string& GetFilepath() {return m_filepath;}
        const bool IsPlaying();
    };
}