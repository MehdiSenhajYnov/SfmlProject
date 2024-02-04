#pragma once
#include "Event.h"

class SceneManager
{
public:
	enum SceneEnum { Menu, LevelOne, LevelTwo, LevelThree };
	static SceneEnum currentScene;
	static void ChangeScene(SceneEnum newScene);
	static Event<SceneManager::SceneEnum> OnSceneChanged;
private:

};

