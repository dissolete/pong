#include "PongApp.hpp"

PongApp::PongApp(const std::string theTitle, int windowWidth, int windowHeight) :
	CRE::App(theTitle, windowWidth, windowHeight)
{}

PongApp::~PongApp()
{}

void PongApp::init_asset_handlers(void)
{
	_textManager.set_font("resources/cour.ttf");
}

void PongApp::init_screen_factory(void)
{

	_window.setKeyRepeatEnabled(false);

	// Add game states here
	_stateManager.add_active_state(new(std::nothrow) PlayState("PlayState", *this));
	_stateManager.add_active_state(new(std::nothrow) MenuState("MenuState", *this));
	_stateManager.add_active_state(new(std::nothrow) CRE::SplashState(*this));
}

void PongApp::handle_cleanup()
{
	// Destroy anything that was allocated in this class here
}