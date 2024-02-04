#pragma once
#include "Component.h"
Component::Component()
{
}

Component::~Component()
{
}

void Component::LoadComponentBase(std::shared_ptr<GameObject> _gameObject)
{
	gameObject = _gameObject;
}

std::shared_ptr<GameObject> Component::GetAttachedObject()
{
	return gameObject;
}