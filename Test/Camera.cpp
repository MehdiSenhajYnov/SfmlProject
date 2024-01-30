#pragma once
#include "Camera.h"

std::map <sf::Shape*, std::shared_ptr<GameObject>> Camera::PermanentDrawablesObjects;
Camera::Camera()
{
}

void Camera::StartRenderingThread()
{
	window->setActive(false);
	sf::Thread thread(&Camera::RenderingThread, this);
	thread.launch();
}

void Camera::RenderingThread()
{
	window->setActive(true);
	while (window->isOpen())
	{
		Render();
	}
}

void Camera::Render()
{
	window->clear(sf::Color::White);
	if (gameObject == nullptr)
	{
		std::cout << "CAMERA NOT INITIALIZED" << std::endl;
		return;
	}

	for (auto& [_gObject, components] : scene->GetAllGamesObjectsComponents())
	{
		if (_gObject.get() == nullptr) continue;
		if (_gObject->GetSprite() == nullptr) continue;

		// Le sprite de l'objet n'a pas de texture, pas besoin de le draw
		if (_gObject->GetSprite()->getTexture() == nullptr) continue;

		if (_gObject->GetPosition().x < gameObject->GetPosition().x - CameraView.x ||
			_gObject->GetPosition().x > gameObject->GetPosition().x + CameraView.x)
		{
			continue;
		}

		if (_gObject->GetPosition().y < gameObject->GetPosition().y - CameraView.y ||
			_gObject->GetPosition().y > gameObject->GetPosition().y + CameraView.y)
		{
			continue;
		}

		_gObject->GetSprite()->setPosition(_gObject->GetPosition() - gameObject->GetPosition());
		//std::cout << "drawing " << _gameObject->Name << std::endl;
		window->draw(*_gObject->GetSprite());

	}

	for (auto& [toDraw, attachedObj] : PermanentDrawablesObjects)
	{
		if (attachedObj != nullptr)
		{
			if (attachedObj->GetPosition().x < gameObject->GetPosition().x - CameraView.x ||
				attachedObj->GetPosition().x > gameObject->GetPosition().x + CameraView.x)
			{
				continue;
			}

			if (attachedObj->GetPosition().y < gameObject->GetPosition().y - CameraView.y ||
				attachedObj->GetPosition().y > gameObject->GetPosition().y + CameraView.y)
			{
				continue;
			}

			toDraw->setPosition(attachedObj->GetPosition() - gameObject->GetPosition());
		}
		if (toDraw == nullptr) continue;
		window->draw(*toDraw);
	}

	window->display();
}



void Camera::AddToPermanentDrawablesObjects(sf::Shape* drawableToAdd, std::shared_ptr<GameObject> attachedObject)
{
	PermanentDrawablesObjects[drawableToAdd] = attachedObject;
}

void Camera::RemoveFromPermanentDrawablesObjects(sf::Shape* drawableToRemove)
{
	if (PermanentDrawablesObjects.contains(drawableToRemove))
	{
		PermanentDrawablesObjects.erase(drawableToRemove);
	}
}

void Camera::Start()
{
}

void Camera::Update(float deltaTime)
{
}

void Camera::Initialize(std::shared_ptr<GameObject> _gameObject, sf::Vector2<float> _cameraView, sf::RenderWindow* _window, Scene* _scene)
{
	LoadComponentBase(_gameObject);
	CameraView = _cameraView;
	window = _window; 
	scene = _scene;
}


