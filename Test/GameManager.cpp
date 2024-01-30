#include "GameManager.h"

GameManager::GameManager() :
window(sf::VideoMode(1024, 800), "Simple 2D Game")
{
	iswindowFocus = true;
}

void GameManager::Run()
{
	auto gamescene = GameScene();
	currentScene = &gamescene;
	currentScene->InitializeScene(&window);

	sf::Clock dtClock;
	float deltaTime;
	while (window.isOpen())
	{
		WindowsEvents();

		if (!iswindowFocus) continue;
		deltaTime = dtClock.restart().asSeconds();

		currentScene->Update(deltaTime);
	}
}

void GameManager::WindowsEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::GainedFocus)
		{
			iswindowFocus = true;
			std::cout << "window gained focus : " << std::endl;
		}

		if (event.type == sf::Event::LostFocus)
		{
			iswindowFocus = false;
			std::cout << "window lost focus : " << std::endl;
		}


		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}

			if (currentScene != nullptr && iswindowFocus)
			{
				currentScene->OnKeyDown(event.key.code);
			}

			//if (event.key.code == sf::Keyboard::C)
			//{
			//	physicsEngine.SwitchModifyMode();
			//}

		}
	}
}