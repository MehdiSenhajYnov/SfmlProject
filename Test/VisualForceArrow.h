#pragma once
#include "Component.h"
#include "ArrowComponent.h"
class VisualForceArrow : public Component
{
public:
	// Hérité via Component
	void Start() override;
	void Update(float deltaTime) override;
	void InitComponent(std::shared_ptr<GameObject> _gameObject, ArrowComponent* _arrowComponent);
private:
	ArrowComponent* arrowComponent;
};

