#include "CRSoundManager.hpp"
#include "CRApp.hpp"

namespace CRE
{
    SoundManager::SoundManager() :
        _theApp(NULL),
        _songList(),
        _soundMap()
    {}

    SoundManager::~SoundManager()
    {
        // Iterate through the song list and deallocate memory
        while( not _songList.empty() )
        {
            // Get the song at the back of the vector
            Song * currSong = _songList.back();

            // Remove this song from the vector
            _songList.pop_back();

            // Delete the song
            delete currSong;

            // Remove local pointer
            currSong = NULL;
        }

        // Iterate through key list
        while( not _mapKeys.empty() )
        {
            // Get the key
            std::string key = _mapKeys.back();

            // Remove key
            _mapKeys.pop_back();

            // Get a pointer to the sound
            Sound * thisSong = _soundMap[key];

            // Remove the sound from the map
            _soundMap.erase(key);

            // Deallocate sound
            delete thisSong;

            // Remove local pointer
            thisSong = NULL;
        }

        // Remove app pointer
        _theApp = NULL;
    }

    void SoundManager::register_app(App * theApp)
    {
        // Check that our pointer is good
        assert(NULL != theApp and "TextManager::register_app() theApp pointer provided is bad");

        // Make a note of the pointer
        assert(NULL == _theApp and "TextManager::register_app() theApp pointer was already registered");

        _theApp = theApp;
    }

    void SoundManager::add_song(std::string songID, std::string songPath, bool loop)
    {
        // Allocate memory for new song
        Song * newSong = new Song(songID);

        // If the song can be loaded
        if( newSong->_song.openFromFile(songPath) )
        {
            newSong->_song.setLoop(loop);

            // Push it to the back of the vector
            _songList.push_back(newSong);
        }
        else
        {
            delete newSong;
            _theApp->quit(STATUS_ASSET_COULDNT_BE_LOADED);
        }

        newSong = NULL;
        
    }

    void SoundManager::play_song()
    {
        if( not _songList.empty() )
            // Play the song at the back of the vector
            _songList.back()->_song.play();
    }

    void SoundManager::play_song(std::string songID)
    {
        if( not _songList.empty() )
        {
            std::vector<Song *>::iterator it = _songList.begin();

            // Iterate through song list
            while( it != _songList.end() )
            {
                // If the song we're at matches the passed songID
                if( (*it)->get_ID() == songID )
                {
                    // Get a pointer to the soon to be repositioned song
                    Song * thisSong = (*it);

                    // Remove this from the song list
                    _songList.erase(it);

                    // Stop the current song if needed
                    if( not _songList.empty() )
                        _songList.back()->_song.stop();

                    // Add song to the back
                    _songList.push_back(thisSong);

                    // Play this song
                    _songList.back()->_song.play();

                    // Remove local pointer
                    thisSong = NULL;

                    // break from the loop
                    break;
                } //if( (*it)->get_ID() == songID )
            }//while( it != _songList.end() )
        }//if( not _songList.empty() )
    }

    void SoundManager::stop_song()
    {
        _songList.back()->_song.stop();
    }

    void SoundManager::pause_song()
    {
        _songList.back()->_song.pause();
    }

    void SoundManager::remove_song(std::string songID)
    {
        std::vector<Song *>::iterator it = _songList.begin();

        // Iterate through song list
        while( it != _songList.end() )
        {
            // If the song we're at matches the song ID
            if( (*it)->get_ID() == songID )
            {
                // Get a pointer to this song
                Song * thisSong = (*it);

                // Remove the song from the list
                _songList.erase(it);

                // Stop this song if needed
                thisSong->_song.stop();

                // Delete the song
                delete thisSong;

                // Remove local pointer
                thisSong = NULL;

                // break from loop
                break;
            } // if( (*it)->get_ID() == songID )
        } // while( it != _songList.end() )
    }

    sf::Music * SoundManager::get_song(std::string songID)
    {
        for( Song * songIT : _songList )
            if(songIT->get_ID() == songID)
                return &(songIT->_song);
    }

    sf::Music * SoundManager::get_active_song()
    {
        return &(_songList.back()->_song);
    }

    void SoundManager::add_sound(std::string soundID, std::string soundPath)
    {
        // Allocate memory for the new sound
        Sound * newSound = new Sound();

        // If this sound can be loaded
        if( newSound->_buffer.loadFromFile(soundPath) )
        {
            // Set the buffer for the actual sf::sound object
            newSound->_sound.setBuffer(newSound->_buffer);

            // Add this to the map
            std::pair<std::string, Sound *> songInsert(soundID, newSound);
            _soundMap.insert(songInsert);

            // Add the key to the key vector
            _mapKeys.push_back(soundID);
        }
        // Otherwise
        else
        {
            // Delete the allocated song class
            delete newSound;

            // Quit the app
            if( _theApp != NULL )
                _theApp->quit(STATUS_ASSET_COULDNT_BE_LOADED);
        }

        // remove local pointer
        newSound = NULL;
    }

    void SoundManager::play_sound(std::string soundID)
    {
        _soundMap[soundID]->_sound.play();
    }

    void SoundManager::remove_sound(std::string soundID)
    {
        // Get pointer to the song in the map
        Sound * thisSound = _soundMap[soundID];

        // Remove the sound from the map
        _soundMap.erase(soundID);

        // Remove this key
        std::vector<std::string>::iterator it;
        for( it = _mapKeys.begin(); it <= _mapKeys.end(); it++ )
        {
            if( *it == soundID )
            {
                _mapKeys.erase(it);
                break;
            }
        }

        // Deallocate the memory for the sound
        delete thisSound;

        // Remove local pointer
        thisSound = NULL;

    }
}