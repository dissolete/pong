

#include "CRApp.hpp"
#include "PlayState.hpp"
#include "CRConstants.hpp"

PlayState::PlayState(const std::string stateID, CRE::App& theApp) :
	CRE::State(stateID, theApp),
	_paddleTexture(),
	_paddleSprite1(),
	_paddleSprite2(),
	_paddleHeight(60),
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
	_p2Score(0),
	_gameOver(false)
{

}

PlayState::~PlayState()
{
}

void PlayState::init(void)
{
	CRE::State::init();



	/*switch(_theApp._statManager.get_difficulty()){

		case CRE::DIFF_EASY:
			_paddleHeight = 60;
			break;

		case CRE::DIFF_HARD:
			_paddleHeight = 30;
			//for some reason _paddleHeight never gets set to 30 even though difficulty is set to hard
			break;

		/*default:
			_paddleHeight = 60;
	// 		break;*/
	// if(_theApp._statManager.get_difficulty() == CRE::DIFF_HARD){
	// 	_paddleHeight = 30;
	// } else {
	// 	_paddleHeight = 60;
	// }

	//}

	if( _paddleTexture.loadFromFile("resources/white_texture.png", sf::IntRect(10, 10, _paddleWidth, _paddleHeight)) )
	{
		if( _ballTexture.loadFromFile("resources/white_texture.png", sf::IntRect(10, 10, 10, 10)))
		{
				_paddleSprite1.setTexture(_paddleTexture);
				_paddleSprite2.setTexture(_paddleTexture);

				// Set the size of the sprites based on the game difficulty
				if( _theApp._statManager.get_difficulty() == CRE::DIFF_HARD )
				{
					_paddleSprite1.setScale(1, .5);
					_paddleSprite2.setScale(1, .5);
				}
				else
				{
					_paddleSprite1.setScale(1, 1);
					_paddleSprite2.setScale(1, 1);
				}
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

				//add text
				_theApp._textManager.add_text("p1ScoreText", "Player 1: 0", sf::Vector2f(70, _theApp._windowHeight - 20), 20);
				_theApp._textManager.add_text("p2ScoreText", "Player 2: 0", sf::Vector2f(_theApp._windowWidth - 70, _theApp._windowHeight - 20), 20);
				_theApp._textManager.add_text("gameOverText", "Game Over", sf::Vector2f(_theApp._windowWidth / 2, _theApp._windowHeight / 2 - 15), 30);
				_theApp._textManager.add_text("winnerText", "Player _ Wins!", sf::Vector2f(_theApp._windowWidth / 2, _theApp._windowHeight / 2 + 15), 30);

				//Initialize data member values
				_gameOver = false;
				_p1Score = _p2Score = 0;
				
		}
		else
			_theApp.quit(CRE::STATUS_ASSET_COULDNT_BE_LOADED);

	}
	else
		_theApp.quit(CRE::STATUS_ASSET_COULDNT_BE_LOADED);

	_theApp._soundManager.add_sound("Bounce", "resources/bounce.wav");
}

void PlayState::reinit(void)
{

}

