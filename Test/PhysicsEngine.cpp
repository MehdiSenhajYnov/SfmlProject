#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
	
}


void PhysicsEngine::Init(Scene* _scene, GraphicDebugger* _graphicDebugger)
{
	scene = _scene; 
	modifyMode = false; 
	graphicDebugger = _graphicDebugger;

	graphicDebugger->AddPointToDebug("contactPoint", sf::Vector2f(0, 0), sf::Color::Cyan);
}


bool PhysicsEngine::SomeObjecsAreColliding()
{
	for (int i = 0; i < AllColliders.size(); i++)
	{

		for (int j = i+1; j < AllColliders.size(); j++)
		{
			if (TwoObjectAreColliding(AllColliders[i].get(), AllColliders[j].get()))
			{
				return true;
			}
		}
	}
	return false;

}


std::shared_ptr<BoxCollider> PhysicsEngine::CreateBoxCollider(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, sf::Vector2f _size)
{
	std::shared_ptr<BoxCollider> newCollider = std::make_shared<BoxCollider>();
	newCollider->Init(_gameObject, _topLeftPoint, _size);

	AllColliders.push_back(newCollider);
	scene->AddComponent(_gameObject, newCollider.get());
	return newCollider;
}

std::shared_ptr<CircleCollider> PhysicsEngine::CreateCircleCollider(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, float radius, int accuracy)
{
	std::shared_ptr<CircleCollider> newCollider = std::make_shared<CircleCollider>();
	newCollider->Init(_gameObject, _topLeftPoint, radius, accuracy);

	AllColliders.push_back(newCollider);
	scene->AddComponent(_gameObject, newCollider.get());
	return newCollider;
}


std::shared_ptr<CustomCollider> PhysicsEngine::CreateCustomCollider(std::shared_ptr<GameObject> _gameObject, std::vector<sf::Vector2f> allPoints)
{
	std::shared_ptr<CustomCollider> newCollider = std::make_shared<CustomCollider>();
	newCollider->Init(_gameObject, allPoints);

	AllColliders.push_back(newCollider);
	scene->AddComponent(_gameObject, newCollider.get());
	return newCollider;
}


void PhysicsEngine::DestroyCollider(Collider* _colliderToRemove)
{
	int index = -1;
	for (int i = 0; i < AllColliders.size(); i++)
	{
		if (AllColliders[i].get() == _colliderToRemove)
		{
			index = i;
			break;
		}
	}
	scene->RemoveComponent(_colliderToRemove->GetAttachedObject(), _colliderToRemove);
	if (index != -1)
	{
		AllColliders.erase(AllColliders.begin() + index);
	}

}

void PhysicsEngine::EnterModifyMode()
{
	SetModifyMode(true);
}

void PhysicsEngine::ExitModifyMode()
{
	SetModifyMode(false);
}

void PhysicsEngine::SwitchModifyMode()
{
	SetModifyMode(!modifyMode);
}

void PhysicsEngine::UpdatePhysics(float deltaTime)
{
	bool movementResult;
	for (int i = 0; i < AllColliders.size(); i++)
	{
		if (AllColliders[i] != nullptr && AllColliders[i]->GetVelocity() != sf::Vector2f(0, 0))
		{
			bool isStatic = AllColliders[i]->GetIsStatic();
			if (isStatic) continue;
			//std::cout << "velocity moving" << std::endl;
			movementResult = MoveObject(AllColliders[i].get(), AllColliders[i]->GetVelocity());
			//if (!movementResult)
			//{
			//	AllColliders[i]->SetVelocity(sf::Vector2f(0, 0));
			//	AllColliders[i]->SetAcceleration(sf::Vector2f(0, 0));
			//}
		}
	}

	//Test
	SomeObjecsAreColliding();
}

