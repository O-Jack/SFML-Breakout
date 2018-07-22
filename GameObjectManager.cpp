#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::add(std::string name, VisibleGameObject * obj)
{
}

void GameObjectManager::remove(std::string name)
{
}

int GameObjectManager::size() const
{
	return 0;
}

VisibleGameObject * GameObjectManager::get(std::string name)
{
	return nullptr;
}

void GameObjectManager::draw_all(sf::RenderWindow & window)
{
}