void PlayState::pause(void)
{
	CRE::State::pause();
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
		else if( theEvent.key.code == sf::Keyboard::Escape && _gameOver){
			_theApp._stateManager.drop_active_state();
			_theApp._stateManager.set_active_state("MenuState");

			//remove text from text manager
			_theApp._textManager.remove_text("gameOverText");
			_theApp._textManager.remove_text("p1ScoreText");
			_theApp._textManager.remove_text("p2ScoreText");

			// remove sound
			_theApp._soundManager.remove_sound("Bounce");
		}


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
	if(not _gameOver){

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
		if( _ballXPos + _ball.getRadius() * 2 > _theApp._windowWidth){//right side

			// Play sound
			_theApp._soundManager.play_sound("Bounce");

			_p1Score++;
			//reset position of ball to the player that scored
			_ballXPos = 20 + _paddleWidth;
			_ballYPos = _paddle1Pos;
			_ballXVel = 5;
			_ballYVel = -5;

			//Update score text
			_theApp._textManager.get_text("p1ScoreText") -> setString("Player 1: " + std::to_string(_p1Score));//set to _p1Score

			if(_p1Score == 7)
				_gameOver = true;

		} else if(_ballXPos < 0){//left side
			// Play sound
			_theApp._soundManager.play_sound("Bounce");

			_p2Score++;
			//reset position of ball to the player that scored
			_ballXPos = _theApp._windowWidth - _paddleWidth - 20 - (2 * _ball.getRadius());
			_ballYPos = _paddle2Pos;
			_ballXVel = -5;
			_ballYVel = -5;

			if(_p2Score == 7)
				_gameOver = true;

			//Update score text
			_theApp._textManager.get_text("p2ScoreText") -> setString("Player 2: " + std::to_string(_p2Score));//set to _p2Score
		}else if( _ballYPos + _ball.getRadius() * 2 > _theApp._windowHeight or _ballYPos < 0 ){//ball collides with bottom or top respectively
			// Play sound
			_theApp._soundManager.play_sound("Bounce");

			_ballYVel *= -1;
		}
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

			if(paddle1Rect.intersects(ballRect)){
				
				//If the ball hits between the center and the left edge x values
				hitsX = (20 + _paddleWidth) <= _ballXPos + _ball.getRadius() and (20 + _paddleWidth) >= _ballXPos;

				//If it hits between the top edge and center y values of the ball respectively
				hitsBottom = _paddle1Pos + _paddleHeight >= _ballYPos and _paddle1Pos + _paddleHeight <= _ball.getRadius() + _ballYPos;

				//If it hits between the bottom edge and center y values of the ball respectively
				hitsTop = _paddle1Pos <= _ballYPos + (2 * _ball.getRadius()) and _paddle1Pos >= _ballYPos + _ball.getRadius();

			} else {//if it hits paddle2

				int paddle2X = _theApp._windowWidth - _paddleWidth - 20;

				//uses same idea as above in paddle1
				hitsX = paddle2X <= _ballXPos + (2 * _ball.getRadius()) and paddle2X >= _ballXPos +  _ball.getRadius();//if it hits within one radius to the		                      
				                                                                                                       //right of the center

				hitsBottom = _paddle2Pos + _paddleHeight >= _ballYPos and _paddle2Pos + _paddleHeight <= _ball.getRadius() + _ballYPos;

				hitsTop = _paddle2Pos <= _ballYPos + (2 * _ball.getRadius()) and _paddle2Pos >= _ballYPos + _ball.getRadius();
			}

			if(hitsX){
				// Play sound
				_theApp._soundManager.play_sound("Bounce");

				_ballXPos -= 2 * _ballXVel;
				_ballXVel *= -1;
			}

			if(hitsBottom){
				// Play sound
				_theApp._soundManager.play_sound("Bounce");

				_ballYVel = 5;
				_ballYPos += 2 * _ballYVel;
			}

			if(hitsTop){
				// Play sound
				_theApp._soundManager.play_sound("Bounce");
				
				_ballYVel = -5;
				_ballYPos += 2* _ballYVel;
			}
		}

		// Set the new position of the ball
		_ball.setPosition(sf::Vector2f(_ballXPos, _ballYPos));
	}

}

void PlayState::update_variable(float elapsedTime)
{

}

void PlayState::draw(void)
{
	if(CRE::State::is_init_complete()){
		// Draw the paddles and the ball
		_theApp._window.clear(sf::Color::Black);
		_theApp._window.draw(_paddleSprite1);
		_theApp._window.draw(_paddleSprite2);
		_theApp._window.draw(_ball);

		_theApp._textManager.draw_text("p1ScoreText");
		_theApp._textManager.draw_text("p2ScoreText");

		if(_gameOver){
			if(_p1Score == 7){
				_theApp._textManager.get_text("winnerText") -> setString("Player 1 Wins!");
			} else {
				_theApp._textManager.get_text("winnerText") -> setString("Player 2 Wins!");
			}
			_theApp._textManager.draw_text("gameOverText");
			_theApp._textManager.draw_text("winnerText");
		}
	}
}

void PlayState::handle_cleanup(void)
{

}