#pragma once
#include "GameScene.h"
class LevelThreeScene : public GameScene
{
public:
	LevelThreeScene();
	void Update(float deltaTime) override;
private:
	void InitLevel() override;
	void SetupMapElements() override;
	void SetupElements() override;
};