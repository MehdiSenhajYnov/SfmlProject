#include "GameScene.h"

GameScene::GameScene()
{
}

void GameScene::InitializeScene(sf::RenderWindow* _window)
{
	oldCurrentForce = -9999;
	isMousePressed = false;
	window = _window;
	mainCameraObject = CreateGameObject("mainCameraObject");
	mainCamera = Camera();
	mainCamera.Initialize(mainCameraObject, sf::Vector2f(10000, 10000), window, this);

	AddComponent(mainCameraObject, &mainCamera);
	graphicDebugger = GraphicDebugger();
	graphicDebugger.Init(&mainCamera, 15);
	
	physicsEngine = PhysicsEngine();
	physicsEngine.Init(this, &graphicDebugger);

	//graphicDebugger.Disable();

	Player = CreateGameObject("Ball");
	Player->SetSprite("Circle.png");
	Player->SetPosition(300,600);
	float ballcolliderlength = 100;

	playerCollider = physicsEngine.CreateCircleCollider(Player, sf::Vector2f(0, 0), 50, 30);
	playerCollider->OnCollisionEnter()->Subscribe(&GameScene::OnPlayerCollisionEnter, this);

	std::shared_ptr<GameObject> box = CreateGameObject("Box");
	box.get()->SetSprite("Square.png");
	box.get()->SetPosition(0, 0);
	std::shared_ptr<BoxCollider> boxCollider = physicsEngine.CreateBoxCollider(box, sf::Vector2f(0, 0), sf::Vector2f(100, 100));



	//sf::Thread thread(&Camera::RenderingThread, &mainCamera);
	//thread.launch();

	sf::Clock dtClock;
	float deltaTime;


	sf::Vector2f basePosition(300, 300);

	int circleRadius = 200;
	sf::CircleShape circle(circleRadius);

	circle.setPosition(basePosition);
	circle.setOutlineColor(sf::Color::Red);
	circle.setOutlineThickness(5);
	circle.setFillColor(sf::Color::Transparent);

	int shapePoints = 8;

	auto RegularShape = CreateGameObject("RegularShape");
	std::shared_ptr<CircleCollider> testshapeCollider =
		physicsEngine.CreateCircleCollider(RegularShape, sf::Vector2f(0, 0), 100, 50);
	RegularShape->SetPosition(200, 0);



	playerCollider->Gravity = true;


	std::shared_ptr<GameObject> ground = CreateGameObject("ground");
	//ground.get()->SetSprite("Square.png");
	ground->SetPosition(-2000, 750);
	std::shared_ptr<BoxCollider> groundCollider = physicsEngine.CreateBoxCollider(ground, sf::Vector2f(0, 0), sf::Vector2f(5000, 100));

	directionArrow = CreateGameObject("directionArrow");
	directionArrow->SetSprite("Arrow.png");
	directionArrow->GetSprite()->setScale(0.15, 0.15);
	
	forceArrow = CreateGameObject("forceArrow");
	forceArrow->SetSprite("ArrowFull.png");
	forceArrow->GetSprite()->setScale(0.15, 0.15);

	float directionArrowWidth = directionArrow->GetSprite()->getTexture()->getSize().x;
	float directionArrowHeight = directionArrow->GetSprite()->getTexture()->getSize().y;

	sf::Vector2f directionOrigin(directionArrowWidth / 2, directionArrowHeight);
	directionArrow->GetSprite()->setOrigin(directionOrigin);
	directionArrow->SetPosition(300, 300);

	forceArrow->SetPosition(300, 300);

	physicsEngine.SwitchModifyMode();


	//playerCollider->AddForce(sf::Vector2f(0, -3300));
}

void GameScene::Update(float deltaTime)
{
	mainCamera.Render();
	KeyboardEvents();
	GameLoop(deltaTime);
}

void GameScene::KeyboardEvents()
{


}

