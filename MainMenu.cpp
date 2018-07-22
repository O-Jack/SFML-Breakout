#include "stdafx.h"
#include "MainMenu.h"

/* Renders menu elements to window and displays it */
MainMenu::MenuResult MainMenu::show(sf::RenderWindow &window) {
	/* Load menu image from a file and construct sprite */
	sf::Texture menu_texture;
	menu_texture.loadFromFile("Images/main-menu.png");
	sf::Sprite menu_sprite(menu_texture);

	/* Set up clickable dimensions of menu items */
	MenuItem play_button;
	play_button.rect.top = 145;
	play_button.rect.height = 235;
	play_button.rect.left = 0;
	play_button.rect.width = 1023;
	play_button.action = PLAY;

	MenuItem exit_button;
	exit_button.rect.top = 145;
	exit_button.rect.height = 235;
	exit_button.rect.left = 0;
	exit_button.rect.width = 1023;
	exit_button.action = EXIT;

	_menu_items.push_back(play_button);
	_menu_items.push_back(exit_button);

	/* Render main menu to window and display */
	window.draw(menu_sprite);
	window.display();

	return get_menu_response(window);
}

/* Handles menu events and returns result */
MainMenu::MenuResult MainMenu::get_menu_response(sf::RenderWindow &window) {
	sf::Event menu_event;

	while (true) {
		/* Poll for click events */
		while (window.pollEvent(menu_event)) {
			if (menu_event.type == sf::Event::MouseButtonPressed)
				/* Access x and y coordinates of click through mouseButton attribute of event */
				return click_handler(menu_event.mouseButton.x, menu_event.mouseButton.y);
			else if (menu_event.type == sf::Event::Closed)
				return EXIT;
		}
	}
}

/* Checks region of mouse click and returns appropriate menu result */
MainMenu::MenuResult MainMenu::click_handler(int x, int y) {
	std::list<MenuItem>::iterator it;
	sf::Rect<int> item_rect;

	/* Iterate over each item in menu */
	for (it = _menu_items.begin(); it != _menu_items.end(); it++) {
		item_rect = it->rect;

		/* If click falls within menu item dimensions, return menu item's action */
		if (item_rect.contains(x, y))
			return it->action;
	}

	/* If click doesn't fall within any item dimensions, return NONE */
	return MainMenu::NONE;
}