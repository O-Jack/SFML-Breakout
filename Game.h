#pragma once
#include "stdafx.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameObjectManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Logger.h"

/* Game class for state-driven implementation of Breakout */

class Game {
public:
	static void start();

	/* Parameters */
	static const int WINDOW_WIDTH;
	static const int WINDOW_HEIGHT;
	static const int WINDOW_BPP;		/* Bits per pixel */
	static const int PADDLE_Y_POS;

	/* Getters, must be declared static to access static member variables */
	static GameObjectManager& get_obj_manager();
	static Logger& get_logger();
	

private:
	/* Game states */
	enum GameState {
		UNINITIALIZED,
		SPLASHSCREEN,
		PAUSED,
		MENU,
		PLAYING,
		EXITING
	};

	/* Static member variables:
	 * Declared only once, scope lasts through lifetime of program.
	 * All instances of a class share the same static member variable.
	 * Must be initialized and accessed using class name and scope resolution operator.
	 */
	static GameState _state;
	static sf::RenderWindow _main_window;
	static sf::Clock _clock;
	static Logger _logger;
	static GameObjectManager _obj_manager;

	/* Static member functions:
	 * Class functions, do not depend on instances (no this pointer, access using scope resolution).
	 * Only allowed to access other static data members and functions.
	 */
	static bool is_exiting();
	static void game_loop();
	static void show_splash_screen();
	static void show_main_menu();
	static void create_blocks();
};

/* Note: all members are static, essentially turns class into a namespace */