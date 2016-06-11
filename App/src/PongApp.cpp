#include "PongApp.hpp"

PongApp::PongApp(const std::string theTitle, int windowWidth, int windowHeight) :
	CRE::App(theTitle, windowWidth, windowHeight)
{}

PongApp::~PongApp()
{}

void PongApp::init_asset_handlers(void)
{}

void PongApp::init_screen_factory(void)
{
	// Add game states here
	_stateManager.add_active_state(new(std::nothrow) CRE::SplashState(*this));
}

void PongApp::handle_cleanup()
{
	// Destroy anything that was allocated in this class here
}