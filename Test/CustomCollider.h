#pragma once
#include "Collider.h"
class CustomCollider : public Collider
{
public:
	CustomCollider();
	void Init(std::shared_ptr<GameObject> _gameObject, std::vector<sf::Vector2f> allPoints);
private:

	void Start() override;
	void ColliderUpdate(float deltaTime) override;

};

