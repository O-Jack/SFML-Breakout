#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject(std::string obj_id="") :
	_id(obj_id),
	_is_loaded(false),
	_status(ACTIVE)
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

/* Dependent on the object, pass time elapsed since object was last drawn so change occurs with respect to time
 * instead of with respect to CPU clock cycles (non-constant across machines)
 */
void VisibleGameObject::update(float elapsed_time)
{
}

void VisibleGameObject::set_id(std::string obj_id)
{
	_id = obj_id;
}

/* Sets x and y position of this object's sprite */
void VisibleGameObject::set_position(int x, int y)
{
	if (_is_loaded)
		_sprite.setPosition(x, y);
}

void VisibleGameObject::set_status(ObjectStatus new_status)
{
	_status = new_status;
}

std::string VisibleGameObject::get_id() const
{
	return _id;
}

sf::Vector2f VisibleGameObject::get_position() const
{
	if (_is_loaded)
		return _sprite.getPosition();
	else
		return sf::Vector2f();
}

float VisibleGameObject::get_width() const
{
	if (_is_loaded)
		return _sprite.getLocalBounds().width;
	else
		return 0.0;
}

float VisibleGameObject::get_height() const
{
	if (_is_loaded)
		return _sprite.getLocalBounds().height;
	else
		return 0.0;
}

bool VisibleGameObject::is_loaded() const
{
	return _is_loaded;
}

sf::FloatRect VisibleGameObject::get_global_bound() const
{
	return _sprite.getGlobalBounds();
}

sf::Sprite& VisibleGameObject::get_sprite()
{
	return _sprite;
}

VisibleGameObject::ObjectStatus VisibleGameObject::get_status() const
{
	return _status;
}
