#pragma once
#include "stdafx.h"

class MainMenu {
public:
	/* Return values that menu can return */
	enum MenuResult {
		NONE,
		EXIT,
		PLAY
	};

	/* Represents each item on the menu */
	struct MenuItem {
		sf::Rect<int> rect;		/* Dimensions of menu item */
		MenuResult action;		/* Value returned if menu item is clicked */
	};

	/* Shows menu on given RenderWindow */
	MenuResult show(sf::RenderWindow &window);

private:
	MenuResult get_menu_response(sf::RenderWindow &window);
	MenuResult click_handler(int x, int y);
	std::list<MenuItem> _menu_items;
};
