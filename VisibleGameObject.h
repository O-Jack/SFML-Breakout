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
	virtual void update(float elapsed_time);

	virtual void set_position(int x, int y);
	virtual sf::Vector2f get_position() const;
	virtual bool is_loaded() const;

protected:
	sf::Sprite& get_sprite();

private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	std::string _filename;
	bool _is_loaded;
};
