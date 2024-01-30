#include "GraphicDebugger.h"

GraphicDebugger::GraphicDebugger()
{
}



void GraphicDebugger::Init(Camera* _mainCamera, int numberOfPointMax)
{
	mainCamera = _mainCamera;
	toDebug.reserve(numberOfPointMax);
}

void GraphicDebugger::AddPointToDebug(sf::Vector2f pointToDebugCordinate, sf::Color colorOfPoint)
{
	int newElementIndex = toDebug.size();
	toDebug.push_back(sf::CircleShape(10));
	toDebug[newElementIndex].setFillColor(colorOfPoint);
	toDebug[newElementIndex].setPosition(pointToDebugCordinate.x - 10, pointToDebugCordinate.y - 10);
	if (debuggerIsActive)
	{
		mainCamera->AddToPermanentDrawablesObjects(&toDebug[newElementIndex], nullptr);
	}

}

void GraphicDebugger::ChangePositionOfPoint(int indexOfPoint, sf::Vector2f newposition)
{
	toDebug[indexOfPoint].setPosition(newposition.x - 10, newposition.y - 10);
}

void GraphicDebugger::Enable()
{
	if (!debuggerIsActive)
	{
		debuggerIsActive = true;
		for (int i = 0; i < toDebug.size(); i++)
		{
			mainCamera->AddToPermanentDrawablesObjects(&toDebug[i], nullptr);
		}
	}
}

void GraphicDebugger::Disable()
{
	if (debuggerIsActive)
	{
		debuggerIsActive = false;
		for (int i = 0; i < toDebug.size(); i++)
		{
			mainCamera->RemoveFromPermanentDrawablesObjects(&toDebug[i]);
		}
	}
}




