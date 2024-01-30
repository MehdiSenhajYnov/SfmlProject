#include "Scene.h"

std::shared_ptr<GameObject> Scene::CreateGameObject(std::string _gameObjectName)
{
	std::shared_ptr<GameObject> newGameObject = std::make_unique<GameObject>(_gameObjectName);
	gamesObjectsComponents[newGameObject] = std::vector<Component*>();
	return newGameObject;
}

void Scene::AddComponent(std::shared_ptr<GameObject> _gameObject, Component* _component)
{
	gamesObjectsComponents[_gameObject].push_back(_component);
}

void Scene::RemoveComponent(std::shared_ptr<GameObject> _gameObject, Component* _component)
{
	if (gamesObjectsComponents.contains(_gameObject))
	{
		for (int i = 0; i < gamesObjectsComponents[_gameObject].size(); i++)
		{
			if (gamesObjectsComponents[_gameObject][i] == _component)
			{
				gamesObjectsComponents[_gameObject].erase(gamesObjectsComponents[_gameObject].begin() + i);
				return;
			}
			gamesObjectsComponents.erase(_gameObject);
		}
	}
}



void Scene::RemoveGameObject(std::shared_ptr<GameObject> _gameObjectToRemove)
{
	gamesObjectsComponents.erase(_gameObjectToRemove);
}

std::map<std::shared_ptr<GameObject>, std::vector<Component*>> Scene::GetAllGamesObjectsComponents()
{
	return gamesObjectsComponents;
}

void Scene::CalUpdateOnAll(float deltaTime)
{
	for (auto& [_gameObject, components] : gamesObjectsComponents) 
	{
		for (int i = 0; i < components.size(); i++)
		{
			components[i]->Update(deltaTime);
		}

	}
}
