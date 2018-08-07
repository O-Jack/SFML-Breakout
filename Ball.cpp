#include "stdafx.h"
#include "Ball.h"

Ball::Ball(std::string obj_id = "") :
	/*_velocity_x(-200.0),
	_velocity_y(-200.0)*/
	VisibleGameObject(obj_id),
	_velocity(230.0),
	_elapsed_time_since_start(0)
{
	/* Load ball sprite and set origin to center */
	load("Images/ball-basic.png");
	assert(is_loaded());
	get_sprite().setOrigin(15, 15);

	/* Init. random angle for ball */
	_angle = Utility::rand_range(45, 135);
}

Ball::~Ball()
{
}

/* Simple update function */
//void Ball::update(float elapsed_time)
//{
//	/* Random variations to bounce velocity */
//	int rand_x_vel = Utility::rand_range(-50, 50);
//	int rand_y_vel = Utility::rand_range(-50, 50);
//
//	/* Bounce by reversing velocity if ball collides with a wall, randomly tweak velocity in other dimension */
//	sf::Vector2f ball_pos = get_position();
//	if (ball_pos.y - get_height() / 2 < 0.0 || ball_pos.y + get_height() / 2 > Game::WINDOW_HEIGHT) {
//		_velocity_y = -_velocity_y;
//		_velocity_x += rand_x_vel;
//	}
//		
//	if (ball_pos.x - get_width() / 2 < 0.0 || ball_pos.x + get_width() / 2 > Game::WINDOW_WIDTH) {
//		_velocity_x = -_velocity_x;
//		_velocity_y += rand_y_vel;
//	}
//
//	get_sprite().move(_velocity_x * elapsed_time, _velocity_y * elapsed_time);
//}

/* More complex update function */
void Ball::update(float elapsed_time) {
	_elapsed_time_since_start += elapsed_time;

	/* Don't move ball until we're at least 3 seconds in */
	if (_elapsed_time_since_start < 3.0)
		return;

	/* Calculate change in position */
	sf::Vector2f ball_pos = get_position();
	float delta_pos = _velocity * elapsed_time;
	float delta_pos_x = linear_vel_x(_angle) * delta_pos;
	float delta_pos_y = linear_vel_y(_angle) * delta_pos;

	/* Handle collision logic with top wall (and bottom for testing) */
	if (ball_pos.y - get_height()/2 + delta_pos_y <= 0 || ball_pos.y + get_height()/2 + delta_pos_y >= Game::WINDOW_HEIGHT) {
		/* Bounce */
		_angle = 360.0 - _angle;
		delta_pos_y *= -1;
	}

	/* Handle collision logic with left and right walls */
	if (ball_pos.x - get_width()/2 + delta_pos_x <= 0 || ball_pos.x + get_width()/2 + delta_pos_x >= Game::WINDOW_WIDTH) {
		/* Bounce */
		_angle = _angle + 180 - 2*_angle;
		delta_pos_x *= -1;
	}

	/* Handle collision logic with other game objects (paddle and blocks) */
	GameObjectManager& obj_manager = Game::get_obj_manager();
	for (auto it = obj_manager.begin(); it != obj_manager.end(); it++) {
		VisibleGameObject *curr = it->second;
		if (curr->get_id() != this->get_id() && get_global_rect().intersects(curr->get_global_rect())) {
			_angle = 360.0 - _angle;
			delta_pos_y *= -1;
		}
	}

	get_sprite().move(delta_pos_x, delta_pos_y);
}

/* Given angle, returns x-component multiplier of velocity (in radians) */
float Ball::linear_vel_x(float angle)
{
	if (angle < 0) angle += 360;
	return (float)std::cos(angle * 3.1415926 / 180.0);
}

/* Given angle, returns y-component multiplier of velocity (in radians) */
float Ball::linear_vel_y(float angle)
{
	if (angle < 0) angle += 360;
	return -1 * (float)std::sin(angle * 3.1415926 / 180.0);

	/* Return negative value for y dimension since positive = going down, negative = going up
	 * (makes angles a little easier to think about)
	 */
}


