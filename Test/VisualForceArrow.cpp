#include "VisualForceArrow.h"

void VisualForceArrow::Start()
{
}

void VisualForceArrow::Update(float deltaTime)
{
	gameObject->SetPosition(arrowComponent->GetAttachedObject()->GetPosition());
	gameObject->SetRotation(arrowComponent->GetAttachedObject()->GetRotation());

	gameObject->GetSprite()->setTextureRect(sf::IntRect(0, 648 - arrowComponent->GetCurrentForce(), 450, arrowComponent->GetCurrentForce()));

	float forceArrowWidth = gameObject->GetSprite()->getTexture()->getSize().x;
	float forceArrowHeight = arrowComponent->GetCurrentForce();

	sf::Vector2f forceOrigin(forceArrowWidth / 2, forceArrowHeight);
	gameObject->GetSprite()->setOrigin(forceOrigin);
}

void VisualForceArrow::InitComponent(std::shared_ptr<GameObject> _gameObject, ArrowComponent* _arrowComponent)
{
	LoadComponentBase(_gameObject);
	arrowComponent = _arrowComponent;
}
