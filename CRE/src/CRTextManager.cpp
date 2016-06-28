#include "CRTextManager.hpp"
#include "CRApp.hpp"

namespace CRE

{
	TextManager::TextManager() :
		_theApp(NULL),
		_texts(),
		_defaultFont()
	{}

	TextManager::~TextManager()
	{
		//deletes all texts
		//while there are still texts...
		while(not _texts.empty()){

			//Get the text at the back of the vector and then removes it
			Text * currText = _texts.back();
			_texts.pop_back();

			delete currText;
			currText = NULL;
		}

		_theApp = NULL;
	}

	void TextManager::register_app(App * theApp)
	{
		// Check that our pointer is good
        assert(NULL != theApp and "TextManager::register_app() theApp pointer provided is bad");

        // Make a note of the pointer
        assert(NULL == _theApp and "TextManager::register_app() theApp pointer was already registered");

        _theApp = theApp;
	}

	void TextManager::set_font(std::string fontResource)
	{
		if( not _defaultFont.loadFromFile(fontResource) )
			_theApp->quit(STATUS_FONT_COULDNT_BE_LOADED);
	}

//The reason this function does not call the next version of it by passing the default font is to save
//processing time with function calls. Not much space would be saved for a decrease in performance.
	void TextManager::add_text(std::string textID, std::string textString, sf::Vector2f coordinate, unsigned int charSize)
	{
		// Create the new Text object
		Text *newText = new Text(textID, textString, _defaultFont, charSize);

		// Set origin of the text to the absolute center of the text object
		sf::FloatRect textRect = newText->_text.getLocalBounds();
		newText->_text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);

		// Set text to the position provided
		newText->_text.setPosition(coordinate);

		// Add the new text object to the vector
		_texts.push_back(newText);
	}

	void TextManager::add_text(std::string textID, std::string textString, sf::Font theFont, 
				sf::Vector2f coordinate, unsigned int charSize)
	{
		// Creates the new Text object and adds it to the vector
		Text *newText = new Text(textID, textString, theFont, charSize);

		// Set origin of the text to the absolute center of the text object
		sf::FloatRect textRect = newText->_text.getLocalBounds();
		newText->_text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);

		// Set text to the position provided
		newText->_text.setPosition(coordinate);

		// Add the new text object to the vector
		_texts.push_back(newText);
	}

	void TextManager::draw_all_texts()
	{
		for( CRE::Text *text : _texts )
			_theApp->_window.draw(text -> _text);
	}

	void TextManager::draw_text(std::string textID)
	{
		//Tests texts until an ID matches (or the end is reached) and draws it
		//before exiting function
		for(CRE::Text *text : _texts){
			if(text -> get_ID() == textID){
				_theApp -> _window.draw(text -> _text);
				break;
			}
		}
	}

//NOTE: Relocates the text to the passed coordinate
	void TextManager::draw_text(std::string textID, sf::Vector2f coordinate)
	{
		//for each CRE::Text pointer...
		for(CRE::Text *text : _texts){
			//if the text pointer matches the ID...
			if(text -> get_ID() == textID){
				//move the text to passed position
				text -> _text.setPosition(coordinate);
				_theApp -> _window.draw(text -> _text);
				break;
			}
		}
	}

	void TextManager::remove_text(std::string textID)
	{
		for(auto it = _texts.begin(); it <= _texts.end(); it++){
			//if the iterator is on the passed ID, remove that Text
			if((*it) -> get_ID() == textID){

				// Get a pointer to this text
				Text * thisText = (*it);

				// Remove text from the list
				_texts.erase(it);

				// Delete the text object
				delete thisText;

				// Remove local pointer
				thisText = NULL;

				//No longer need to loop, assumes each textID is unique
				break;
			}
			
		}
	}

	void TextManager::set_style(std::string textID, sf::Uint32 style)
	{
		// Move through the texts
		for( Text * text : _texts )
		{
			// If we found the text we need...
			if( text->get_ID() == textID )
			{
				// set the style for the text
				text->_text.setStyle(style);

				// and break the for loop
				break;
			}
		}
	}

	void TextManager::set_color(std::string textID, const sf::Color & color)
	{
		// Move through texts
		for( Text * text : _texts )
		{
			// If we found the text we need...
			if( text->get_ID() == textID )
			{
				// set the color for the text
				text->_text.setColor(color);

				// and break from the for loop
				break;
			}
		}
	}

	bool TextManager::is_empty()
	{
		return _texts.empty();
	}

	sf::Text* TextManager::get_text(std::string textID)
	{
		for(CRE::Text *text : _texts){
			if(text -> get_ID() == textID)
				return &(text -> _text);
		}
	}
}