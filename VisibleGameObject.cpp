#include "stdafx.h"
#include "VisibleGameObject.h"

/* Sets _is_loaded to false */
VisibleGameObject::VisibleGameObject() :
	_is_loaded(false)
{
	/* None */
}

VisibleGameObject::~VisibleGameObject()
{
	/* None */
}

/* Loads texture from designated file and constructs sprite */
void VisibleGameObject::load(std::string filename)
{
	if (_texture.loadFromFile(filename)) {
		_is_loaded = true;
		_filename = filename;
		_sprite.setTexture(_texture);
	}
	else {
		_is_loaded = false;
		_filename = "";
	}
}

/* Draws this object's sprite to given window */
void VisibleGameObject::draw(sf::RenderWindow & window)
{
	/* Only draw to window if a sprite has been loaded */
	if (_is_loaded)
		window.draw(_sprite);
}

void VisibleGameObject::update(float elapsed_time)
{
}

/* Sets x and y position of this object's sprite */
void VisibleGameObject::set_position(int x, int y)
{
	if (_is_loaded)
		_sprite.setPosition(x, y);
}

sf::Vector2f VisibleGameObject::get_position() const
{
	if (_is_loaded)
		return _sprite.getPosition();
	else
		return sf::Vector2f();
}

bool VisibleGameObject::is_loaded() const
{
	return _is_loaded;
}

sf::Sprite & VisibleGameObject::get_sprite()
{
	return _sprite;
}
