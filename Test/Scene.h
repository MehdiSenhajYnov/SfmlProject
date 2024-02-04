#pragma once
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include "Component.h"
#include "Event.h"


class Scene
{
public:
	virtual void InitializeScene(sf::RenderWindow* _window) = 0;

	std::shared_ptr<GameObject> CreateGameObject(std::string _gameObjectName, int ZIndex);
	void RemoveGameObject(std::shared_ptr<GameObject> _gameObjectToAdd);

	std::map<std::shared_ptr<GameObject>, std::vector<Component*>> GetAllGamesObjectsComponents();
	std::map<int, std::vector<std::shared_ptr<GameObject>>> GetAllGamesObjectsByZIndex();

	void AddComponent(std::shared_ptr<GameObject> _gameObject, Component* _component);
	void RemoveComponent(std::shared_ptr<GameObject> _gameObject, Component* _component);

	void CalUpdateOnAll(float deltaTime);
	virtual void Update(float deltaTime) = 0;

	virtual void OnKeyDown(sf::Keyboard::Key pressedKey) = 0;

	virtual void DestroyScene() = 0;

protected:

	bool sceneChanged;

	sf::RenderWindow* window;
	std::map<int, std::vector<std::shared_ptr<GameObject>>> gameObjectZIndex;
	std::map<std::shared_ptr<GameObject>, std::vector<Component*>> gamesObjectsComponents;
};

