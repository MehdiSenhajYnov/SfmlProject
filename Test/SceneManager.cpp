#include "SceneManager.h"

SceneManager::SceneEnum SceneManager::currentScene;
Event<SceneManager::SceneEnum> SceneManager::OnSceneChanged;

void SceneManager::ChangeScene(SceneEnum newScene)
{
	currentScene = newScene;
	OnSceneChanged.InvokeEvent(newScene);
}

void SceneManager::SetLevel(int newLevel)
{
    if (newLevel == 0)
    {
        ChangeScene(SceneEnum::Menu);
    }
    else if (newLevel == 1) 
    {
        ChangeScene(SceneEnum::Level1);
    }
    else if (newLevel == 2) 
    {
        ChangeScene(SceneEnum::Level2);
    }
    else if (newLevel == 3) 
    {
        ChangeScene(SceneEnum::Level3);
    }
    else
    {
        ChangeScene(SceneEnum::Menu);
    }

	//currentScene = newScene;
	//OnSceneChanged.InvokeEvent(newScene);
}