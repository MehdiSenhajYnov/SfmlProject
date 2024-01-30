#include "CircleCollider.h"

CircleCollider::CircleCollider()
{
}

void CircleCollider::Init(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, float radius, int accuracy)
{
	std::vector<sf::Vector2f> _allpoints = MyMath::GetPointsOfPolygonInCircle(_topLeftPoint,radius, accuracy);
	InitializeCollider(_gameObject, _allpoints);
}

void CircleCollider::Start()
{
}

void CircleCollider::ColliderUpdate(float deltaTime)
{
	if (shape_ptr != nullptr)
	{
		shape_ptr->setPosition(gameObject->GetPosition());
	}

}
