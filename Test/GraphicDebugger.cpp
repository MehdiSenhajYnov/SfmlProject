#include "GraphicDebugger.h"

GraphicDebugger::GraphicDebugger()
{
}



void GraphicDebugger::Init(Camera* _mainCamera)
{
	mainCamera = _mainCamera;
}

void GraphicDebugger::AddPointToDebug(std::string pointName, sf::Vector2f pointToDebugCordinate, sf::Color colorOfPoint)
{
	toDebug[pointName] = sf::CircleShape(10);
	toDebug[pointName].setFillColor(colorOfPoint);
	toDebug[pointName].setPosition(pointToDebugCordinate.x - 10, pointToDebugCordinate.y - 10);
	if (debuggerIsActive)
	{
		mainCamera->AddToPermanentDrawablesObjects(&toDebug[pointName], nullptr);
	}

}

void GraphicDebugger::ChangePositionOfPoint(std::string pointName, sf::Vector2f newposition)
{
	toDebug[pointName].setPosition(newposition.x - 10, newposition.y - 10);
}

void GraphicDebugger::Enable()
{
	if (!debuggerIsActive)
	{
		debuggerIsActive = true;

		for (auto& [pointName, pointShape] : toDebug)
		{
			mainCamera->AddToPermanentDrawablesObjects(&toDebug[pointName],nullptr);
		}
	}
}

void GraphicDebugger::Disable()
{
	if (debuggerIsActive)
	{
		debuggerIsActive = false;
		for (auto& [pointName, pointShape] : toDebug)
		{
			mainCamera->RemoveFromPermanentDrawablesObjects(&toDebug[pointName]);
		}
	}
}




