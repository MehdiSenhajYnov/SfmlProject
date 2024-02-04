#include "CustomCollider.h"

CustomCollider::CustomCollider()
{
}

void CustomCollider::Init(std::shared_ptr<GameObject> _gameObject, std::vector<sf::Vector2f> allPoints)
{
	InitializeCollider(_gameObject, allPoints);
}

void CustomCollider::Start()
{
}

void CustomCollider::ColliderUpdate(float deltaTime)
{
	if (shape_ptr != nullptr)
	{
		shape_ptr->setPosition(gameObject->GetPosition());
	}
}