bool PhysicsEngine::MoveObject(Collider* _colliderToMove, sf::Vector2f _moveby)
{
	if (ObjectCanMoveBy(_colliderToMove, _moveby))
	{
		auto vectorToStr = [](sf::Vector2f toconvert) { return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); };
		//std::cout << "moving by : " << vectorToStr(_moveby) << " from : " << vectorToStr(_colliderToMove->GetAttachedObject()->GetPosition()) << std::endl;
		_colliderToMove->GetAttachedObject()->Move(_moveby);
		return true;
	}
	return false;

}

bool PhysicsEngine::ObjectCanMoveBy(Collider* colliderToCheck, sf::Vector2f _moveBy)
{
	//return true;
	if (colliderToCheck->GetCurrentCollisions().size() <= 0)
	{
		return true;
	}
	bool col1isTouchincol2;
	sf::Vector2f centerPositionCol1 = colliderToCheck->GetCenter() + colliderToCheck->GetAttachedObject()->GetPosition();

	sf::Vector2f centerPositionCol2;
	for (auto& [colliderInCollision, ContactPoint] : colliderToCheck->GetCurrentCollisions())
	{
		if (colliderInCollision == colliderToCheck) continue;
		col1isTouchincol2 = ShapeAreTouching(
			colliderToCheck->GetCenter(), colliderToCheck->GetAttachedObject()->GetPosition() + _moveBy, colliderToCheck->GetAllPoints(),
			colliderInCollision->GetCenter(), colliderInCollision->GetAttachedObject()->GetPosition(), colliderInCollision->GetAllPoints());


		//centerPositionCol2 = colliderInCollision->GetCenter() + colliderInCollision->GetAttachedObject()->GetPosition();

		//float distance = std::abs(MyMath::VectorLength(centerPositionCol1 - centerPositionCol2));
		//float distance2 = std::abs(MyMath::VectorLength(centerPositionCol1 + _moveBy - centerPositionCol2));

		//if (distance2 < distance)
		//{
		//	return false;
		//}

		if (col1isTouchincol2)
		{
			return false;
		}

	}


	return true;
}

void PhysicsEngine::SetModifyMode(bool newState)
{
	modifyMode = newState;
	for (int i = 0; i < AllColliders.size(); i++)
	{
		AllColliders[i]->SetVisible(newState, graphicDebugger->mainCamera);
	}
}

bool PhysicsEngine::TwoObjectAreColliding(Collider* c1, Collider* c2)
{
	// ca marche que avec les polygone convexe (sans angle interieure > 180 degrée)

	Collider* colliderOne = c1;
	Collider* colliderTwo = c2;

	bool colOneAlreadyContainsColTwo = colliderOne->AlreadyColliding(colliderTwo);
	bool colTwoAlreadyContainsColOne = colliderTwo->AlreadyColliding(colliderOne);

	sf::Vector2f ContactPoint(0, 0);

	sf::Vector2f OutComplementaryAxePoint1;
	sf::Vector2f OutComplementaryAxePoint2;

	bool isTouching = ShapeAreTouching(c1->GetCenter(), c1->GetAttachedObject()->GetPosition(), c1->GetAllPoints(),
		c2->GetCenter(), c2->GetAttachedObject()->GetPosition(), c2->GetAllPoints(), ContactPoint, OutComplementaryAxePoint1, OutComplementaryAxePoint2);

	if (isTouching)
	{
		sf::Vector2f normalForceVector = CalculateNormalForceVector(c1,c2,ContactPoint,OutComplementaryAxePoint1, OutComplementaryAxePoint2);

		sf::Vector2f normalizedNormalVector = MyMath::GetNormalizedVector(normalForceVector);
		sf::Vector2f normalizedForce = MyMath::GetNormalizedVector(c1->GetVelocity());
		float multiplier = c1->GetVelocity().x / normalizedForce.x;
		normalizedNormalVector *= multiplier;


		c1->SetVelocity(normalForceVector);

		if (!colOneAlreadyContainsColTwo)
		{
			colliderOne->AddInCollisionWith(colliderTwo, ContactPoint);


		}
		if (!colTwoAlreadyContainsColOne)
		{
			colliderTwo->AddInCollisionWith(colliderOne, ContactPoint);
		}


		return true;
	}

	if (colOneAlreadyContainsColTwo)
	{
		colliderOne->RemoveFromCollisionWith(colliderTwo);
	}

	if (colTwoAlreadyContainsColOne)
	{
		colliderTwo->RemoveFromCollisionWith(colliderOne);
	}

	return false;
}

