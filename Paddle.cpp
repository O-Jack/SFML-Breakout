#include "stdafx.h"
#include "Paddle.h"
#include "Game.h"

Paddle::Paddle() :
	_velocity(0),
	_max_velocity(600)
{
	/* Load paddle with its sprite */
	load("Images/paddle-basic.png");
	assert(is_loaded());
	
	/* Set origin (center) of paddle to be the center of its sprite */
	float sprite_width = get_sprite().getGlobalBounds().width;
	float sprite_height = get_sprite().getGlobalBounds().height;
	get_sprite().setOrigin(sprite_width / 2, sprite_height / 2);

}

Paddle::~Paddle()
{
}

void Paddle::update(float elapsed_time)
{
	/* Update direction and magnitude of paddle velocity based on key pressed */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_velocity -= 3.0;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_velocity += 3.0;
	
	/* If no direction key is held down, stop moving paddle */
	else
		_velocity = 0.0;

	/* Limit magnitude of velocity */
	if (_velocity < -_max_velocity) _velocity = -_max_velocity;
	else if (_velocity > _max_velocity) _velocity = _max_velocity;

	/* Ensure that paddle does not go off bounds of screen */
	sf::Vector2f paddle_pos = get_position();
	if (paddle_pos.x <= get_sprite().getLocalBounds().width / 2 ||
		paddle_pos.x >= Game::WINDOW_WIDTH - get_sprite().getLocalBounds().width / 2)
		_velocity = 0.0;

	/* Update position based on velocity and time elapsed since last frame was drawn */
	get_sprite().move(sf::Vector2f(_velocity * elapsed_time, 0.0));
}

float Paddle::get_velocity() const
{
	return _velocity;
}
