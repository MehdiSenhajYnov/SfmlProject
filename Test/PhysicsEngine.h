#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Scene.h"
#include <vector>
#include <future>
#include "BoxCollider.h"
#include "CircleCollider.h"
#include <memory>
#include "GraphicDebugger.h"
#include "MyMath.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	void Init(Scene* _scene, GraphicDebugger* _graphicDebugger);

	bool ObjectCanMoveBy(Collider* colliderToCheck, sf::Vector2f _moveBy);
	//bool IsColliderTouchingCollider(Collider* firstCollider, Collider* Collider);
	bool SomeObjecsAreColliding();
	std::shared_ptr<BoxCollider> CreateBoxCollider(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, sf::Vector2f _size);
	std::shared_ptr<CircleCollider> CreateCircleCollider(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, float radius, int accuracy);
	void DestroyCollider(Collider* _colliderToRemove);
	void EnterModifyMode();
	void ExitModifyMode();
	void SwitchModifyMode();

	void UpdatePhysics(float deltaTime);

private:
	Scene* scene;
	std::vector<std::shared_ptr<Collider>> AllColliders;
	sf::FloatRect TestRect;
	bool modifyMode;
	void changeModifyModeTo(bool newState);
	bool ShapeAreTouching(sf::Vector2f CenterShape1, sf::Vector2f OffsetShape1, std::vector<sf::Vector2f> Shape1AllPoints, sf::Vector2f CenterShape2, sf::Vector2f OffsetShape2, std::vector<sf::Vector2f> Shape2AllPoints);
	bool ShapeAreTouching(sf::Vector2f CenterShape1, sf::Vector2f OffsetShape1, std::vector<sf::Vector2f> Shape1AllPoints, sf::Vector2f CenterShape2, sf::Vector2f OffsetShape2, std::vector<sf::Vector2f> Shape2AllPoints, sf::Vector2f& OutCollisionPoint);
	bool TwoObjectAreColliding(Collider* c1, Collider* c2);
	bool point_in_polygon(sf::Vector2f point, std::vector<sf::Vector2f> polygon, sf::Vector2f offest);

	GraphicDebugger* graphicDebugger;
	bool MoveObject(Collider* _colliderToMove, sf::Vector2f _moveby);
};

