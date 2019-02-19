#pragma once

#include <Core\GameBase.h>

namespace Geometry::Prefab
{
	class PrefabBase;
}

class RilyGame : public Core::GameBase
{
public:
	RilyGame();
	virtual ~RilyGame();

	void Start();

protected:
	int Initialize() override;
	void Update() override;
	void Shutdown() override;

private:
	void InitializeTestScene();
	void LogTest() const;

private:
	static const std::string NAME;
	static const std::string SETTINGS_PATH;

	Geometry::Prefab::PrefabBase* m_pPrefab = nullptr;
};

