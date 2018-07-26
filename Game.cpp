#include "stdafx.h"
#include "Game.h"

void Game::start()
{
	/* Do nothing if game has already started */
	if (_state != UNINITIALIZED)
		return;

	/* Create main window with resolution of 1024x768 at 32bpp */
	_main_window.create(sf::VideoMode(1024, 768, 32), "Breakout");

	/* Initialize Paddle object and add it to object manager */
	Paddle *paddle = new Paddle();
	paddle->load("Images/paddle-basic.png");
	paddle->set_position(1024 / 2 - 45, 700);
	_obj_manager.add("paddle", paddle);

	/* Start by showing splash screen  */
	_state = SPLASHSCREEN;

	/* Keep executing game loop until state is changed to EXITING */
	while (!is_exiting())
		game_loop();

	_main_window.close();
}

bool Game::is_exiting()
{
	return _state == EXITING;
}

void Game::game_loop()
{
	sf::Event curr_event;

	/* Keep popping from event queue and processing while there are still events on the queue */
	while (_main_window.pollEvent(curr_event)) {
		/* Handle event based on what the current state of the game is */
		switch (_state) {
			case SPLASHSCREEN:
				show_splash_screen();
				break;
			case MENU:
				show_main_menu();
				break;
			case PLAYING:
				/* DEBUG: Clear screen with red and display it on window */
				_main_window.clear(sf::Color(0, 0, 0, 255));
				_obj_manager.draw_all(_main_window);
				_main_window.display();

				/* If window is closed (Closed event), switch to EXITING state */
				if (curr_event.type == sf::Event::Closed)
					_state = EXITING;
				
				/* If P key pressed, transition to MENU state */
				if (curr_event.type == sf::Event::KeyPressed)
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
						_state = MENU;

				break;
		}
	}
}

/* Instantiate a SplashScreen object and show it on _main_window */
void Game::show_splash_screen()
{
	SplashScreen splash_screen;
	splash_screen.show(_main_window);

	/* Change state to PLAY after return from SplashScreen's show function */
	_state = PLAYING;
}

/* Instantiate a MainMenu object and show it on _main_window */
void Game::show_main_menu()
{
	MainMenu main_menu;
	MainMenu::MenuResult result = main_menu.show(_main_window);

	/* Change states based on result of click event from main menu */
	switch (result) {
		case MainMenu::PLAY:
			_state = PLAYING;
			break;
		case MainMenu::EXIT:
			_state = EXITING;
			break;
	}
}

/* Manually instantiate and initialize static member variables outside of class */
Game::GameState Game::_state = UNINITIALIZED;
sf::RenderWindow Game::_main_window;
GameObjectManager Game::_obj_manager;