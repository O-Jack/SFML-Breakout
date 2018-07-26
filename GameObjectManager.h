#pragma once
#include "VisibleGameObject.h"

/* Class for managing game objects; responsible for storing, updating, drawing, and removing
 * game objects (but not instantiating them).
 */

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, VisibleGameObject *obj);	/* Adds game object to manager */
	void remove(std::string name);						/* Removes game object from manager */
	int size() const;									/* Returns number of objects in manager */
	VisibleGameObject * get(std::string name);			/* Gets game object by name */
	void draw_all(sf::RenderWindow &window);			/* Draws all game objects to render window */

private:
	/* Map containing pointers to game objects, keyed by object name */
	std::unordered_map<std::string, VisibleGameObject *> _game_objects;

	/* Deallocator functor (class acting as function) for freeing game objects */
	struct GameObjectDeallocator {
		void operator()(const std::pair<std::string, VisibleGameObject *> &p) {
			delete p.second;
		}
	};
};
