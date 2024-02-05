#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GraphicDebugger.h"
#include "PhysicsEngine.h"
#include "ArrowComponent.h"
#include "VisualForceArrow.h"
#include "SceneManager.h"
#include "GameScene.h"


class LevelOneScene : public GameScene
{
public:
	LevelOneScene();
	void Update(float deltaTime) override;
private:
	void InitLevel() override;
	void SetupMapElements() override;
	void SetupElements() override;
};



