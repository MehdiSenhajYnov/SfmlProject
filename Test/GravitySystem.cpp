#include "GravitySystem.h"
#include <iostream>

GravitySystem::GravitySystem()
{

}

void GravitySystem::Init(std::shared_ptr<GameObject> _gameObject, BoxCollider* _boxCollider, PhysicsEngine* _physicsEngine)
{
	boxCollider = _boxCollider; 
	physicsEngine = _physicsEngine; 
	gravityForce = 9.0f; 
	isGravityEnable = true; 
	canBounce = true; 
	multiplier = 100;

	LoadComponentBase(_gameObject);
	minY = gameObject->GetPosition().y;
}

void GravitySystem::Start()
{
}

void GravitySystem::Update(float deltaTime)
{
	if (gameObject->GetPosition().y > maxY)
	{
		multiplier = -100;
	}
	if (gameObject->GetPosition().y < minY)
	{
		multiplier = 100;
	}

	//gameObject->Move(0, gravityForce * multiplier * deltaTime);
	//physicsEngine->MoveObject(boxCollider, sf::Vector2f(0,gravityForce * multiplier * deltaTime));
}

void GravitySystem::SetGravity(float _newGravityForce)
{
	gravityForce = _newGravityForce;
}
