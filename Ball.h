#pragma once
#include "VisibleGameObject.h"

class Ball : public VisibleGameObject {
public:
	Ball();
	virtual ~Ball();

	void update(float elapsed_time);

private:
	float _velocity_x;
	float _velocity_y;
};