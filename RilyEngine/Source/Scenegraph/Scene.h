#pragma once

namespace Scenegraph
{


class SceneObject;

class Scene
{
public:
	Scene(const std::string& name);
	~Scene();

	void Update(float deltaTime);
	void Render();

	void AddObject(SceneObject* pObject);
	void RemoveObject(SceneObject* pObject);
	void RemoveObject(uint_t id);

	std::string GetName() const { return m_Name; }

private:
	std::string m_Name;
	std::unordered_map<uint_t, SceneObject*> m_Objects;
};

}
