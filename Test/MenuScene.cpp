#include "MenuScene.h"

void MenuScene::GameLoop(float deltaTime)
{
	CalUpdateOnAll(deltaTime);
}

void MenuScene::OnPlayButtonClicked()
{
	std::cout << "PLAY clicked !" << std::endl;
	loadingButtonComponent.SetString("Loading ...");
	mainCamera.Render();
	SceneManager::ChangeScene(SceneManager::SceneEnum::LevelOne);

	OnSceneChanged();

}

void MenuScene::OnExitButtonClicked()
{
	std::cout << "EXIT clicked !" << std::endl;

	window->close();
}

void MenuScene::Update(float deltaTime)
{
	mainCamera.Render();
	GameLoop(deltaTime);

	//std::cout << "drawing" << std::endl;
}




void MenuScene::InitializeScene(sf::RenderWindow* _window)
{
	window = _window;

	mainCameraObject = CreateGameObject("mainCameraObject", 0);
	mainCamera = Camera();
	mainCamera.Initialize(mainCameraObject, sf::Vector2f(10000, 10000), window, this);


	playButtonObj = CreateGameObject("playButton", 10);
	exitButtonObj = CreateGameObject("exitButton", 10);

	playButtonObj->SetSprite("assets/RoundedRectangle.png");

	playButtonObj->SetPosition(window->getSize().x / 2, window->getSize().y / 2 - 50);

	playButtonComponent.Init(playButtonObj, "PLAY", &mainCamera);
	playButtonComponent.OnButtonClicked.Subscribe(&MenuScene::OnPlayButtonClicked, this);

	AddComponent(playButtonObj, &playButtonComponent);


	exitButtonObj->SetPosition(window->getSize().x / 2, window->getSize().y / 2 + 50);
	exitButtonObj->SetSprite("assets/RoundedRectangle.png");

	exitButtonComponent.Init(exitButtonObj, "EXIT", &mainCamera);
	exitButtonComponent.OnButtonClicked.Subscribe(&MenuScene::OnExitButtonClicked, this);

	AddComponent(exitButtonObj, &exitButtonComponent);


	LoadingObj = CreateGameObject("Loading", 10);
	LoadingObj->SetPosition(playButtonObj->GetPosition().x + 105, playButtonObj->GetPosition().y - 40);

	loadingButtonComponent.Init(LoadingObj, "", &mainCamera);
	AddComponent(LoadingObj, &loadingButtonComponent);
	//OnPlayButtonClicked();
}

void MenuScene::OnSceneChanged()
{
	sceneChanged = true;
}



void MenuScene::DestroyScene()
{

}

void MenuScene::OnKeyDown(sf::Keyboard::Key pressedKey)
{

}
