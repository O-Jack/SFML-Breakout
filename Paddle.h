#pragma once
#include "VisibleGameObject.h"

/* Note that only public members of Base class are inherited 
 * (ie: interface functions), so complexity is hidden from 
 * Derived class
 */
class Paddle : public VisibleGameObject {
public:
	Paddle();
	~Paddle();
};