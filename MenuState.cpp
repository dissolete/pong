#ifndef MENUSTATE_CPP
#define MENUSTATE_CPP

#include "States.hpp"

namespace crp{

MenuState::MenuState(std::string stateName, sf::RenderWindow & theWindow):
		crp::GameState(stateName, theWindow), atMenuScreen(true), atDifficultyScreen(false), atPlayerScreen(false){
			std::cout<<"In menuStateConstructor"<<std::endl;
		}

MenuState::~MenuState(){

    }

void MenuState::init(){

	//Loading fonts
	titleFont.loadFromFile("titleFont.ttf");
    dataFont.loadFromFile("dataFont.ttf");

    //Setup Title Text 
    menuTitleText.setFont(titleFont);
    menuTitleText.setString("Pong");
    menuTitleText.setCharacterSize(24);
    menuTitleText.setColor(sf::Color::White);
    titleRect = menuTitleText.getLocalBounds();
    menuTitleText.setOrigin(titleRect.left + titleRect.width/2, titleRect.top + titleRect.height/2);
    menuTitleText.setPosition(WINDOW_WIDTH_/2, 30);
    titleRect = menuTitleText.getGlobalBounds();

    //Setup Player Text
    menuPlayerText.setFont(dataFont);
    menuPlayerText.setString("Players");
    menuPlayerText.setCharacterSize(24);
    menuPlayerText.setColor(sf::Color::White);
    playerRect = menuPlayerText.getLocalBounds();
    menuPlayerText.setOrigin(playerRect.left + playerRect.width/2, playerRect.top + playerRect.height/2);
    menuPlayerText.setPosition(WINDOW_WIDTH_/2, 120);
    playerRect = menuPlayerText.getGlobalBounds();

    //Setup Computer option text
    menuComputerText.setFont(dataFont);
    menuComputerText.setString("Single Player");
    menuComputerText.setCharacterSize(24);
    menuComputerText.setColor(sf::Color::White);
    computerRect = menuComputerText.getLocalBounds();
    menuComputerText.setOrigin(computerRect.left + computerRect.width/2, computerRect.top + computerRect.height/2);
    menuComputerText.setPosition(WINDOW_WIDTH_/2, 90);
    computerRect = menuComputerText.getGlobalBounds();

    //Setup multiPlayer text
    menuMultiPlayerText.setFont(dataFont);
    menuMultiPlayerText.setString("MultiPlayer");
    menuMultiPlayerText.setCharacterSize(24);
    menuMultiPlayerText.setColor(sf::Color::White);
    multiPlayerRect = menuMultiPlayerText.getLocalBounds();
    menuMultiPlayerText.setOrigin(multiPlayerRect.left + multiPlayerRect.width/2, multiPlayerRect.top + multiPlayerRect.height/2);
    menuMultiPlayerText.setPosition(WINDOW_WIDTH_/2, 200);
    multiPlayerRect = menuMultiPlayerText.getGlobalBounds();

    //Setup difficulty text
    difficultyText.setFont(dataFont);
    difficultyText.setString("Difficulty");
    difficultyText.setCharacterSize(24);
    difficultyText.setColor(sf::Color::White);
    difficultyRect = difficultyText.getLocalBounds();
    difficultyText.setOrigin(difficultyRect.left + difficultyRect.width/2, difficultyRect.top + difficultyRect.height/2);
    difficultyText.setPosition(WINDOW_WIDTH_/2, 200);
    difficultyRect = difficultyText.getGlobalBounds();

    //Setup hard level text
    hardDiffText.setFont(dataFont);
    hardDiffText.setString("Hard");
 	hardDiffText.setCharacterSize(24);
 	hardDiffText.setColor(sf::Color::White);
 	hardDiffRect = hardDiffText.getLocalBounds();
 	hardDiffText.setOrigin(hardDiffRect.left + hardDiffRect.width/2, hardDiffRect.top + hardDiffRect.height/2);
 	hardDiffText.setPosition(WINDOW_WIDTH_/2, 90);
 	hardDiffRect = hardDiffText.getGlobalBounds();

 	//Setup Normal level text
 	normalDiffText.setFont(dataFont);
 	normalDiffText.setString("Normal");
 	normalDiffText.setCharacterSize(24);
 	normalDiffText.setColor(sf::Color::White);
    normalDiffRect = normalDiffText.getLocalBounds();
    normalDiffText.setOrigin(normalDiffRect.left + normalDiffRect.width/2, normalDiffRect.top + normalDiffRect.height/2);
    normalDiffText.setPosition(WINDOW_WIDTH_/2, 200);
    normalDiffRect = normalDiffText.getGlobalBounds();

    //Setup Menu start text
    menuStartText.setFont(dataFont);
    menuStartText.setString("Start Game");
    menuStartText.setCharacterSize(24);
    menuStartText.setColor(sf::Color::White);
    startRect = menuStartText.getLocalBounds();
    menuStartText.setOrigin(startRect.left + startRect.width/2, startRect.top + startRect.height/2);
    menuStartText.setPosition(WINDOW_WIDTH_/2, WINDOW_HEIGHT_ - 30 );
    startRect = menuStartText.getGlobalBounds();

}

void MenuState::reinit(){}

void MenuState::deinit(){
 	deinit_ = true;
}

void MenuState::pause(){
	paused_ = true;
}

void MenuState::resume(){}

void MenuState::process_events(sf::Event & event){
 
 if( event.type == sf::Event::Closed ){
			deinit();
			pause();
		}

 else if (event.type == sf::Event::MouseButtonPressed){
 	if(playerRect.contains(mousePosition.x, mousePosition.y )&& atMenuScreen){
 		atMenuScreen = false;
 		atPlayerScreen = true;

 	//	std::cout<<"PLAYERS BUTTON IS BEING PRESSED"<<std::endl;
 	}
 	else if(difficultyRect.contains(mousePosition.x, mousePosition.y)&& atMenuScreen){
 		atMenuScreen = false;
 		atDifficultyScreen = true;
 	}
 	else if(computerRect.contains(mousePosition.x, mousePosition.y)&& atPlayerScreen){
 		atPlayerScreen = false;
 		atMenuScreen = true;

 		numPlayers = 1;
 	}
 	else if(multiPlayerRect.contains(mousePosition.x, mousePosition.y)&& atPlayerScreen){
 		atPlayerScreen = false;
 		atMenuScreen = true;

 		numPlayers = 2;
 	}
 	else if(normalDiffRect.contains(mousePosition.x, mousePosition.y)&& atDifficultyScreen){
 		atDifficultyScreen = false;
 		atMenuScreen = true;

 		//set level to normal
 	}
 	else if(hardDiffRect.contains(mousePosition.x, mousePosition.y)&& atDifficultyScreen){
 		atDifficultyScreen = false;
 		atMenuScreen = true;
 	}
 	else if(startRect.contains(mousePosition.x, mousePosition.y)&& atMenuScreen){
 		atMenuScreen = false;
 		//deinit?
 	}

 }
	
}

void MenuState::process_logic(){

	mousePosition = sf::Mouse::getPosition(window_);

	if(atMenuScreen){
		if(playerRect.contains(mousePosition.x, mousePosition.y)){
			menuPlayerText.setColor(sf::Color::Red);
			menuPlayerText.setStyle(sf::Text::Underlined);
		}
		else if(difficultyRect.contains(mousePosition.x, mousePosition.y)){
			difficultyText.setColor(sf::Color::Red);
			difficultyText.setStyle(sf::Text::Underlined);
		}
		else if(startRect.contains(mousePosition.x, mousePosition.y)){
			menuStartText.setColor(sf::Color::Red);
			menuStartText.setStyle(sf::Text::Underlined);
		}
		else{
			menuStartText.setColor(sf::Color::White);
			menuStartText.setStyle(sf::Text::Regular);
			menuPlayerText.setColor(sf::Color::White);
			menuPlayerText.setStyle(sf::Text::Regular);
			difficultyText.setColor(sf::Color::White);
			difficultyText.setStyle(sf::Text::Regular);
		}
	}
	else if(atPlayerScreen){
		if(computerRect.contains(mousePosition.x, mousePosition.y)){
			menuComputerText.setColor(sf::Color::Red);
			menuComputerText.setStyle(sf::Text::Underlined);
		}
		else if(multiPlayerRect.contains(mousePosition.x, mousePosition.y)){
			menuMultiPlayerText.setColor(sf::Color::Red);
			menuMultiPlayerText.setStyle(sf::Text::Underlined);
		}
		else{
			menuMultiPlayerText.setColor(sf::Color::White);
			menuMultiPlayerText.setStyle(sf::Text::Regular);
			menuComputerText.setColor(sf::Color::White);
			menuComputerText.setStyle(sf::Text::Regular);
		}
	}
	else if(atDifficultyScreen){
		if(hardDiffRect.contains(mousePosition.x, mousePosition.y)){
			hardDiffText.setColor(sf::Color::Red);
			hardDiffText.setStyle(sf::Text::Underlined);

		}
		else if(normalDiffRect.contains(mousePosition.x, mousePosition.y)){
			normalDiffText.setColor(sf::Color::Red);
			normalDiffText.setStyle(sf::Text::Underlined);
		}
		else{
			normalDiffText.setColor(sf::Color::White);
			normalDiffText.setStyle(sf::Text::Regular);
			hardDiffText.setColor(sf::Color::White);
			hardDiffText.setStyle(sf::Text::Regular);
		}
	}

}

void MenuState::render(){

	if(atMenuScreen){
		window_.clear(sf::Color::Black);
		window_.draw(menuTitleText);
		window_.draw(menuStartText);
		window_.draw(menuPlayerText);
		window_.draw(difficultyText);

		//std::cout <<"MENU SCREEN IS TRUE"<<std::endl;
	}
	else if(atPlayerScreen){
		window_.clear(sf::Color::Black);
		window_.draw(menuComputerText);
		window_.draw(menuMultiPlayerText);

		//std::cout <<"PLAYER SCREEN IS TRUE"<<std::endl;
	}
	else if(atDifficultyScreen){
		window_.clear(sf::Color::Black);
		window_.draw(hardDiffText);
		window_.draw(normalDiffText);


		//std::cout<<"AT DIFFICULTY SCREEN IS TRUE"<<std::endl;
	}

	window_.display();

}

void MenuState::cleanup(){

}

}

#endif