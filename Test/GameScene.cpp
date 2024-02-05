#include "GameScene.h"

GameScene::GameScene()
{
}

void GameScene::InitializeScene(sf::RenderWindow* _window)
{


	if (!font.loadFromFile("fonts/Arial.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	ThrowsText.setFont(font);


	ThrowsText.setCharacterSize(48);
	ThrowsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	ThrowsText.setFillColor(sf::Color::Black);

	LevelText.setFont(font);
	LevelText.setCharacterSize(48);
	LevelText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	LevelText.setFillColor(sf::Color::Black);


	std::cout << "Game Scene initialize begin" << std::endl;
	window = _window;

	mainCameraObject = CreateGameObject("mainCameraObject",0);
	mainCamera = Camera();
	mainCamera.Initialize(mainCameraObject, sf::Vector2f(10000, 10000), window, this);

	AddComponent(mainCameraObject, &mainCamera);
	graphicDebugger = GraphicDebugger();
	graphicDebugger.Init(&mainCamera);
	
	physicsEngine = PhysicsEngine();
	physicsEngine.Init(this, &graphicDebugger);

	SetupMapElements();
	SetupElements();

	graphicDebugger.Disable();
	//physicsEngine.SwitchModifyMode();
	physicsEngine.SetModifyMode(false);
	std::cout << "Game Scene initialize end" << std::endl;

	ThrowsText.setString(std::to_string(arrowComponent.GetCurrentThrows()) + " / " + std::to_string(arrowComponent.GetMaxThrows()));
	ThrowsText.setPosition(sf::Vector2f(window->getSize().x - 150, 20));

	InitLevel();

	LevelText.setString("Level" + std::to_string(currentLevel));
	LevelText.setPosition(sf::Vector2f(window->getSize().x / 2, 20));

	mainCamera.AddToTexts(&ThrowsText);
	mainCamera.AddToTexts(&LevelText);

}

void GameScene::Update(float deltaTime)
{
	mainCamera.Render();
	GameLoop(deltaTime);
}


void GameScene::GameLoop(float deltaTime)
{
	ThrowsText.setString(std::to_string(arrowComponent.GetCurrentThrows()) + " / " + std::to_string(arrowComponent.GetMaxThrows()));

	if (arrowComponent.PlayerIsInIdle)
	{
		if (arrowComponent.GetCurrentThrows() > arrowComponent.GetMaxThrows())
		{
			SceneManager::SetLevel(0);
		}
	}

	if (Player->GetPosition().y > 1200)
	{
		SceneManager::SetLevel(0);
	}


	mainCameraObject->SetPosition(sf::Vector2(Player->GetPosition().x - window->getSize().x/2, mainCameraObject->GetPosition().y));

	CalUpdateOnAll(deltaTime);
	physicsEngine.UpdatePhysics(deltaTime);
}


void GameScene::DestroyScene()
{

}

void GameScene::OnKeyDown(sf::Keyboard::Key pressedKey)
{
	float forceToAdd = 10;
	float multiplier = 0.05f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerCollider->AddForce(sf::Vector2f(-forceToAdd * multiplier, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerCollider->AddForce(sf::Vector2f(forceToAdd * multiplier, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerCollider->AddForce(sf::Vector2f(0, -forceToAdd * multiplier));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerCollider->AddForce(sf::Vector2f(0, forceToAdd * multiplier));
	}

}

void GameScene::OnPlayerCollisionEnter(Collider* _collideWith, sf::Vector2f _collisionPoint)
{
	if (_collideWith->GetAttachedObject()->Name == "Target")
	{
		SceneManager::SetLevel(currentLevel + 1);
	}
}

void GameScene::OnSceneChanged()
{
	sceneChanged = true;
}





std::shared_ptr<GameObject> GameScene::CreateBackground()
{
	auto tempBackground = CreateGameObject("Background", 0);
	tempBackground->SetSprite("Background.png");
	return tempBackground;
}

std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CircleCollider>> GameScene::CreatePlayer()
{
	auto _tempPlayer = CreateGameObject("Ball", 20);
	_tempPlayer->SetSprite("assets/Ball.png");

	_tempPlayer->GetSprite()->setScale(sf::Vector2f(0.025f, 0.025f));
	_tempPlayer->SetPosition(300, 400);

	auto _tempPlayerCollider = physicsEngine.CreateCircleCollider(_tempPlayer, sf::Vector2f(0, 0), 15, 15);
	_tempPlayerCollider->OnCollisionEnter()->Subscribe(&GameScene::OnPlayerCollisionEnter, this);
	_tempPlayerCollider->Gravity = true;

	return std::make_tuple(_tempPlayer, _tempPlayerCollider);
}

std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<GameObject>> GameScene::CreateArrows
(std::shared_ptr<GameObject> _player, std::shared_ptr<Collider> _playerCollider, ArrowComponent& _arrowComponent, VisualForceArrow& _arrowVisual, int MaxThrows)
{
	auto tempDirectionArrow = CreateGameObject("directionArrow", 20);
	tempDirectionArrow->SetSprite("Arrow.png");
	tempDirectionArrow->GetSprite()->setScale(0.15, 0.15);

	float directionArrowWidth = tempDirectionArrow->GetSprite()->getTexture()->getSize().x;
	float directionArrowHeight = tempDirectionArrow->GetSprite()->getTexture()->getSize().y;

	sf::Vector2f directionOrigin(directionArrowWidth / 2, directionArrowHeight);
	tempDirectionArrow->GetSprite()->setOrigin(directionOrigin);
	tempDirectionArrow->SetPosition(300, 300);

	auto tempForceArrow = CreateGameObject("forceArrow", 30);
	tempForceArrow->SetSprite("ArrowFull.png");
	tempForceArrow->GetSprite()->setScale(0.15, 0.15);
	tempForceArrow->SetPosition(300, 300);

	_arrowComponent.InitComponent(tempDirectionArrow, _player, _playerCollider, MaxThrows);
	_arrowVisual.InitComponent(tempForceArrow, &_arrowComponent);

	AddComponent(tempDirectionArrow, &_arrowComponent);
	AddComponent(tempForceArrow, &_arrowVisual);

	return std::make_tuple(tempDirectionArrow, tempForceArrow);

}

std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> GameScene::CreateTarget()
{

	std::shared_ptr<GameObject> target = CreateGameObject("Target", 20);
	target->SetSprite("assets/Target.png");
	target->GetSprite()->setScale(sf::Vector2f(0.05f, 0.05f));
	std::shared_ptr<CustomCollider> targetCollider = physicsEngine.CreateCustomCollider(target, {
		sf::Vector2f(15,70),
		sf::Vector2f(45,70),
		sf::Vector2f(60,79),
		sf::Vector2f(60,90),

		sf::Vector2f(45,100),
		sf::Vector2f(15,100),
		sf::Vector2f(0, 90),
		sf::Vector2f(0,79),
		});
	targetCollider->SetIsStatic(true);

	return std::make_tuple(target, targetCollider);

}




std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> GameScene::CreatePlatformeOne()
{

	std::shared_ptr<GameObject> ground = CreateGameObject("ground", 10);
	ground->SetSprite("assets/Platforme1.png");
	ground->GetSprite()->setScale(sf::Vector2f(0.4f, 0.4f));
	ground->SetPosition(300, 700);
	std::shared_ptr<CustomCollider> groundCollider = physicsEngine.CreateCustomCollider(ground, {
		sf::Vector2f(0,100),
		sf::Vector2f(630,100),
		sf::Vector2f(400,350),
		sf::Vector2f(350,350),
		sf::Vector2f(220,200),
		sf::Vector2f(120,200),
		});
	groundCollider->SetIsStatic(true);

	return std::make_tuple(ground, groundCollider);

}




std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> GameScene::CreatePlatformeTwo()
{

	std::shared_ptr<GameObject> ground = CreateGameObject("ground", 10);
	ground->SetSprite("assets/Platforme2.png");
	ground->GetSprite()->setScale(sf::Vector2f(0.2f, 0.2f));
	ground->SetPosition(300, 650);
	std::shared_ptr<CustomCollider> groundCollider = physicsEngine.CreateCustomCollider(ground, {
		sf::Vector2f(0,50),
		sf::Vector2f(525,50),
		sf::Vector2f(275,220),
		sf::Vector2f(250,220),
		sf::Vector2f(220,200),
		sf::Vector2f(120,200),
		});
	groundCollider->SetIsStatic(true);

	return std::make_tuple(ground, groundCollider);

}


std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> GameScene::CreatePlatformeThree()
{

	std::shared_ptr<GameObject> ground = CreateGameObject("ground", 10);
	ground->SetSprite("assets/Platforme3.png");
	ground->GetSprite()->setScale(sf::Vector2f(0.4f, 0.4f));
	ground->SetPosition(300, 600);
	std::shared_ptr<CustomCollider> groundCollider = physicsEngine.CreateCustomCollider(ground, {
		sf::Vector2f(0,100),
		sf::Vector2f(750,100),
		sf::Vector2f(430,280),
		sf::Vector2f(190,280),
		});
	groundCollider->SetIsStatic(true);

	return std::make_tuple(ground, groundCollider);

}



std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> GameScene::CreatePlatformeFour()
{

	std::shared_ptr<GameObject> ground = CreateGameObject("ground", 10);
	ground->SetSprite("assets/Platforme4.png");
	ground->GetSprite()->setScale(sf::Vector2f(0.15f, 0.15f));
	ground->SetPosition(300, 700);
	std::shared_ptr<CustomCollider> groundCollider = physicsEngine.CreateCustomCollider(ground, {
		sf::Vector2f(0,50),
		sf::Vector2f(355,50),
		sf::Vector2f(220,150),
		sf::Vector2f(120,150),
		});
	groundCollider->SetIsStatic(true);

	return std::make_tuple(ground, groundCollider);

}
