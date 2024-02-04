#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Button.h"
#include "SceneManager.h"


class MenuScene : public Scene
{
public:

	void GameLoop(float deltaTime);

private:
	std::shared_ptr<GameObject> mainCameraObject;
	Camera mainCamera;

	std::shared_ptr<GameObject> playButtonObj;
	std::shared_ptr<GameObject> exitButtonObj;

	Button playButtonComponent;
	Button exitButtonComponent;


	std::shared_ptr<GameObject> LoadingObj;
	Button loadingButtonComponent;



	void OnPlayButtonClicked();
	void OnExitButtonClicked();

	// Hérité via Scene
	void Update(float deltaTime) override;
	void InitializeScene(sf::RenderWindow* _window) override;
	void OnSceneChanged();

	void DestroyScene() override;
	void OnKeyDown(sf::Keyboard::Key pressedKey) override;
};

