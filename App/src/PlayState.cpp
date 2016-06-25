

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
	_ballYVel(0),
	_p1Score(0),
	_p2Score(0)
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
	if( _ballXPos + _ball.getRadius() * 2 > _theApp._windowWidth or _ballXPos < 0 ){
		//_ballXVel *= -1;
		_ballXPos = _theApp._windowWidth / 2;
		_ballYPos = _theApp._windowHeight / 2;
	}
	else if( _ballYPos + _ball.getRadius() * 2 > _theApp._windowHeight or _ballYPos < 0 )
		_ballYVel *= -1;
	// Check if the ball has collided with the paddles
	else if( paddle1Rect.intersects(ballRect) or paddle2Rect.intersects(ballRect))
	{
		// Not quite sure why, by we need to overcomposate moving the ball backwards
		// by multiplying the velocity by 2 when the ball collides with the paddles.
		// Perhaps because it's a circle and SFML circles are weird.
		/*_ballXPos -= _ballXVel * 2;
		_ballXVel *= -1;*/

		bool hitsX;
		bool hitsTop;
		bool hitsBottom;
		int centerX = _ballXPos + _ball.getRadius();
		int centerY = _ballYPos + _ball.getRadius();


		if(paddle1Rect.intersects(ballRect)){
			
			//so long as the ball hits no greater than 45 deg above or below the top or bottom respectively
			//it will reflect xvel (.707 ~ cos(45))
			/*hitsX = (int) (centerX - (_ball.getRadius() * 0.707f)) >= 20 + _paddleWidth;
			hitsY = (int) (centerY - (_ball.getRadius() * 0.707f)) >= _paddle1Pos + _paddleHeight
					or (int) (centerY + (_ball.getRadius() * 0.707f)) <= _paddle1Pos;//hits bottom or top in that order*/

			//If the ball hits between the center and the left edge x values
			hitsX = (20 + _paddleWidth) <= _ballXPos + _ball.getRadius() and (20 + _paddleWidth) >= _ballXPos;
			//hitsY = (_paddle1Pos + _paddleHeight >= _ballYPos and _paddle1Pos + _paddleHeight <= _ballYPos - _ball.getRadius())
					//or (_paddle1Pos <= _ballYPos + (2 * _ball.getRadius()) and _paddle1Pos >= _ballYPos + _ball.getRadius());//Hits bottom or top respectively

			//If it hits between the top edge and center y values of the ball respectively
			hitsBottom = _paddle1Pos + _paddleHeight >= _ballYPos and _paddle1Pos + _paddleHeight <= _ball.getRadius() + _ballYPos;

			//If it hits between the bottom edge and center y values of the ball respectively
			hitsTop = _paddle1Pos <= _ballYPos + (2 * _ball.getRadius()) and _paddle1Pos >= _ballYPos + _ball.getRadius();

			/*if(centerX >= 20){//if the center is to the right of the paddle, reflect x
				_ballXPos -= _ballXVel * 2;
				_ballXVel *= -1;
			}

			if((_paddle1Pos - centerY <= _ball.getRadius() and _paddle1Pos - centerY >= 0)or 
					(centerY - _paddle1Pos + _paddleHeight <= _ball.getRadius()) 
					and centerY - _paddle1Pos + _paddleHeight >= 0){//if center is within one radius of top or bottom of paddle

				_ballYPos -= _ballYVel * 2;
				_ballYVel *= -1;
			}*/

		} else {//if it hits paddle2

			int paddle2X = _theApp._windowWidth - _paddleWidth - 20;

			/*if(paddle2X - centerX <= _ball.getRadius() and paddle2X - centerX >= 0){//if the center is within one radius of the inside of the paddle
				_ballXPos -= _ballXVel * 2;
				_ballXVel *= -1;

			} else if((_paddle2Pos - centerY <= _ball.getRadius() and _paddle2Pos - centerY >= 0) or 
					(centerY - _paddle2Pos + _paddleHeight <= _ball.getRadius() 
					and centerY - _paddle2Pos + _paddleHeight >= 0)){//if center is within one radius of top or bottom of paddle

				_ballYPos -= _ballYVel * 2;
				_ballYVel *= -1;
			}*/

			//uses same idea as above in paddle1
			hitsX = paddle2X <= _ballXPos + (2 * _ball.getRadius()) and paddle2X >= _ballXPos +  _ball.getRadius();//if it hits within one radius to the		                      
			                                                                                                       //right of the center
			//hitsY = (_paddle2Pos + _paddleHeight >= _ballYPos and _paddle2Pos + _paddleHeight <= _ballYPos - _ball.getRadius()) 
					//or (_paddle2Pos <= _ballYPos + (2 * _ball.getRadius()) and _paddle2Pos >= _ballYPos + _ball.getRadius());//hits bottom or top respectively
			hitsBottom = _paddle2Pos + _paddleHeight >= _ballYPos and _paddle2Pos + _paddleHeight <= _ball.getRadius() + _ballYPos;

			hitsTop = _paddle2Pos <= _ballYPos + (2 * _ball.getRadius()) and _paddle2Pos >= _ballYPos + _ball.getRadius();
		}

		if(hitsX){
			_ballXPos -= 2 * _ballXVel;
			_ballXVel *= -1;
		}

		if(hitsBottom){
			_ballYVel = 5;
			_ballYPos += 2 * _ballYVel;
		}

		if(hitsTop){
			_ballYVel = -5;
			_ballYPos += 2* _ballYVel;
		}
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