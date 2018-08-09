#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

/* Free all game objects currently stored in manager */
GameObjectManager::~GameObjectManager()
{
	/* for_each applies given unary function (functor) to each dereferenced value 
	 * of given iterator range
	 */
	std::for_each(_game_objects.begin(), _game_objects.end(), GameObjectDeallocator());
}

/* Add game object to manager */
void GameObjectManager::add(std::string name, VisibleGameObject * obj)
{
	/* Object key must be unique in order to be inserted */
	if (_game_objects.find(name) == _game_objects.end())
		_game_objects.insert(std::pair<std::string, VisibleGameObject *>(name, obj));
}

/* Remove and free game object from manager */
void GameObjectManager::remove(std::string name)
{
	/* Object key must be in map in order to be removed */
	auto result = _game_objects.find(name);
	if (result != _game_objects.end()) {
		delete result->second;
		_game_objects.erase(name);
	}
}

/* Return number of game objects currently stored in manager */
int GameObjectManager::size() const
{
	return _game_objects.size();
}

/* Retrieve pointer to game object by name */
VisibleGameObject * GameObjectManager::get(std::string name)
{
	/* Object key must be in map in order for value to be retrieved */
	if (_game_objects.find(name) != _game_objects.end())
		return _game_objects[name];
	else
		return NULL;
}

/* Update all game objects, and remove any inactive ones */
void GameObjectManager::update_all(float elapsed_time)
{
	for (auto it = _game_objects.begin(); it != _game_objects.end(); it++) {
		it->second->update(elapsed_time);
	}

	auto it = _game_objects.begin();
	auto temp = _game_objects.begin();
	while (it != _game_objects.end()) {
		if (it->second->get_status() == VisibleGameObject::INACTIVE) {
			temp = it;
			it++;
			remove(temp->second->get_id());
		}
		else
			it++;
	}
}

/* Draw all game objects currently stored in manager to given window */
void GameObjectManager::draw_all(sf::RenderWindow & window)
{
	for (auto it = _game_objects.begin(); it != _game_objects.end(); it++) {
		it->second->draw(window);
	}
}

std::unordered_map<std::string, VisibleGameObject*>::iterator GameObjectManager::begin()
{
	return _game_objects.begin();
}

std::unordered_map<std::string, VisibleGameObject*>::iterator GameObjectManager::end()
{
	return _game_objects.end();
}
