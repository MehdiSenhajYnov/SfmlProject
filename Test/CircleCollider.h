#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "GameObject.h"
#include "Collider.h"
#include "MyMath.h"

class CircleCollider : public Collider
{
public:
	CircleCollider();
	void Init(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, float radius, int accuracy);
private:
	void Start() override;
	void ColliderUpdate(float deltaTime) override;
};

