#pragma once
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{

}

void BoxCollider::Init(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, sf::Vector2f _bottomRightPoint)
{
	InitializeCollider(_gameObject,
		{
			_topLeftPoint, sf::Vector2f(_topLeftPoint.x,_bottomRightPoint.y),
			_bottomRightPoint, sf::Vector2f(_bottomRightPoint.x, _topLeftPoint.y)
		});

}




void BoxCollider::Start()
{
}

void BoxCollider::ColliderUpdate(float deltaTime)
{
	if (shape_ptr != nullptr)
	{
		shape_ptr->setPosition(gameObject->GetPosition());
	}
}


