#include "stdafx.h"
#include "Block.h"

Block::Block(sf::Color block_color, std::string obj_id) :
	VisibleGameObject(obj_id)
{
	/* Load sprite image and set origin to center of sprite */
	load("Images/block.png");
	assert(is_loaded());
	
	get_sprite().setOrigin(get_width() / 2, get_height() / 2);

	/* Set color of block */
	get_sprite().setColor(block_color);
}

Block::~Block()
{
}

/* Check if this block intersects with Ball object, and erase / remove self from game if so */
void Block::update(float time)
{
	GameObjectManager& obj_manager = Game::get_obj_manager();
	Ball* ball = dynamic_cast<Ball*>(obj_manager.get("ball"));

	if (get_global_rect().intersects(ball->get_global_rect()))
		obj_manager.remove(get_id());

	/* TODO: add scoring system, adding points when a block is hit */
}
