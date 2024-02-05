#include "ArrowComponent.h"

void ArrowComponent::Start()
{
	oldCurrentForce = -9999;
	isMousePressed = false;
}

void ArrowComponent::Update(float deltaTime)
{

	CheckIfPlayerIsInIdle();

	if (currentThrows <= maxThrows && PlayerIsInIdleShort)
	{

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!isMousePressed)
			{
				isMousePressed = true;
				MouseInitialPosition = sf::Mouse::getPosition();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				rightMouseClicked = true;
			}

			if (!rightMouseClicked)
			{

				forceToGive = MouseInitialPosition - sf::Mouse::getPosition();
				currentForce = (abs(forceToGive.x) + abs(forceToGive.y)) / 2;


				sf::Vector2f targetPosition = gameObject->GetPosition() + sf::Vector2f(forceToGive);


				// Calcul de l'angle entre la position actuelle de l'objet et le point cible
				currentAngle = std::atan2(targetPosition.y - gameObject->GetPosition().y,
				targetPosition.x - gameObject->GetPosition().x);
				currentAngle = currentAngle * 180 / 3.14159265; // Convertir de radians à degrés
				currentAngle += 90;

				gameObject->SetRotation(currentAngle);

			}

		}
		else
		{


			if (isMousePressed)
			{
				if (!rightMouseClicked)
				{
					forceToGive = MouseInitialPosition - sf::Mouse::getPosition();
					std::cout << "Force x: " << forceToGive.x << " y:" << forceToGive.y << std::endl;
					isMousePressed = false;

					float multiplier = 0.017f;
					currentThrows += 1;
					playerCollider->AddForce(sf::Vector2f(forceToGive.x, forceToGive.y) * multiplier);
					forceToGive = sf::Vector2i(0, 0);
				}
				rightMouseClicked = false;
				isMousePressed = false;
			}

			

		}
	}

	float angleRadians = (currentAngle - 90) * (3.41 / 180.0);

	sf::Vector2f original(1, 0);

	sf::Vector2u CurrentPlayerSize = player->GetSprite()->getTexture()->getSize();
	CurrentPlayerSize.x = CurrentPlayerSize.x * player->GetSprite()->getScale().x;
	CurrentPlayerSize.y = CurrentPlayerSize.y * player->GetSprite()->getScale().y;

	sf::Vector2f playerCenter =
		sf::Vector2f(player->GetPosition().x + (CurrentPlayerSize.x / 2),
			player->GetPosition().y + (CurrentPlayerSize.y / 2));

	sf::Vector2f playerTopPosition =
		sf::Vector2f(player->GetPosition().x + (CurrentPlayerSize.x / 2),
			player->GetPosition().y);

	float rayon = abs(playerCenter.y - playerTopPosition.y);
	float rotatedX = rayon * cos(angleRadians);
	float rotatedY = rayon * sin(angleRadians);

	sf::Vector2f rotatedVector(rotatedX, rotatedY);
	rotatedVector.x *= 1.5;
	rotatedVector.y *= 1.5;
	gameObject->SetPosition(playerCenter + rotatedVector);

	if (currentForce != oldCurrentForce)
	{
		if (currentForce < 0)
		{
			currentForce = 0;
		}
		else if (currentForce > 648)
		{
			currentForce = 648;
		}

		oldCurrentForce = currentForce;
	}

}

float ArrowComponent::GetCurrentForce()
{
	return currentForce;
}

float ArrowComponent::GetOldCurrentForce()
{
	return oldCurrentForce;
}

void ArrowComponent::CheckIfPlayerIsInIdle()
{
	float xDifference = std::abs(player->GetPosition().x - oldPlayerPosition.x);
	float yDifference = std::abs(player->GetPosition().y - oldPlayerPosition.y);
	//std::cout << "xdifference : " << xDifference << " yDifference : " << yDifference << std::endl;
	if (xDifference < 0.5f && yDifference < 0.5f)
	{
		counterOffSamePosition += 1;
		if (counterOffSamePosition > 100)
		{
			PlayerIsInIdleShort = true;
		}


		if (counterOffSamePosition > 750)
		{
			counterOffSamePosition = 0;
			PlayerIsInIdle = true;
		}
	}
	else
	{
		PlayerIsInIdleShort = false;
		PlayerIsInIdle = false;
		counterOffSamePosition = 0;
	}

	oldPlayerPosition = player->GetPosition();
}

int ArrowComponent::GetMaxThrows()
{
	return maxThrows;
}

int ArrowComponent::GetCurrentThrows()
{
	return currentThrows;
}

void ArrowComponent::InitComponent(std::shared_ptr<GameObject> _gameObject, std::shared_ptr<GameObject> _player, std::shared_ptr<Collider> _playerCollider, int _maxThrows)
{
	LoadComponentBase(_gameObject);
	player = _player;
	playerCollider = _playerCollider;
	maxThrows = _maxThrows;
	oldPlayerPosition = player->GetPosition();
	PlayerIsInIdle = true;
	PlayerIsInIdleShort = true;

}
