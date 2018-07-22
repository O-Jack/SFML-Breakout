#pragma once
#include "stdafx.h"

/* Base class for game objects that need to be drawn to the screen (ie: paddle, ball) */
class VisibleGameObject {
public:
	VisibleGameObject();

	/* Virtual functions: signals to compiler to look in derived classes for
	 * implementation instead of using pointer type to determine which version
	 * to call.
	 */
	virtual ~VisibleGameObject();

	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow &window);
	virtual void set_position(int x, int y);

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	std::string _filename;
	bool _is_loaded;
};
