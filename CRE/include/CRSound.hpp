#ifndef CRSOUND_HPP
#define CRSOUND_HPP

#include <SFML/Audio.hpp>
#include "CRTypes.hpp"

namespace CRE
{
    class Sound
    {
        public:

            Sound() :
                _sound(),
                _buffer()
            {}

            sf::Sound _sound;
            sf::SoundBuffer _buffer;
    };
}

#endif