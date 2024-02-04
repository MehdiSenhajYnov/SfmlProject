#include "SceneManager.h"

SceneManager::SceneEnum SceneManager::currentScene;
Event<SceneManager::SceneEnum> SceneManager::OnSceneChanged;

void SceneManager::ChangeScene(SceneEnum newScene)
{
	currentScene = newScene;
	OnSceneChanged.InvokeEvent(newScene);
}