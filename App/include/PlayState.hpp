#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string.h>
#include "PongApp.hpp"
#include "CRState.hpp"
#include "CRTypes.hpp"

class PlayState : public CRE::State
{
	public:

		/**
		*
		*/
		PlayState(const std::string stateID, CRE::App& theApp);

		/**
		*
		*/
		virtual ~PlayState();

		/**
		*
		*/
		virtual void init(void);

		/**
		*
		*/
		virtual void reinit(void);

		/**
		*
		*/
		virtual void pause(void);

		/**
		*
		*/
		virtual void resume(void);

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

		bool _gameOver;
		
		const int _paddleWidth = 20;
		const int _paddleHeight = 60;
		const int _vel = 5;

		int _paddle1Vel, _paddle2Vel, _paddle1Pos, _paddle2Pos, _ballXPos, _ballYPos, 
				_ballXVel, _ballYVel, _p1Score, _p2Score;

		sf::Texture _paddleTexture;
		sf::Texture _ballTexture;
		sf::Sprite _paddleSprite1, _paddleSprite2;
		sf::CircleShape _ball;

};

#endif