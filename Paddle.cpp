#include "stdafx.h"
#include "Paddle.h"

Paddle::Paddle(std::string obj_id = "") :
	VisibleGameObject(obj_id),
	_velocity(0),
	_max_velocity(600)
{
	/* Load paddle with its sprite */
	load("Images/paddle-basic.png");
	assert(is_loaded());
	
	/* Set origin (center) of paddle to be the center of its sprite */
	get_sprite().setOrigin(get_width() / 2, get_height() / 2);

}

Paddle::~Paddle()
{
}

void Paddle::update(float elapsed_time)
{
	sf::Sprite& paddle_sprite = get_sprite();
	sf::Vector2f paddle_pos = get_position();

	/* Update direction and magnitude of paddle velocity based on key pressed */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity -= 10.0;
		//Game::_logger << "Left key pressed.\n";
		std::cout << "Left key pressed (pos = " << paddle_pos.x << ", velocity = " << _velocity << ")\n";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			 !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity += 10.0;
		//Game::_logger << "Right key pressed.\n";
		std::cout << "Right key pressed (pos = " << paddle_pos.x << ", velocity = " << _velocity << ")\n";
	}
	
	/* If no direction key is held down, stop moving paddle */
	else
		_velocity = 0.0;

	/* Limit magnitude of velocity */
	if (_velocity < -_max_velocity) _velocity = -_max_velocity;
	else if (_velocity > _max_velocity) _velocity = _max_velocity;

	/* Ensure that paddle does not go off bounds of screen (remember that origin is at center of paddle) */
	float next_pos = paddle_pos.x + _velocity * elapsed_time;
	if (next_pos < paddle_sprite.getLocalBounds().width / 2 ||
		next_pos > Game::WINDOW_WIDTH - paddle_sprite.getLocalBounds().width / 2)
	{
		/* If paddle will go out of bounds, stop paddle and set position to be against the wall */
		_velocity = 0.0;

		if (next_pos < Game::WINDOW_WIDTH / 2)
			paddle_sprite.setPosition(paddle_sprite.getLocalBounds().width / 2, Game::PADDLE_Y_POS);
		else
			paddle_sprite.setPosition(Game::WINDOW_WIDTH - paddle_sprite.getLocalBounds().width / 2, Game::PADDLE_Y_POS);

		return;
	}
		
	/* Update position based on velocity and time elapsed since last frame was drawn */
	get_sprite().move(sf::Vector2f(_velocity * elapsed_time, 0.0));
}

float Paddle::get_velocity() const
{
	return _velocity;
}
