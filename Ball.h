#pragma once
#include "VisibleGameObject.h"

class Ball : public VisibleGameObject {
public:
	Ball();
	virtual ~Ball();

	void update(float elapsed_time);

private:
	/*float _velocity_x;
	float _velocity_y;*/

	float _velocity;
	float _angle;
	float _elapsed_time_since_start;

	float linear_vel_x(float angle);
	float linear_vel_y(float angle);
};