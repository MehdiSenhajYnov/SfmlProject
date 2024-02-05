#include "Collider.h"

Collider::Collider(){}



void Collider::InitializeCollider(std::shared_ptr<GameObject> _gameObject, std::vector<sf::Vector2f>  _allPoints)
{
	LoadComponentBase(_gameObject);
	IsStatic = false;

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



void Collider::SetVisible(bool _visibleState, Camera* cameraToUse)
{
	Visible = _visibleState;

	if (Visible)
	{
		CreateShape();
		shape_ptr = &shape;
		cameraToUse->AddToPermanentDrawablesObjects(shape_ptr, gameObject);

	}
	else
	{
		cameraToUse->RemoveFromPermanentDrawablesObjects(shape_ptr);
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

std::map<Collider*, sf::Vector2f> Collider::GetCurrentCollisions()
{
	return currentCollisions;
}

void Collider::AddInCollisionWith(Collider* ColliderToAdd, sf::Vector2f ContactPoint)
{
	auto vectorToStr = [](sf::Vector2f toconvert) { return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); };

	currentCollisions[ColliderToAdd] = ContactPoint;
	//std::cout << "Collision enter between " << this->gameObject->Name << " and " << ColliderToAdd->gameObject->Name << std::endl;
	//std::cout << "Current velocity " << vectorToStr(this->GetVelocity()) << std::endl;
	//std::cout << "Current acceleration " << vectorToStr(this->GetAcceleration()) << std::endl;
	FireCollisionEnter(ColliderToAdd, ContactPoint);
}

void Collider::RemoveFromCollisionWith(Collider* ColliderToRemove)
{
	if (currentCollisions.contains(ColliderToRemove))
	{
		currentCollisions.erase(ColliderToRemove);
		FireCollisionExit(ColliderToRemove);
	}
}

bool Collider::AlreadyColliding(Collider* ColliderToCheck)
{
	return currentCollisions.contains(ColliderToCheck);
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
		AddForce(sf::Vector2f(0, gravityForce * 0.0025));
	}

	//velocity = acceleration * deltaTime;

	velocity *= frictionForce;

	if (std::abs(velocity.x) < 0.00001f && std::abs(velocity.y) < 0.00001f) {
		velocity = sf::Vector2f(0.0f, 0.0f);
	}

	ColliderUpdate(deltaTime);
}

void Collider::AddForce(sf::Vector2f forceToAdd)
{
	// testing
	//forceToAdd.x = forceToAdd.x / 100;
	//forceToAdd.y = forceToAdd.y / 100;
	if (IsStatic) return;

	auto vectorToStr = [](sf::Vector2f toconvert) { return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); };
	if (std::isnan(forceToAdd.x) || std::isnan(forceToAdd.y))
	{
		std::cout << "adding NAN force" << std::endl;
		return;
	}
	if ((velocity + forceToAdd).x <= -std::numeric_limits<float>::max() || (velocity + forceToAdd).y <= -std::numeric_limits<float>::max())
	{
		std::cout << "out of limit. MIN Force = " << std::numeric_limits<float>::min() <<" acceleration = " << vectorToStr(velocity)  << " force to add : " << vectorToStr(forceToAdd) <<std::endl;
		return;
	}

	if ((velocity + forceToAdd).x >= std::numeric_limits<float>::max() || (velocity + forceToAdd).y >= std::numeric_limits<float>::max())
	{
		std::cout << "out of limit MAX Force" << std::endl;
		return;
	}
	
	velocity += (forceToAdd);
	//std::cout << "Add force : " << vectorToStr(forceToAdd) << " Current velocity : " << vectorToStr(velocity) << std::endl;
}

void Collider::SetVelocity(sf::Vector2f newVelocity)
{
	velocity = newVelocity;
}

sf::Vector2f Collider::GetVelocity()
{
	return velocity;
}


Event<Collider*, sf::Vector2f>* Collider::OnCollisionEnter()
{
	return &onCollisionEnter;
}

Event<Collider*>* Collider::OnCollisionExit()
{
	return &onCollisionExit;
}

bool Collider::GetIsStatic()
{
	return IsStatic;
}

void Collider::SetIsStatic(bool _isStatic)
{
	IsStatic = _isStatic;
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