#include "Button.h"

sf::Font Button::font;
bool Button::fontLoaded;

void Button::Init(std::shared_ptr<GameObject> _gameObject, std::string _buttonString, Camera* _camera)
{
	LoadComponentBase(_gameObject);

	if (!fontLoaded)
	{
		if (!font.loadFromFile("fonts/Arial.ttf"))
		{
			std::cout << "ERROR" << std::endl;
		}
		else
		{
			fontLoaded = true;
		}

	}
	
	buttonText.setFont(font); // font is a sf::Font


	// set the character size
	buttonText.setCharacterSize(48); // in pixels, not points!
	buttonText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	// set the color
	buttonText.setFillColor(sf::Color::Black);
	SetString(_buttonString);

	UpdatePosition();

	camera = _camera;
	camera->AddToTexts(&buttonText);
}

void Button::SetString(std::string _buttonString)
{
	buttonText.setString(_buttonString);
	sf::FloatRect textRect = buttonText.getLocalBounds();
	buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

sf::Text* Button::GetText()
{
	return &buttonText;
}

bool Button::IsInButton(sf::Vector2i positionToCheck)
{
	if (!camera->IsOnDisplay(gameObject.get()))
	{
		return false;
	}
	//if (gameObject->Name == "exitButton")
	//{
	//	Logs(positionToCheck);
	//}

	if (positionToCheck.x < (gameObject->GetPosition().x - camera->GetAttachedObject()->GetPosition().x))
	{
		return false;
	}

	if (positionToCheck.y < (gameObject->GetPosition().y - camera->GetAttachedObject()->GetPosition().y))
	{
		return false;
	}

	if (gameObject->GetSprite()->getTexture() != nullptr)
	{
		if (positionToCheck.x > (gameObject->GetPosition().x - camera->GetAttachedObject()->GetPosition().x) +
			(gameObject->GetSprite()->getTexture()->getSize().x * gameObject->GetSprite()->getScale().x))
		{
			return false;

		}


		if (positionToCheck.y > (gameObject->GetPosition().y - camera->GetAttachedObject()->GetPosition().y) +
			(gameObject->GetSprite()->getTexture()->getSize().y * gameObject->GetSprite()->getScale().y))
		{
			return false;
		}

	}
	else
	{
		if (positionToCheck.x > (gameObject->GetPosition().x - camera->GetAttachedObject()->GetPosition().x) + gameObject->GetSprite()->getScale().x)
		{
			return false;
		}

		if (positionToCheck.y > (gameObject->GetPosition().y - camera->GetAttachedObject()->GetPosition().y) + gameObject->GetSprite()->getScale().y)
		{
			return false;
		}

	}
	return true;
}

void Button::Start()
{
}

void Button::Logs(sf::Vector2i positionToCheck)
{
	auto vectorToStr = [](sf::Vector2f toconvert) { return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); };
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "mouse position : " << vectorToStr(sf::Vector2f(positionToCheck.x, positionToCheck.y)) << std::endl;
	std::cout << "gameObject position : " << vectorToStr(gameObject->GetPosition()) << std::endl;
	std::cout << "gameObjectWithCamereOffset position : " << vectorToStr(gameObject->GetPosition() - camera->GetAttachedObject()->GetPosition()) << std::endl;

	sf::Vector2f limits = gameObject->GetPosition() - camera->GetAttachedObject()->GetPosition();
	limits = limits + sf::Vector2f(
		gameObject->GetSprite()->getTexture()->getSize().x * gameObject->GetSprite()->getScale().x,
		gameObject->GetSprite()->getTexture()->getSize().y * gameObject->GetSprite()->getScale().y
	);

	std::cout << "limits : " << vectorToStr(limits) << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}

void Button::Update(float deltaTime)
{
	if (oldObjPosition != gameObject->GetPosition())
	{
		UpdatePosition();
	}
	//std::cout << "update" << std::endl;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//std::cout << "Mouse click first" << std::endl;
		if (!isMousePressed)
		{
			//std::cout << "Mouse click" << std::endl;
			isMousePressed = true;
			if (IsInButton(sf::Mouse::getPosition(*camera->GetCurrentWindow())))
			{
				//std::cout << "click on the button" << std::endl;
				ClickOnTheButton = true;
			}
		}
	}
	else
	{
		if (isMousePressed)
		{
			if (IsInButton(sf::Mouse::getPosition(*camera->GetCurrentWindow())))
			{
				if (ClickOnTheButton)
				{
					OnButtonClicked.InvokeEvent();
				}
			}
		}
		ClickOnTheButton = false;
		isMousePressed = false;
	}


}



void Button::UpdatePosition()
{
	sf::Vector2f newPos;
	if (gameObject->GetSprite()->getTexture() != nullptr)
	{
		newPos.x = gameObject->GetPosition().x + ((gameObject->GetSprite()->getTexture()->getSize().x * gameObject->GetSprite()->getScale().x) / 2);
		newPos.y = gameObject->GetPosition().y + ((gameObject->GetSprite()->getTexture()->getSize().y * gameObject->GetSprite()->getScale().y) / 2);
	}
	else
	{
		newPos.x = gameObject->GetPosition().x + (gameObject->GetSprite()->getScale().x / 2);
		newPos.y = gameObject->GetPosition().y + (gameObject->GetSprite()->getScale().y / 2);
	}

	buttonText.setPosition(newPos);

	oldObjPosition = gameObject->GetPosition();
}

