#include "stdafx.h"
#include "Game.h"

/* Manually instantiate and initialize static member variables outside of class */
Game::GameState Game::_state = UNINITIALIZED;
sf::RenderWindow Game::_main_window;
sf::Clock Game::_clock;							/* Tracks time between drawing of frames */
GameObjectManager Game::_obj_manager;

const int Game::WINDOW_WIDTH = 1024;
const int Game::WINDOW_HEIGHT = 768;
const int Game::WINDOW_BPP = 32;
const int Game::PADDLE_Y_POS = 700;

void Game::start()
{
	/* Do nothing if game has already started */
	if (_state != UNINITIALIZED)
		return;

	/* Create main window with resolution of 1024x768 at 32bpp */
	_main_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP), "Breakout");

	/* Initialize game objects and add them to object manager */
	Paddle *paddle = new Paddle("paddle");
	paddle->set_position(WINDOW_WIDTH / 2, PADDLE_Y_POS);
	paddle->get_sprite().setColor(sf::Color::Cyan);
	_obj_manager.add(paddle->get_id(), paddle);

	Ball *ball = new Ball("ball");
	ball->set_position(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 15);
	ball->get_sprite().setColor(sf::Color::Red);
	_obj_manager.add(ball->get_id(), ball);

	create_blocks();

	/* Start by showing splash screen  */
	_state = SPLASHSCREEN;

	/* Keep executing game loop until state is changed to EXITING */
	_clock.restart();
	while (!is_exiting())
		game_loop();

	_main_window.close();
}

GameObjectManager & Game::get_obj_manager()
{
	return _obj_manager;
}

bool Game::is_exiting()
{
	return _state == EXITING;
}

void Game::game_loop()
{
	sf::Event curr_event;

	/* Pop event from event queue (curr_event will be default if event queue is empty) */
	_main_window.pollEvent(curr_event);

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
			_obj_manager.update_all(_clock.restart().asSeconds());		/* Pass time since clock was last restarted (in last loop iteration) */
			_obj_manager.remove_inactive();
			_obj_manager.draw_all(_main_window);
			_main_window.display();

			/* If window is closed (Closed event), switch to EXITING state */
			if (curr_event.type == sf::Event::Closed)
				_state = EXITING;
				
			/* If P key pressed, transition to MENU state */
			if (curr_event.type == sf::Event::KeyPressed)
				if (curr_event.key.code == sf::Keyboard::P)
					_state = MENU;

			break;
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

/* Creates Block objects and adds them to object manager */
void Game::create_blocks()
{
	/* Create first row of blocks (8 blocks per row) */
	for (int i = 0; i < 8; i++) {
		std::string block_name = "block_1-" + std::to_string(i + 1);

		Block *new_block = new Block(sf::Color::Red, block_name);
		new_block->set_position(new_block->get_width()/2 + i * new_block->get_width(), 60);

		_obj_manager.add(block_name, new_block);
	}

	/* Create second row of blocks */
	for (int i = 0; i < 8; i++) {
		std::string block_name = "block_2-" + std::to_string(i + 1);

		Block *new_block = new Block(sf::Color::Blue, block_name);
		new_block->set_position(new_block->get_width()/2 + i * new_block->get_width(), 60 + new_block->get_height());

		_obj_manager.add(block_name, new_block);
	}

	/* Create third row of blocks */
	for (int i = 0; i < 8; i++) {
		std::string block_name = "block_3-" + std::to_string(i + 1);

		Block *new_block = new Block(sf::Color::Green, block_name);
		new_block->set_position(new_block->get_width()/2 + i * new_block->get_width(), 60 + 2 * new_block->get_height());

		_obj_manager.add(block_name, new_block);
	}
}
