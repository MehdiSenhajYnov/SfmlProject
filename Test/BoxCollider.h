#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "GameObject.h"
#include "Component.h"
#include "Event.h"
#include "Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider();
	void Init(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, sf::Vector2f _bottomRightPoint);

private:

	void Start() override;
	void ColliderUpdate(float deltaTime) override;

};

