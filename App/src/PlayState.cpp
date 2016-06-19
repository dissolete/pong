

#include "CRApp.hpp"
#include "PlayState.hpp"

PlayState::PlayState(const std::string stateID, CRE::App& theApp) :
	CRE::State(stateID, theApp),
	_paddleTexture(),
	_paddleSprite1(),
	_paddleSprite2(),
	_ballTexture(),
	_ball(0),
	_paddle1Vel(0),
	_paddle2Vel(0),
	_paddle1Pos(0),
	_paddle2Pos(0),
	_ballXPos(0),
	_ballYPos(0),
	_ballXVel(0),
	_ballYVel(0)
{

}

PlayState::~PlayState()
{
}

void PlayState::init(void)
{
	CRE::State::init();

	if( _paddleTexture.loadFromFile("resources/white_texture.png", sf::IntRect(10, 10, _paddleWidth, _paddleHeight)) )
	{
		if( _ballTexture.loadFromFile("resources/white_texture.png", sf::IntRect(10, 10, 10, 10)))
		{
				_paddleSprite1.setTexture(_paddleTexture);
				_paddleSprite2.setTexture(_paddleTexture);
				_ball.setRadius(10);
		
				_ball.setTexture(&_ballTexture);
		
				_paddle1Pos = (_theApp._windowHeight - _paddleHeight) / 2;
				_paddle2Pos = (_theApp._windowHeight - _paddleHeight) / 2;

				_ballXPos = 40;
				_ballYPos = _theApp._windowHeight / 2;

				_ballXVel = 5;
				_ballYVel = -5;
		
				_paddleSprite1.setPosition(sf::Vector2f(20, _paddle1Pos ));
				_paddleSprite2.setPosition(sf::Vector2f(_theApp._windowWidth - _paddleWidth - 20, _paddle2Pos ));

				_ball.setPosition(sf::Vector2f(_ballXPos, _ballYPos));
				
		}
		else
			_theApp.quit(CRE::STATUS_ASSET_COULDNT_BE_LOADED);

	}
	else
		_theApp.quit(CRE::STATUS_ASSET_COULDNT_BE_LOADED);
}

void PlayState::reinit(void)
{

}

void PlayState::pause(void)
{

}

void PlayState::resume(void)
{

}

void PlayState::handle_events(sf::Event theEvent)
{
	// Check if the user presses down a key
	if( theEvent.type == sf::Event::KeyPressed )
	{
		// Set paddle velocities if the right key was pressed
		if( theEvent.key.code == sf::Keyboard::Up )
			_paddle2Vel -= _vel;
		else if( theEvent.key.code == sf::Keyboard::Down )
			_paddle2Vel += _vel;
		else if( theEvent.key.code == sf::Keyboard::W )
			_paddle1Vel -= _vel;
		else if( theEvent.key.code == sf::Keyboard::S )
			_paddle1Vel += _vel;

	}
	// reset velocities if the user lets go of a key
	else if( theEvent.type == sf::Event::KeyReleased )
	{
		if( theEvent.key.code == sf::Keyboard::Up )
			_paddle2Vel += _vel;
		else if( theEvent.key.code == sf::Keyboard::Down )
			_paddle2Vel -= _vel;
		else if( theEvent.key.code == sf::Keyboard::W )
			_paddle1Vel += _vel;
		else if( theEvent.key.code == sf::Keyboard::S )
			_paddle1Vel -= _vel;
	}
}

void PlayState::update(void)
{
	/////////////////////////////
	/* Update paddle positions */
	/////////////////////////////

	// Change Y position of paddles
	_paddle1Pos += _paddle1Vel;
	_paddle2Pos += _paddle2Vel;

	// Check if the paddles have moved offscreen, if they have then move them back
	if( _paddle1Pos + _paddleHeight > _theApp._windowHeight or _paddle1Pos < 0 )
		_paddle1Pos -= _paddle1Vel;

	if( _paddle2Pos + _paddleHeight > _theApp._windowHeight or _paddle2Pos < 0 )
		_paddle2Pos -= _paddle2Vel;

	// Set the new positions of the paddles
	_paddleSprite1.setPosition(sf::Vector2f(20, _paddle1Pos));
	_paddleSprite2.setPosition(sf::Vector2f( _theApp._windowWidth - _paddleWidth - 20, _paddle2Pos));

	//////////////////////////
	/* Update ball position */
	//////////////////////////

	// Check X and Y position of ball
	_ballXPos += _ballXVel;
	_ballYPos += _ballYVel;

	// Get rectangles of ball and paddles for collision detection
	sf::FloatRect paddle1Rect = _paddleSprite1.getGlobalBounds();
	sf::FloatRect paddle2Rect = _paddleSprite2.getGlobalBounds();
	sf::FloatRect ballRect = _ball.getGlobalBounds();

	// Check if ball has touched the left or right side of the screen
	if( _ballXPos + _ball.getRadius() * 2 > _theApp._windowWidth or _ballXPos < 0 )
		_ballXVel *= -1;
	else if( _ballYPos + _ball.getRadius() * 2 > _theApp._windowHeight or _ballYPos < 0 )
		_ballYVel *= -1;
	// Check if the ball has collided with the paddles
	else if( paddle1Rect.intersects(ballRect) or paddle2Rect.intersects(ballRect))
	{
		// Not quite sure why, by we need to overcomposate moving the ball backwards
		// by multiplying the velocity by 2 when the ball collides with the paddles.
		// Perhaps because it's a circle and SFML circles are weird.
		_ballXPos -= _ballXVel * 2;
		_ballXVel *= -1;
	}

	// Set the new position of the ball
	_ball.setPosition(sf::Vector2f(_ballXPos, _ballYPos));


}

void PlayState::update_variable(float elapsedTime)
{

}

void PlayState::draw(void)
{
	// Draw the paddles and the ball
	_theApp._window.clear(sf::Color::Black);
	_theApp._window.draw(_paddleSprite1);
	_theApp._window.draw(_paddleSprite2);
	_theApp._window.draw(_ball);

}

void PlayState::handle_cleanup(void)
{

}