#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GraphicDebugger.h"
#include "PhysicsEngine.h"
#include "ArrowComponent.h"
#include "VisualForceArrow.h"
#include "SceneManager.h"

class GameScene : public Scene
{
public:
	GameScene();

	void InitializeScene(sf::RenderWindow* _window) override;
	void Update(float deltaTime) override;

	void GameLoop(float deltaTime);

	void DestroyScene() override;
	void OnKeyDown(sf::Keyboard::Key pressedKey) override;
	void OnPlayerCollisionEnter(Collider* _collideWith, sf::Vector2f _collisionPoint);
	std::shared_ptr<Collider> playerCollider;
protected:
	virtual void SetupMapElements() = 0;
	virtual void SetupElements() = 0;

	void OnSceneChanged();


	std::shared_ptr<GameObject> mainCameraObject;
	Camera mainCamera;
	PhysicsEngine physicsEngine;
	GraphicDebugger graphicDebugger;
	std::shared_ptr<GameObject> Player;
	std::shared_ptr<GameObject> directionArrow;
	std::shared_ptr<GameObject> forceArrow;
	ArrowComponent arrowComponent;
	VisualForceArrow arrowVisual;
	std::shared_ptr<GameObject> BackgroundObject;

	std::shared_ptr<GameObject> CreateBackground();
	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CircleCollider>> CreatePlayer();
	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<GameObject>> CreateArrows(std::shared_ptr<GameObject> _player, std::shared_ptr<Collider> _playerCollider, ArrowComponent& arrowComponent, VisualForceArrow& arrowVisual, int MaxThrows);
	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> CreateTarget();

	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> CreatePlatformeOne();
	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> CreatePlatformeTwo();
	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> CreatePlatformeThree();
	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> CreatePlatformeFour();


	int currentLevel;


	sf::Font font;
	sf::Text ThrowsText;
};