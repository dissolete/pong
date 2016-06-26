#ifndef CRMUSICHANDLER_HPP
#define CRMUSICHANDLER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "CRConstants.hpp"
#include "CRTypes.hpp"
#include "CRMusic.hpp"
#include "CRSound.hpp"

namespace CRE
{

      class SoundManager
      {
            public:

                  /////////////////////////////
                  /* Public member functions */
                  /////////////////////////////

                  /**
                  * Default constructor. Initializes private member values
                  */
                  SoundManager();

                  /**
                  *
                  */
                  virtual ~SoundManager();

                  /**
                  * Registers the app pointer with this class so this can reference the app for
                  * error handling and/or other functions.
                  */
                  void register_app(App * theApp);

                  /**
                  * Adds a new song to the back of the song vector. Quits app if the song resource
                  * doesn't exist.
                  */
                  void add_song(std::string songID, std::string path, bool loop = true);

                  /**
                  * Plays the song at the back of the song list vector. The back is where the active 
                  * song should be.
                  */
                  void play_song();

                  /**
                  * Plays a song based on the string identifier. This function moves the song item to
                  * the back of the song list vector.
                  */
                  void play_song(std::string songID);

                  /**
                  * Stops the active song, which is at the back of the song list vector.
                  */
                  void stop_song();

                  /**
                  * Pauses the active song.
                  */
                  void pause_song();

                  /**
                  * Removes a song from the song vector.
                  */
                  void remove_song(std::string songID);

                  /**
                  * Returns a pointer to the sf::music object to directly change it if needed
                  */
                  sf::Music * get_song(std::string songID);

                  /**
                  * Returns a pointer to the sf::music object to directly change it if needed
                  */
                  sf::Music * get_active_song();

                  /**
                  * Adds a sound to the sound map.
                  */
                  void add_sound(std::string soundID, std::string soundPath);

                  /**
                  * Plays a sound based on the key provided
                  */
                  void play_sound(std::string soundID);

                  /**
                  * Removes a sound based on the soundID
                  */
                  void remove_sound(std::string soundID);
            
            private:

                  // Pointer to the app class
                  App * _theApp;

                  // Vector holds the songs
                  std::vector<Song*> _songList;

                  // Vector holds the keys for the songs (used to deallocate the memory of the map)
                  std::vector<std::string> _mapKeys;

                  // Map holds the sounds
                  std::unordered_map<std::string, Sound *> _soundMap;

                  /**
                  * Copy constructor is private because we do not allow copies of this
                  * class.
                  */
                  SoundManager(const SoundManager&); // intentionally undefined

                  /**
                  * Overloaded assignment operator is private because we do not allow
                  * copies of this class.
                  */
                  SoundManager & operator=(const SoundManager&); // intentionally undefined

      };
}

#endif