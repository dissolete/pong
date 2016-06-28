#include "CRApp.hpp"
#include "MenuState.hpp"
#include "CRConstants.hpp"

MenuState::MenuState(std::string stateID, CRE::App & theApp) :
	CRE::State(stateID, theApp),
	_mousePos()
{}

MenuState::~MenuState()
{}

void MenuState::init()
{
	// Initialize parent state
	CRE::State::init();

	// Set default flags
	_atMainMenu = true;
	_atDifficultyScreen = true;
	_playGame = false;

	// Add texts
	_theApp._textManager.add_text("Title", "Pong", sf::Vector2f(_theApp._windowWidth / 2, 40), 30);
	_theApp._textManager.add_text("DifficultyOption", "Difficulty", 
								sf::Vector2f(_theApp._windowWidth / 2, _theApp._windowHeight / 2), 30);
	_theApp._textManager.add_text("PlayGame", "Play Game", sf::Vector2f(_theApp._windowWidth / 2, _theApp._windowHeight - 40));
	_theApp._textManager.add_text("EasyMode", "Easy", sf::Vector2f(_theApp._windowWidth / 2, _theApp._windowHeight / 3));
	_theApp._textManager.add_text("HardMode", "Hard", sf::Vector2f(_theApp._windowWidth / 2, _theApp._windowHeight * 2 / 3));

	_theApp._soundManager.add_song("Theme", "resources/pong_theme.wav", true);
}

void MenuState::reinit()
{

}

void MenuState::pause()
{
	// Pause parent state
	CRE::State::pause();
}

void MenuState::resume()
{
	// Resume parent state
	CRE::State::resume();

	_theApp._soundManager.play_song();
}

void MenuState::handle_events(sf::Event theEvent)
{
	// Check if the event is a mouse button press
	if( theEvent.type == sf::Event::MouseButtonPressed )
	{
		// Check if the mouse button was pressed over one of the menu options
		if( _theApp._textManager.get_text("DifficultyOption")->getGlobalBounds().contains(_mousePos.x, _mousePos.y) and _atMainMenu )
		{
			_atDifficultyScreen = true;
			_atMainMenu = false;
		}
		else if( _theApp._textManager.get_text("EasyMode")->getGlobalBounds().contains(_mousePos.x, _mousePos.y) and _atDifficultyScreen )
		{
			// Difficulty set
			_theApp._statManager.set_difficulty(CRE::DIFF_EASY);

			// Set flags
			_atMainMenu = true;
			_atDifficultyScreen = false;
		}
		else if( _theApp._textManager.get_text("HardMode")->getGlobalBounds().contains(_mousePos.x, _mousePos.y) and _atDifficultyScreen )
		{
			// Difficulty set
			_theApp._statManager.set_difficulty(CRE::DIFF_HARD);

			// Set flags
			_atMainMenu = true;
			_atDifficultyScreen = false;
		}
		else if( _theApp._textManager.get_text("PlayGame")->getGlobalBounds().contains(_mousePos.x, _mousePos.y) and _atMainMenu )
		{
			// Set the play state as the active state
			_theApp._stateManager.set_active_state("PlayState");
		}
	}
}

void MenuState::update(void)
{
	// Get mouse position, used to highlight texts if needed
	_mousePos = sf::Mouse::getPosition(_theApp._window );

	// If we're at the main menu
	if( _atMainMenu )
	{	
		// If the mouse is hovering over the difficulty option
		if(_theApp._textManager.get_text("DifficultyOption")->getGlobalBounds().contains(_mousePos.x, _mousePos.y) )
		{
			// Color this text red and underline it
			_theApp._textManager.set_color("DifficultyOption", sf::Color::Red);
			_theApp._textManager.set_style("DifficultyOption", sf::Text::Underlined);
		}
		else if(_theApp._textManager.get_text("PlayGame")->getGlobalBounds().contains(_mousePos.x, _mousePos.y))
		{
			// Color this text red and underline it
			_theApp._textManager.set_color("PlayGame", sf::Color::Red);
			_theApp._textManager.set_style("PlayGame", sf::Text::Underlined);
		}
		else
		{
			// Otherwise set everything to normal style
			_theApp._textManager.set_color("DifficultyOption", sf::Color::White);
			_theApp._textManager.set_style("DifficultyOption", sf::Text::Regular);
			_theApp._textManager.set_color("PlayGame", sf::Color::White);
			_theApp._textManager.set_style("PlayGame", sf::Text::Regular);
		}
	}
	// If we are at the difficulty screen
	else if( _atDifficultyScreen )
	{
		// If the mouse pointer is over the easy difficulty option
		if( _theApp._textManager.get_text("EasyMode")->getGlobalBounds().contains(_mousePos.x, _mousePos.y) )
		{
			// Color it red and underline it
			_theApp._textManager.set_color("EasyMode", sf::Color::Red);
			_theApp._textManager.set_style("EasyMode", sf::Text::Underlined);
		}
		// Or if the mous is over the hard difficulty option
		else if( _theApp._textManager.get_text("HardMode")->getGlobalBounds().contains(_mousePos.x, _mousePos.y) )
		{
			// Color it red and underline it
			_theApp._textManager.set_color("HardMode", sf::Color::Red);
			_theApp._textManager.set_style("HardMode", sf::Text::Underlined);
		}
		else
		{
			// Otherwise set everything to normal style
			_theApp._textManager.set_color("EasyMode", sf::Color::White);
			_theApp._textManager.set_style("EasyMode", sf::Text::Regular);
			_theApp._textManager.set_color("HardMode", sf::Color::White);
			_theApp._textManager.set_style("HardMode", sf::Text::Regular);
		}
	}

}

void MenuState::update_variable(float elapsedTime){}

void MenuState::draw(void)
{
	// Clear the screen with black
	_theApp._window.clear(sf::Color::Black);

	// If at main menu
	if( _atMainMenu )
	{
		// Draw necessary texts for the main menu
		_theApp._textManager.draw_text("Title");
		_theApp._textManager.draw_text("DifficultyOption");
		_theApp._textManager.draw_text("PlayGame");
	}
	// If at difficulty screen
	else if( _atDifficultyScreen )
	{
		_theApp._textManager.draw_text("EasyMode");
		_theApp._textManager.draw_text("HardMode");
	}
}

void MenuState::handle_cleanup(void)
{

}