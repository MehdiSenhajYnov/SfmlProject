#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GraphicDebugger.h"
#include "PhysicsEngine.h"

class GameScene : public Scene
{
public:
	GameScene();

	void InitializeScene(sf::RenderWindow* _window) override;
	void Update(float deltaTime) override;

	void KeyboardEvents();

	void GameLoop(float deltaTime);

	void DestroyScene() override;
	void OnKeyDown(sf::Keyboard::Key pressedKey) override;
	void OnPlayerCollisionEnter(Collider* _collideWith, sf::Vector2f _collisionPoint);
	std::shared_ptr<CircleCollider> playerCollider;
private :
	std::shared_ptr<GameObject> mainCameraObject;
	Camera mainCamera;
	PhysicsEngine physicsEngine;
	GraphicDebugger graphicDebugger;
	sf::Vector2i MouseInitialPosition;
	float currentAngle;
	bool isMousePressed;
	sf::Vector2i forceToGive;
	std::shared_ptr<GameObject> Player;
	std::shared_ptr<GameObject> directionArrow;
	std::shared_ptr<GameObject> forceArrow;
	float currentForce;
	float oldCurrentForce;

};

