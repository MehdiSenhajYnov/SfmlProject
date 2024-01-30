#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Camera.h"

class GraphicDebugger
{
public:
	GraphicDebugger();
	void Init(Camera* _mainCamera, int numberOfPointMax);
	void AddPointToDebug(sf::Vector2f pointToDebugCordinate, sf::Color colorOfPoint);
	void ChangePositionOfPoint(int indexOfPoint, sf::Vector2f newposition);
	void Enable();
	void Disable();
	Camera* mainCamera;
private:
	std::vector<sf::CircleShape> toDebug;
	bool debuggerIsActive;
};

