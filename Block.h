#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include "Game.h"
#include "Ball.h"

/* Blocks which are broken when by ball */

class Block : public VisibleGameObject {
public:
	Block(sf::Color block_color, std::string obj_id);
	~Block();

	void update(float time);

private:
};