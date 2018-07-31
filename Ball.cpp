#include "stdafx.h"
#include "Ball.h"
#include "Game.h"

Ball::Ball() :
	_velocity_x(-200.0),
	_velocity_y(-200.0)
{
	/* Load ball sprite and set origin to center */
	load("Images/ball-basic.png");
	assert(is_loaded());

	get_sprite().setOrigin(15, 15);
}

Ball::~Ball()
{
}

void Ball::update(float elapsed_time)
{
	/* Bounce by reversing velocity if ball collides with a wall */
	sf::Vector2f ball_pos = get_position();
	if (ball_pos.y - get_height() / 2 < 0.0 || ball_pos.y + get_height() / 2 > Game::WINDOW_HEIGHT)
		_velocity_y = -_velocity_y;
	if (ball_pos.x - get_width() / 2 < 0.0 || ball_pos.x + get_width() / 2 > Game::WINDOW_WIDTH)
		_velocity_x = -_velocity_x;

	get_sprite().move(_velocity_x * elapsed_time, _velocity_y * elapsed_time);
}
