#pragma once
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include "Component.h"

class Scene
{
public:
	std::shared_ptr<GameObject> CreateGameObject(std::string _gameObjectName);
	void RemoveGameObject(std::shared_ptr<GameObject> _gameObjectToAdd);
	std::map<std::shared_ptr<GameObject>, std::vector<Component*>> GetAllGamesObjectsComponents();
	void CalUpdateOnAll(float deltaTime);
	virtual void Update(float deltaTime) = 0;

	void AddComponent(std::shared_ptr<GameObject> _gameObject, Component* _component);
	void RemoveComponent(std::shared_ptr<GameObject> _gameObject, Component* _component);
	virtual void InitializeScene(sf::RenderWindow* _window) = 0;
	virtual void DestroyScene() = 0;

	virtual void OnKeyDown(sf::Keyboard::Key pressedKey) = 0;

protected:
	sf::RenderWindow* window;
	std::map<std::shared_ptr<GameObject>, std::vector<Component*>> gamesObjectsComponents;
};

