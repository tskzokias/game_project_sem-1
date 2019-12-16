#include "GameObjectManager.h"

#include "..\GameObject.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	for (auto go : mGameObjects)
		delete go;

	mGameObjects.clear();
}

void GameObjectManager::AddGameObject(GameObject* pGameObject)
{
	mGameObjects.push_back(pGameObject);
}

std::vector<GameObject*> GameObjectManager::GetGameObjects()
{
	return mGameObjects;
}