#pragma once
#include "VisibleGameObject.h"
#include "Game.h"

/* Note that only public members of Base class are inherited 
 * (ie: interface functions), so complexity is hidden from 
 * Derived class
 */
class Paddle : public VisibleGameObject {
public:
	Paddle(std::string obj_id);
	~Paddle();

	void update(float elapsed_time);
	float get_velocity() const;

private:
	float _velocity;	/* (-): left, (+): right */
	float _max_velocity;
};