#ifndef _STATES_HPP
#define _STATES_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp> // Used to control the buttons in the game
#include <iostream>
//#include "PongApplication.hpp"

namespace crp
{	
	// The forward declaration is a result of a circular dependency between
	// the application class and the classes included in this header. 
	class Application;

	class GameState{
	protected:
		const std::string stateName_;
		// The pointer to the application
		//Application * theApp_;
		sf::RenderWindow & window_;

		bool initialized_;
		
		bool paused_;

		bool cleanup_;

		bool deinit_;

	public:

		GameState( std::string stateName, sf::RenderWindow & theWindow );

		virtual ~GameState();

		/**
		* init is responsible for initilizing the state.
		*/
		virtual void init();

		virtual void reinit() = 0;

		virtual void deinit();

		virtual void pause();

		virtual void resume();

		virtual void process_events(sf::Event & event) = 0;

		virtual void process_logic() = 0;

		virtual void render() = 0;

		virtual void cleanup();

		virtual const bool isPaused() const;

		virtual const bool isInit() const;

		virtual const bool isDeinit() const;

		virtual const bool needsCleanup() const;

		virtual const std::string getStateName() const;

	};

	class SplashState : public crp::GameState{
	private:

		sf::Texture * splashLogo_;
		sf::Sprite * logoSprite_;
		sf::Color color_;

		int frameCount_;

	public:
		SplashState( std::string stateName, sf::RenderWindow & theWindow );

		virtual ~SplashState();

		virtual void init();

		virtual void reinit();

		virtual void deinit();

		virtual void pause();

		virtual void resume();

		virtual void process_events(sf::Event & event);

		virtual void process_logic();

		virtual void render();

		virtual void cleanup();

	};

	class StateManager{
	private:
		//Application * theApp_;
		std::vector<GameState*> stateStack;
		std::vector<GameState*> deadStateStack;
	public:
		StateManager();
		~StateManager();

		GameState & getActiveState();

		void addActiveState(GameState * state);

		void deactivateActiveState();

		void removeActiveState();

		const bool isEmpty() const;
	};



class MenuState : public crp::GameState{

private:
   // bool flags
	bool atMenuScreen;

	bool atDifficultyScreen;

	bool atPlayerScreen;
    // to see where the mouse is
	sf::Vector2i mousePosition;
    // all of the text for the menu
	sf::Text menuTitleText;
	sf::Text menuPlayerText;
	sf::Text menuComputerText;
	sf::Text menuMultiPlayerText;
	sf::Text difficultyText;
	sf::Text hardDiffText;
	sf::Text normalDiffText;
	sf::Text menuStartText;

  // all of the float rects for the text
    sf::FloatRect titleRect;
    sf::FloatRect playerRect;
	sf::FloatRect computerRect;
	sf::FloatRect multiPlayerRect;
	sf::FloatRect difficultyRect;
	sf::FloatRect hardDiffRect;
    sf::FloatRect normalDiffRect;
    sf::FloatRect startRect;

    sf::Font titleFont;
    sf::Font dataFont;


    int numPlayers;

	const int WINDOW_WIDTH_ = 400;
	const int WINDOW_HEIGHT_ = 300;

    //int frameCount_;
public:

	MenuState(std::string stateName, sf::RenderWindow & theWindow);
    ~MenuState();

    virtual void init();

	virtual void reinit();

	virtual void deinit();

	virtual void pause();

	virtual void resume();

	virtual void process_events(sf::Event & event);

	virtual void process_logic();

	virtual void render();

	virtual void cleanup();




};

}

#endif