void GameScene::GameLoop(float deltaTime)
{
	float multiplier = 30;

	if (playerCollider != nullptr && playerCollider->GetVelocity() != sf::Vector2f(0,0))
	{
		//std::cout << "Player velocity = x: " << playerCollider->GetVelocity().x << " y: " 
		//	<< playerCollider->GetVelocity().y << std::endl;

		//std::cout << "Player Acceleration = x: " << playerCollider->GetAcceleration().x << " y: "
		//	<< playerCollider->GetAcceleration().y << std::endl;
	}


	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	//{
	//	//Player->Move(-10 * multiplier * deltaTime, 0);
	//	physicsEngine.MoveObject(playerCollider.get(), sf::Vector2f(-10 * multiplier * deltaTime, 0));
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//{
	//	//Player->Move(10 * multiplier * deltaTime, 0);
	//	physicsEngine.MoveObject(playerCollider.get(), sf::Vector2f(10 * multiplier * deltaTime, 0));
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	//{
	//	//Player->Move(0, -10 * multiplier * deltaTime);
	//	physicsEngine.MoveObject(playerCollider.get(), sf::Vector2f(0, -10* multiplier * deltaTime));
	//}

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	//Player->Move(0, 10 * multiplier * deltaTime);
	//	physicsEngine.MoveObject(playerCollider.get(), sf::Vector2f(0, 10 * multiplier * deltaTime));
	//}
	if (physicsEngine.SomeObjecsAreColliding())
	{
		//std::cout << "something collides" << std::endl;
		Player->GetSprite()->setColor(sf::Color::Red);
	}
	else
	{
		Player->GetSprite()->setColor(sf::Color::Black);
	}




	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!isMousePressed)
		{
			isMousePressed = true;
			MouseInitialPosition = sf::Mouse::getPosition();
		}

		forceToGive = MouseInitialPosition - sf::Mouse::getPosition();
		currentForce = (abs(forceToGive.x) + abs(forceToGive.y)) / 2;


		sf::Vector2f targetPosition = directionArrow->GetPosition() + sf::Vector2f(forceToGive);


		// Calcul de l'angle entre la position actuelle de l'objet et le point cible
		currentAngle = std::atan2(targetPosition.y - directionArrow->GetPosition().y,
								 targetPosition.x - directionArrow->GetPosition().x);
		currentAngle = currentAngle * 180 / 3.14159265; // Convertir de radians à degrés
		currentAngle += 90;

		directionArrow->SetRotation(currentAngle);




	}
	else
	{
		if (isMousePressed)
		{
			forceToGive = MouseInitialPosition - sf::Mouse::getPosition();
			std::cout << "Force x: " << forceToGive.x <<" y:" << forceToGive.y << std::endl;
			isMousePressed = false;

			float multiplier = 10;
			playerCollider->AddForce(sf::Vector2f(forceToGive.x, forceToGive.y) * multiplier);
			forceToGive = sf::Vector2i(0, 0);
		}
	}




	float angleRadians = (currentAngle - 90) * (3.41 / 180.0);

	sf::Vector2f original(1, 0);




	sf::Vector2f playerCenter =
		sf::Vector2f(Player->GetPosition().x + (Player->GetSprite()->getTexture()->getSize().x / 2),
			Player->GetPosition().y + (Player->GetSprite()->getTexture()->getSize().y / 2));

	sf::Vector2f playerTopPosition =
		sf::Vector2f(Player->GetPosition().x + (Player->GetSprite()->getTexture()->getSize().x / 2),
			Player->GetPosition().y);

	float rayon = abs(playerCenter.y - playerTopPosition.y);

	// Calculer les nouvelles coordonnées après la rotation
	float rotatedX = rayon * cos(angleRadians);
	float rotatedY = rayon * sin(angleRadians);

	sf::Vector2f rotatedVector(rotatedX, rotatedY);
	rotatedVector.x *= 1.5;
	rotatedVector.y *= 1.5;
	directionArrow->SetPosition(playerCenter + rotatedVector);

	//std::cout << "Player Center x:" << playerCenter.x << " y:" << playerCenter.y << std::endl;
	//std::cout << "rotatedVector x:" << rotatedVector.x << " y:" << rotatedVector.y << std::endl;
	//std::cout << "ArrowPosition x:" << forceArrow->GetPosition().x << " y:" << forceArrow->GetPosition().y << std::endl;

	forceArrow->SetPosition(directionArrow->GetPosition());
	forceArrow->SetRotation(directionArrow->GetRotation());

	if (currentForce != oldCurrentForce)
	{
		if (currentForce < 0)
		{
			currentForce = 0;
		} else if (currentForce > 648)
		{
			currentForce = 648;
		}
		forceArrow->GetSprite()->setTextureRect(sf::IntRect(0, 648 - currentForce, 450, currentForce));

		float forceArrowWidth = forceArrow->GetSprite()->getTexture()->getSize().x;
		float forceArrowHeight = currentForce;

		sf::Vector2f forceOrigin(forceArrowWidth / 2, forceArrowHeight);
		forceArrow->GetSprite()->setOrigin(forceOrigin);
		oldCurrentForce = currentForce;
	}

	//mainCameraObject->SetPosition(sf::Vector2(Player->GetPosition().x - window->getSize().x/2, mainCameraObject->GetPosition().y));

	CalUpdateOnAll(deltaTime);
	physicsEngine.UpdatePhysics(deltaTime);
}


void GameScene::DestroyScene()
{

}

void GameScene::OnKeyDown(sf::Keyboard::Key pressedKey)
{
	float forceToAdd = 10;
	float multiplier = 50;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		currentForce += 50;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		currentForce -= 50;
	}
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
	//std::cout << "player collide with : " << _collideWith->GetAttachedObject()->Name;
	//std::cout << " at x : " << _collisionPoint.x << " at y : " << _collisionPoint.y << std::endl;
}


