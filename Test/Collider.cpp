#include "Collider.h"

Collider::Collider(){}



void Collider::InitializeCollider(std::shared_ptr<GameObject> _gameObject, std::vector<sf::Vector2f>  _allPoints)
{
	LoadComponentBase(_gameObject);

	allPoints = _allPoints;

	if (allPoints.size() == 0) return;
	float xSum = 0;
	float ySum = 0;
	for (int i = 0; i < allPoints.size(); i++)
	{
		xSum += allPoints[i].x;
		ySum += allPoints[i].y;
	}
	Center = sf::Vector2f(xSum / allPoints.size(), ySum / allPoints.size());
}


Collider::~Collider()
{

}

std::shared_ptr<GameObject> Collider::GetAttachedObject()
{
	return gameObject;
}

void Collider::SetVisible(bool _visibleState)
{
	Visible = _visibleState;

	if (Visible)
	{
		CreateShape();
		shape_ptr = &shape;
		Camera::AddToPermanentDrawablesObjects(shape_ptr, gameObject);

	}
	else
	{
		Camera::RemoveFromPermanentDrawablesObjects(shape_ptr);
		shape_ptr = nullptr;
	}

}

std::vector<sf::Vector2f> Collider::GetAllPoints()
{
	return allPoints;
}

std::vector<sf::Vector2f> Collider::GetAllPointsOnObject()
{
	auto toreturn = allPoints;
	for (int i = 0; i < toreturn.size(); i++)
	{
		toreturn[i] += gameObject->GetPosition();
	}
	return toreturn;
}

sf::Vector2f Collider::GetCenter()
{
	return Center;
}

std::vector<Collider*> Collider::GetCurrentCollisions()
{
	return currentCollisions;
}

void Collider::AddInCollisionWith(Collider* ColliderToAdd, sf::Vector2f ContactPoint)
{
	auto vectorToStr = [](sf::Vector2f toconvert) { return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); };

	currentCollisions.push_back(ColliderToAdd);
	//std::cout << "Collision enter between " << this->gameObject->Name << " and " << ColliderToAdd->gameObject->Name << std::endl;
	//std::cout << "Current velocity " << vectorToStr(this->GetVelocity()) << std::endl;
	//std::cout << "Current acceleration " << vectorToStr(this->GetAcceleration()) << std::endl;
	FireCollisionEnter(ColliderToAdd, ContactPoint);
}

void Collider::RemoveFromCollisionWith(Collider* ColliderToRemove)
{
	for (int i = 0; i < currentCollisions.size(); i++)
	{
		if (currentCollisions[i] == ColliderToRemove)
		{
			currentCollisions.erase(currentCollisions.begin() + i);
			//std::cout << "Collision exit between " << this->gameObject->Name << " and " << ColliderToRemove->gameObject->Name << std::endl;
			FireCollisionExit(ColliderToRemove);
			return;
		}
	}
}

bool Collider::AlreadyColliding(Collider* ColliderToCheck)
{
	for (int i = 0; i < currentCollisions.size(); i++)
	{
		if (currentCollisions[i] == ColliderToCheck)
		{
			return true;
		}
	}
	return false;
}



void Collider::CreateShape()
{
	shape = sf::ConvexShape(GetAllPoints().size());
	for (int i = 0; i < GetAllPoints().size(); i++)
	{
		//std::cout << "point " << i << " at :" << GetAllPoints()[i].x << " " << GetAllPoints()[i].y << "\n";
		shape.setPoint(i, GetAllPoints()[i]);
	}

	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(-2);
	shape.setFillColor(sf::Color::Transparent);

}

void Collider::Update(float deltaTime)
{
	if (Gravity)
	{
		AddForce(sf::Vector2f(0, gravityForce));
	}

	velocity = acceleration * deltaTime;

	acceleration *= frictionForce;

	if (std::abs(acceleration.x) < 0.1f && std::abs(acceleration.y) < 0.1f) {
		acceleration = sf::Vector2f(0.0f, 0.0f);
	}

	ColliderUpdate(deltaTime);
}

void Collider::AddForce(sf::Vector2f forceToAdd)
{
	acceleration += (forceToAdd*1.5f);
}

void Collider::SetVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;
}

void Collider::SetAcceleration(sf::Vector2f newAcceleration)
{
	acceleration = newAcceleration;
}

sf::Vector2f Collider::GetVelocity()
{
	return velocity;
}

sf::Vector2f Collider::GetAcceleration()
{
	return acceleration;
}

Event<Collider*, sf::Vector2f>* Collider::OnCollisionEnter()
{
	return &onCollisionEnter;
}

Event<Collider*>* Collider::OnCollisionExit()
{
	return &onCollisionExit;
}

void Collider::FireCollisionEnter(Collider* CollideWith, sf::Vector2f ContactPoint)
{
	//std::cout << "collision enter invoked ";
	onCollisionEnter.InvokeEvent(CollideWith, ContactPoint);
}

void Collider::FireCollisionExit(Collider* CollideWith)
{
	onCollisionExit.InvokeEvent(CollideWith);
}