sf::Vector2f PhysicsEngine::CalculateNormalForceVector(Collider* c1, Collider* c2, sf::Vector2f ContactPoint, sf::Vector2f ComplementaryAxePoint1, sf::Vector2f ComplementaryAxePoint2)
{
	auto vectorToStr = [](sf::Vector2f toconvert) { return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); };

	sf::Vector2f c1Center = c1->GetCenter() + c1->GetAttachedObject()->GetPosition();
	sf::Vector2f c2Center = c2->GetCenter() + c2->GetAttachedObject()->GetPosition();
	sf::Vector2f currentForce = c1->GetVelocity();
	sf::Vector2f PointA(ContactPoint - currentForce);
	float longueurForce = MyMath::VectorLength(currentForce);
	float angleVector = MyMath::CalculerAngle(ContactPoint, PointA, ComplementaryAxePoint1);

	sf::Vector2f normalPoint;
	sf::Vector2f alternatifNormalPoint;
	
	if (angleVector <= 90)
	{
		normalPoint = MyMath::TrouverPointA(ComplementaryAxePoint1, ContactPoint, angleVector, longueurForce, alternatifNormalPoint);
	}
	else
	{
		angleVector = MyMath::CalculerAngle(ContactPoint, PointA, ComplementaryAxePoint2);
		normalPoint = MyMath::TrouverPointA(ComplementaryAxePoint2, ContactPoint, angleVector, longueurForce, alternatifNormalPoint);
	}

	if (MyMath::CalculerAngle(ContactPoint, PointA, normalPoint) > 180)
	{
		normalPoint = alternatifNormalPoint;
	}

	sf::Vector2f normalForceVector = normalPoint - ContactPoint;

	if (std::abs(normalForceVector.x) < 0.1f && std::abs(normalForceVector.y) < 0.1f)
	{
		normalForceVector = sf::Vector2f(0.0f, 0.0f);
	}
	else
	{
		// log
		//std::cout << "currentForce = " << vectorToStr(currentForce) << std::endl;
		//std::cout << "ContactPoint = " << vectorToStr(ContactPoint) << std::endl;
		//std::cout << "c1Center = " << vectorToStr(c1Center) << std::endl;
		//std::cout << "c2Center = " << vectorToStr(c2Center) << std::endl;
		//std::cout << "PointA = " << vectorToStr(PointA) << std::endl;
		std::cout << "currentForce = " << vectorToStr(currentForce) << std::endl;
		std::cout << "normal point = " << vectorToStr(normalPoint) << std::endl;
		std::cout << "normal force = " << vectorToStr(normalForceVector) << std::endl << std::endl << std::endl;
	}



	return normalForceVector;
}

bool PhysicsEngine::ShapeAreTouching
(sf::Vector2f CenterShape1, sf::Vector2f OffsetShape1, std::vector<sf::Vector2f> Shape1AllPoints,
	sf::Vector2f CenterShape2, sf::Vector2f OffsetShape2, std::vector<sf::Vector2f> Shape2AllPoints)
{
	sf::Vector2f temp(0, 0);
	return ShapeAreTouching(CenterShape1, OffsetShape1, Shape1AllPoints,
		CenterShape2, OffsetShape2, Shape2AllPoints, temp, temp, temp);
}


