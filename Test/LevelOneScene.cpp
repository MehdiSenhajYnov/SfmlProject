#include "LevelOneScene.h"

LevelOneScene::LevelOneScene()
{
}


void LevelOneScene::Update(float deltaTime)
{
	mainCamera.Render();
	GameLoop(deltaTime);
}


//void LevelOneScene::GameLoop(float deltaTime)
//{
//	mainCameraObject->SetPosition(sf::Vector2(Player->GetPosition().x - window->getSize().x / 2, mainCameraObject->GetPosition().y));
//	CalUpdateOnAll(deltaTime);
//	physicsEngine.UpdatePhysics(deltaTime);
//}

void LevelOneScene::SetupMapElements()
{
	BackgroundObject = CreateBackground();
	
	auto [ground1, ground1Collider] = CreatePlatformeThree();
	ground1->SetPosition(150, 650);

	std::get<0>(CreatePlatformeThree())->SetPosition(2000, 250);

	std::get<0>(CreatePlatformeTwo())->SetPosition(3300, 400);

	std::get<0>(CreatePlatformeOne())->SetPosition(5000, 250);

	std::get<0>(CreatePlatformeOne())->SetPosition(6800, 800);
}

void LevelOneScene::SetupElements()
{
	tie(Player, playerCollider) = CreatePlayer();
	playerCollider->Gravity = true;

	tie(directionArrow, forceArrow) = CreateArrows(Player, playerCollider, arrowComponent, arrowVisual, 5);

	auto[targetObj, targetCollider] = CreateTarget();
	targetCollider->Gravity = false;
	targetObj->SetPosition(6900, 790);

}

