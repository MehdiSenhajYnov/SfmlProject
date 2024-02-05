#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "GameObject.h"
#include "Scene.h"
#include "Camera.h"
#include "GravitySystem.h"
#include "BoxCollider.h"
#include "PhysicsEngine.h"
#include "GraphicDebugger.h"
#include "MyMath.h"
#include "GameScene.h"
#include "LevelOneScene.h"
#include "LevelTwoScene.h"
#include "MenuScene.h"
#include "SceneManager.h"

class GameManager
{
public:
	GameManager();
	void Run();
	void OnChangeSceneAsked(SceneManager::SceneEnum sceneToUse);
	void ChangeScene(SceneManager::SceneEnum sceneToUse);
private:
	SceneManager::SceneEnum newScene;
	bool haveToChangeScene;
	bool iswindowFocus;
	void WindowsEvents();

	std::shared_ptr<Scene> currentScene;
	sf::RenderWindow window;
};