bool PhysicsEngine::ShapeAreTouching
(sf::Vector2f CenterShape1, sf::Vector2f OffsetShape1, std::vector<sf::Vector2f> Shape1AllPoints, 
 sf::Vector2f CenterShape2, sf::Vector2f OffsetShape2, std::vector<sf::Vector2f> Shape2AllPoints,
 sf::Vector2f& OutContactPoint, sf::Vector2f& OutComplementaryAxePoint1, sf::Vector2f& OutComplementaryAxePoint2)
{
	// check des diagonales
	for (int p = 0; p < Shape1AllPoints.size(); p++)
	{
		//std::cout << " checking Line " << i <<" Point x : " << colliderOne->GetAllPoints()[p].x << " y : " << colliderOne->GetAllPoints()[p].y << "\n";
		sf::Vector2f col1PointA = Shape1AllPoints[p] + OffsetShape1;
		sf::Vector2f col1PointB = Shape1AllPoints[(p + 1) % Shape1AllPoints.size()] + OffsetShape1;
		
		// check des coté
		for (int q = 0; q < Shape2AllPoints.size(); q++)
		{
			sf::Vector2f col2PointA = Shape2AllPoints[q] + OffsetShape2;
			// point a coté
			sf::Vector2f col2PointB = Shape2AllPoints[(q + 1) % Shape2AllPoints.size()] + OffsetShape2;

			bool segmentIntersects = false;
			OutContactPoint = MyMath::IntersectionPoint(col1PointA, col1PointB, col2PointA, col2PointB, segmentIntersects);

			if (segmentIntersects)
			{
				if (point_in_polygon(col2PointA, Shape1AllPoints, OffsetShape1))
				{
					OutComplementaryAxePoint1 = col1PointA;
					OutComplementaryAxePoint2 = col1PointB;
				}
				else if (point_in_polygon(col2PointB, Shape1AllPoints, OffsetShape1))
				{
					OutComplementaryAxePoint1 = col1PointA;
					OutComplementaryAxePoint2 = col1PointB;
				}
				else if (point_in_polygon(col1PointA, Shape2AllPoints, OffsetShape2))
				{
					OutComplementaryAxePoint1 = col2PointA;
					OutComplementaryAxePoint2 = col2PointB;
				}
				else if (point_in_polygon(col1PointB, Shape2AllPoints, OffsetShape2))
				{
					OutComplementaryAxePoint1 = col2PointA;
					OutComplementaryAxePoint2 = col2PointB;
				}
				graphicDebugger->ChangePositionOfPoint("contactPoint", OutContactPoint);
				return true;
			}
		}
	}
	return false;
}

// Checking if a point is inside a polygon
bool PhysicsEngine::point_in_polygon(sf::Vector2f point, std::vector<sf::Vector2f> polygon, sf::Vector2f offest)
{
	int num_vertices = polygon.size();
	double x = point.x, y = point.y;
	bool inside = false;
	// Store the first point in the polygon and initialize
	// the second point
	sf::Vector2f p1 = polygon[0] + offest;
	sf::Vector2f p2;

	// Loop through each edge in the polygon
	for (int i = 1; i <= num_vertices; i++) {
		// Get the next point in the polygon
		p2 = polygon[i % num_vertices] + offest;

		// Check if the point is above the minimum y
		// coordinate of the edge
		if (y > std::min(p1.y, p2.y)) {
			// Check if the point is below the maximum y
			// coordinate of the edge
			if (y <= std::max(p1.y, p2.y)) {
				// Check if the point is to the left of the
				// maximum x coordinate of the edge
				if (x <= std::max(p1.x, p2.x)) {
					// Calculate the x-intersection of the
					// line connecting the point to the edge
					double x_intersection
						= (y - p1.y) * (p2.x - p1.x)
						/ (p2.y - p1.y)
						+ p1.x;

					// Check if the point is on the same
					// line as the edge or to the left of
					// the x-intersection
					if (p1.x == p2.x
						|| x <= x_intersection) {
						// Flip the inside flag
						inside = !inside;
					}
				}
			}
		}

		// Store the current point as the first point for
		// the next iteration
		p1 = p2;
	}

	// Return the value of the inside flag
	return inside;
}


