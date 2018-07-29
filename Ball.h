#pragma once
#include "VisibleGameObject.h"

class Ball : public VisibleGameObject {
public:
	Ball();
	virtual ~Ball();

	void update();

private:
	float _velocity_x;
	float _velocity_y;
};