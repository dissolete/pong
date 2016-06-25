#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include "PongApp.hpp"
#include "CRState.hpp"
#include "CRTypes.hpp"

class MenuState : public CRE::State
{
	public:

		/**
		*
		*/
		MenuState(std::string stateID, CRE::App & theApp);

		/**
		*
		*/
		virtual ~MenuState();

		/**
		*
		*/
		virtual void init();

		/**
		*
		*/
		virtual void reinit();

		/**
		*
		*/
		virtual void pause();

		/**
		*
		*/
		virtual void resume();

		/**
		*
		*/
		virtual void handle_events(sf::Event theEvent);

		/**
		*
		*/
		virtual void update(void);

		/**
		*
		*/
		virtual void update_variable(float elapsedTime);

		/**
		*
		*/
		virtual void draw(void);

	protected:

		/**
		*
		*/
		virtual void handle_cleanup(void);

	private:

		bool _atMainMenu;
		bool _atDifficultyScreen;
		bool _playGame;
		bool _normalDiff;

		sf::Vector2i _mousePos;
};

#endif