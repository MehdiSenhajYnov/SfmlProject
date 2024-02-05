#pragma once
#include "Component.h"
#include "Collider.h"
class ArrowComponent : public Component
{
public:
	// Hérité via Component
	void Start() override;
	void Update(float deltaTime) override;
	void InitComponent(std::shared_ptr<GameObject> _gameObject, std::shared_ptr<GameObject> _player, std::shared_ptr<Collider> _playerCollider, int _maxThrows);

	float GetCurrentForce();
	float GetOldCurrentForce();

	void CheckIfPlayerIsInIdle();

	bool PlayerIsInIdle;

	int GetMaxThrows();
	int GetCurrentThrows();
private:
	float currentForce;
	float oldCurrentForce;
	std::shared_ptr<GameObject> player;
	bool isMousePressed;
	sf::Vector2i MouseInitialPosition;
	sf::Vector2i forceToGive;
	float currentAngle;
	std::shared_ptr<Collider> playerCollider;

	int maxThrows;
	int currentThrows;

	bool PlayerIsInIdleShort;

	sf::Vector2f oldPlayerPosition;
	int counterOffSamePosition;

	bool rightMouseClicked;

};

