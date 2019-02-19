#pragma once

#include "../../Helper/Singleton.h"

namespace Scenegraph
{
	class Scene;
}

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	void AddScene(Scenegraph::Scene* pScene);
	void RemoveScene(const std::string& name);

	Scenegraph::Scene* GetActiveScene() const { return m_pActiveScene; }
	void SetActiveScene(Scenegraph::Scene* pScene);

private:
	std::unordered_map<std::string, Scenegraph::Scene*> m_Scenes;
	Scenegraph::Scene* m_pActiveScene;
};

