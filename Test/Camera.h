#pragma once
#include "Scene.h"
#include "Component.h"

class Camera : public Component
{
public:
	Camera();
	void StartRenderingThread();
	void RenderingThread();
	void Render();
	bool IsOnDisplay(GameObject* toCheck);
	void AddToPermanentDrawablesObjects(sf::Shape* drawableToAdd, std::shared_ptr<GameObject> attachedObject);
	void RemoveFromPermanentDrawablesObjects(sf::Shape* drawableToRemove);

	void AddToTexts(sf::Text* textToAdd);
	void RemoveFromTexts(sf::Text* textToRemove);

	sf::RenderWindow* GetCurrentWindow();


	void Initialize(std::shared_ptr<GameObject> _gameObject, sf::Vector2<float> _cameraView, sf::RenderWindow* _window, Scene* _scene);
private:
	std::vector<sf::Text*> Texts;
	std::map <sf::Shape*, std::shared_ptr<GameObject>> PermanentDrawablesObjects;
	sf::Vector2<float> CameraView;
	sf::RenderWindow* window;
	Scene* scene;

	void Start() override;
	void Update(float deltaTime) override;

};

