#include "stdafx.h"

#include "SceneManager.h"

#include "Scenegraph/Scene.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	std::for_each(m_Scenes.begin(), m_Scenes.end(),
		[&](auto pair)
	{
		SAFE_DELETE(pair.second);
	});
}

void SceneManager::AddScene(Scenegraph::Scene* pScene)
{
	m_Scenes[pScene->GetName()] = pScene;
}

void SceneManager::RemoveScene(const std::string& name)
{
	SAFE_DELETE(m_Scenes[name]);
}

void SceneManager::SetActiveScene(Scenegraph::Scene* pScene)
{
	m_pActiveScene = pScene;
}