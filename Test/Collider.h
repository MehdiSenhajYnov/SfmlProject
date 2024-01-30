#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "GameObject.h"
#include "Component.h"
#include "Event.h"
#include "Camera.h"

class Collider : public Component
{
public:
	Collider();

	virtual ~Collider();
	std::shared_ptr<GameObject> GetAttachedObject();

	void SetVisible(bool _visibleState);

	std::vector<sf::Vector2f> GetAllPoints();
	std::vector<sf::Vector2f> GetAllPointsOnObject();
	sf::Vector2f GetCenter();

	std::vector<Collider*> GetCurrentCollisions();

	void AddInCollisionWith(Collider* ColliderToAdd, sf::Vector2f ContactPoint);
	void RemoveFromCollisionWith(Collider* ColliderToRemove);
	bool AlreadyColliding(Collider* ColliderToCheck);

	void AddForce(sf::Vector2f forceToAdd);

	void SetVelocity(sf::Vector2f newVelocity);
	void SetAcceleration(sf::Vector2f newAcceleration);

	sf::Vector2f GetVelocity();
	sf::Vector2f GetAcceleration();
	bool Gravity;

	Event<Collider*, sf::Vector2f>* OnCollisionEnter();
	Event<Collider*>* OnCollisionExit();


protected:
	void InitializeCollider(std::shared_ptr<GameObject> _gameObject, std::vector<sf::Vector2f> _allPoints);
	void CreateShape();
	std::vector<sf::Vector2f> allPoints;
	sf::Vector2f Center;

	std::vector<Collider*> currentCollisions;

	sf::ConvexShape* shape_ptr;
	sf::ConvexShape shape;

	bool Visible;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	void FireCollisionEnter(Collider* CollideWith, sf::Vector2f ContactPoint);
	void FireCollisionExit(Collider* CollideWith);

	// Hérité via Component
	virtual void Start() = 0;
	void Update(float deltaTime);
	virtual void ColliderUpdate(float deltaTime) = 0;
	const float frictionForce = 0.99f;
	const float gravityForce = 14;

	Event<Collider*, sf::Vector2f> onCollisionEnter;
	Event<Collider*> onCollisionExit;
};
