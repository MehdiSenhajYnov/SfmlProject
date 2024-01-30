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

class GameManager
{
public:
	GameManager();
	void Run();
private:
	bool iswindowFocus;
	void WindowsEvents();
	Scene* currentScene;
	sf::RenderWindow window;
};

