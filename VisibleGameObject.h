#pragma once
#include "stdafx.h"

/* Base class for game objects that need to be drawn to the screen (ie: paddle, ball) */
class VisibleGameObject {
public:
	VisibleGameObject(std::string obj_id);

	/* Virtual functions: signals to compiler to look in derived classes for
	 * implementation instead of using pointer type to determine which version
	 * to call.
	 */
	virtual ~VisibleGameObject();

	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow &window);
	virtual void update(float elapsed_time);

	/* Setters and Getters */
	virtual void set_id(std::string obj_id);
	virtual void set_position(int x, int y);

	virtual std::string get_id() const;
	virtual sf::Vector2f get_position() const;
	virtual float get_width() const;
	virtual float get_height() const;
	virtual bool is_loaded() const;
	virtual sf::FloatRect get_global_rect() const;
	virtual sf::Sprite& get_sprite() const;

private:
	std::string _id;
	sf::Texture _texture;
	sf::Sprite _sprite;
	std::string _filename;
	bool _is_loaded;
};
