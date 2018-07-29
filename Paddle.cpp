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

void Paddle::update()
{
	/* Update direction and magnitude of paddle velocity based on key pressed */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity -= 20.0;
		Game::_logger.write("Left key pressed.");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			 !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity += 20.0;
		Game::_logger.write("Right key pressed.");
	}
	
	/* If no direction key is held down, stop moving paddle */
	else
		_velocity = 0.0;

	/* Limit magnitude of velocity */
	if (_velocity < -_max_velocity) _velocity = -_max_velocity;
	else if (_velocity > _max_velocity) _velocity = _max_velocity;

	/* Ensure that paddle does not go off bounds of screen (remember that origin is at center of paddle) */
	sf::Sprite& paddle_sprite = get_sprite();
	sf::Vector2f paddle_pos = get_position();
	float next_pos = paddle_pos.x + _velocity;
	if (next_pos < paddle_sprite.getLocalBounds().width / 2 ||
		next_pos > Game::WINDOW_WIDTH - paddle_sprite.getLocalBounds().width / 2)
	{
		_velocity = 0.0;

		if (next_pos < Game::WINDOW_WIDTH / 2)
			paddle_sprite.setPosition(paddle_sprite.getLocalBounds().width / 2, Game::PADDLE_Y_POS);
		else
			paddle_sprite.setPosition(Game::WINDOW_WIDTH - paddle_sprite.getLocalBounds().width / 2, Game::PADDLE_Y_POS);

		return;
	}
		
	/* Update position based on velocity and time elapsed since last frame was drawn */
	get_sprite().move(sf::Vector2f(_velocity, 0.0));
	/* TODO: Fix move, waiting and then inputting direction causes paddle to jump */
}

float Paddle::get_velocity() const
{
	return _velocity;
}
