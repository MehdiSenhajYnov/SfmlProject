#pragma once
#include "Camera.h"

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
	for (auto& [zIndex, _gObjectList] : scene->GetAllGamesObjectsByZIndex())
	{
		for (int i = 0; i < _gObjectList.size(); i++)
		{
			if (_gObjectList[i].get() == nullptr) continue;
			if (_gObjectList[i]->GetSprite() == nullptr) continue;

			// Le sprite de l'objet n'a pas de texture, pas besoin de le draw
			if (_gObjectList[i]->GetSprite()->getTexture() == nullptr) continue;

			if (!IsOnDisplay(_gObjectList[i].get()))
			{
				continue;
			}

			_gObjectList[i]->GetSprite()->setPosition(_gObjectList[i]->GetPosition() - gameObject->GetPosition());
			//std::cout << "drawing " << _gameObject->Name << std::endl;
			window->draw(*_gObjectList[i]->GetSprite());
		}
	}

	for (auto& [toDraw, attachedObj] : PermanentDrawablesObjects)
	{
		if (attachedObj != nullptr)
		{
			if (!IsOnDisplay(attachedObj.get()))
			{
				continue;
			}

			toDraw->setPosition(attachedObj->GetPosition() - gameObject->GetPosition());
		}
		if (toDraw == nullptr) continue;
		window->draw(*toDraw);
	}

	for (int i = 0; i < Texts.size(); i++)
	{
		if (Texts[i] == nullptr) continue;
		window->draw(*Texts[i]);

	}

	window->display();
}

bool Camera::IsOnDisplay(GameObject* toCheck)
{

	// TODO: add object scale and texture size
	if (toCheck->GetPosition().x < gameObject->GetPosition().x - CameraView.x ||
		toCheck->GetPosition().x > gameObject->GetPosition().x + CameraView.x)
	{
		return false;
	}

	if (toCheck->GetPosition().y < gameObject->GetPosition().y - CameraView.y ||
		toCheck->GetPosition().y > gameObject->GetPosition().y + CameraView.y)
	{
		return false;
	}

	return true;
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

void Camera::AddToTexts(sf::Text* textToAdd)
{
	Texts.push_back(textToAdd);
}

void Camera::RemoveFromTexts(sf::Text* textToRemove)
{
	for (int i = 0; i < Texts.size(); i++)
	{
		if (Texts[i] == textToRemove)
		{
			Texts.erase(Texts.begin() + i);
			return;
		}
	}
}

sf::RenderWindow* Camera::GetCurrentWindow()
{
	return window;
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


