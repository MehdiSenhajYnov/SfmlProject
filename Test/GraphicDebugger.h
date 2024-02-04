#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Camera.h"

class GraphicDebugger
{
public:
	GraphicDebugger();
	void Init(Camera* _mainCamera);
	void AddPointToDebug(std::string pointName, sf::Vector2f pointToDebugCordinate, sf::Color colorOfPoint);
	void ChangePositionOfPoint(std::string pointName, sf::Vector2f newposition);
	void Enable();
	void Disable();
	Camera* mainCamera;
private:
	std::map<std::string, sf::CircleShape> toDebug;
	bool debuggerIsActive;
};

