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
	static void AddToPermanentDrawablesObjects(sf::Shape* drawableToAdd, std::shared_ptr<GameObject> attachedObject);
	static void RemoveFromPermanentDrawablesObjects(sf::Shape* drawableToRemove);
	void Initialize(std::shared_ptr<GameObject> _gameObject, sf::Vector2<float> _cameraView, sf::RenderWindow* _window, Scene* _scene);
private:
	static std::map <sf::Shape*, std::shared_ptr<GameObject>> PermanentDrawablesObjects;
	sf::Vector2<float> CameraView;
	sf::RenderWindow* window;
	Scene* scene;

	void Start() override;
	void Update(float deltaTime) override;

};

