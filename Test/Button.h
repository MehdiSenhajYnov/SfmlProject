#pragma once
#include "Component.h"
#include "Camera.h"
#include "Event.h"

class Button : public Component
{
public:
	void Init(std::shared_ptr<GameObject> _gameObject, std::string _buttonString, Camera* _camera);
	void SetString(std::string _buttonString);

	sf::Text* GetText();

	Event<> OnButtonClicked;

	bool IsInButton(sf::Vector2i positionToCheck);

	// Hérité via Component
	void Start() override;
	void Logs(sf::Vector2i positionToCheck);
	void Update(float deltaTime) override;
private:
	void UpdatePosition();
	Camera* camera;
	static sf::Font font;
	static bool fontLoaded;
	sf::Text buttonText;
	sf::Vector2f oldObjPosition;
	bool isMousePressed;
	bool ClickOnTheButton;


};

