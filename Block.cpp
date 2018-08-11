#include "stdafx.h"
#include "Block.h"

Block::Block(sf::Color block_color, std::string obj_id = "") :
	VisibleGameObject(obj_id)
{
	/* Load sprite image and set origin to center of sprite */
	load("Images/block-basic.png");
	assert(is_loaded());
	
	get_sprite().setOrigin(get_width() / 2, get_height() / 2);

	/* Set color of block */
	get_sprite().setColor(block_color);
}

Block::~Block()
{
}

/* Check if this block intersects with Ball object, and mark it to be removed */
void Block::update(float time)
{
	//GameObjectManager& obj_manager = Game::get_obj_manager();
	//Ball* ball = dynamic_cast<Ball*>(obj_manager.get("ball"));

	///* Block cannot remove itself, since GameObjectManager is currently iterating over all game objects;
	// * instead, mark block and let GameObjectManager handle actual removal
	// */
	//if (get_global_bound().intersects(ball->get_global_bound()))
	//	set_status(VisibleGameObject::INACTIVE);

	/* TODO: add scoring system, adding points when a block is hit */
}
