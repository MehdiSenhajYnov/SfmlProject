#include "LevelThreeScene.h"

LevelThreeScene::LevelThreeScene()
{
}


void LevelThreeScene::Update(float deltaTime)
{
	mainCamera.Render();
	GameLoop(deltaTime);
}

void LevelThreeScene::InitLevel()
{
	currentLevel = 3;
}

void LevelThreeScene::SetupMapElements()
{
	BackgroundObject = CreateBackground();

	auto [ground1, ground1Collider] = CreatePlatformeThree();
	ground1->SetPosition(150, 650);

	std::get<0>(CreatePlatformeThree())->SetPosition(2000, 250);

	std::get<0>(CreatePlatformeTwo())->SetPosition(3300, 400);

	std::get<0>(CreatePlatformeOne())->SetPosition(5000, 250);

	std::get<0>(CreatePlatformeOne())->SetPosition(6800, 800);
}

void LevelThreeScene::SetupElements()
{
	tie(Player, playerCollider) = CreatePlayer();
	playerCollider->Gravity = true;

	tie(directionArrow, forceArrow) = CreateArrows(Player, playerCollider, arrowComponent, arrowVisual, 3);

	auto [targetObj, targetCollider] = CreateTarget();
	targetCollider->Gravity = false;
	targetObj->SetPosition(6900, 790);

}

