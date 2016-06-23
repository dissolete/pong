#ifndef PONGAPP_HPP
#define PONGAPP_HPP

#include "CRApp.hpp"
#include "SplashState.hpp"
#include "PlayState.hpp"
#include "MenuState.hpp"

class PongApp : public CRE::App
{
	public:
		/**
		*
		*/
		PongApp(const std::string theTitle = "Pong by Code Red",
			int windowWidth = 800, int windowHeight = 600);

		/**
		*
		*/
		virtual ~PongApp();

	protected:
		/**
		*
		*/
		virtual void init_asset_handlers(void);

		/**
		*
		*/
		virtual void init_screen_factory(void);

		/**
		*
		*/
		virtual void handle_cleanup(void);

	private:
}; // class PongApp

#endif