#include "GameManager.h"

GameManager::GameManager() :
window(sf::VideoMode(1700, 1000), "Simple 2D Game")
{
	iswindowFocus = true;
}

void GameManager::Run()
{
	SceneManager::OnSceneChanged.Subscribe(&GameManager::OnChangeSceneAsked, this);
	haveToChangeScene = false;
	OnChangeSceneAsked(SceneManager::SceneEnum::LevelOne);

	sf::Clock dtClock;
	float deltaTime;

	while (window.isOpen())
	{
		if (haveToChangeScene)
		{
			ChangeScene(newScene);
		}
		WindowsEvents();
		if (!iswindowFocus) continue;

		deltaTime = dtClock.restart().asSeconds();
		currentScene->Update(deltaTime);

	}
}

void GameManager::OnChangeSceneAsked(SceneManager::SceneEnum sceneToUse)
{
	newScene = sceneToUse;
	haveToChangeScene = true;
}

void GameManager::ChangeScene(SceneManager::SceneEnum sceneToUse)
{
	if (sceneToUse == SceneManager::SceneEnum::Menu)
	{
		currentScene = std::make_unique<MenuScene>();
	}
	else if (sceneToUse == SceneManager::SceneEnum::LevelOne)
	{
		currentScene = std::make_unique<LevelOneScene>();
	}

	currentScene->InitializeScene(&window);
	haveToChangeScene = false;

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