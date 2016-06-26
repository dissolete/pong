#ifndef CRMUSIC_HPP
#define CRMUSIC_HPP

#include <SFML/Audio/Music.hpp>
#include <string>

namespace CRE
{
	class Song
	{
		public:

			/**
			* Default constructor sets songID
			*/
			Song(std::string songID) :
				_songID(songID)
			{}

			/**
			* Returns the string ID for this song
			*/
			std::string get_ID()
			{
				return _songID;
			}

			// The SFML music object this class holds
			sf::Music _song;

		private:

			//////////////////////////////
            /* Private member variables */
            //////////////////////////////

			// The string identifier for this song
            const std::string _songID;

	};
}

#endif