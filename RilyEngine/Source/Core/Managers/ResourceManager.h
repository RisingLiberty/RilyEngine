#pragma once
#include "../../Helper/Singleton.h"

struct DefaultResourceDesc;

namespace Resources
{
	class Resource;
	enum class ShaderType;
}

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	int Initialize();

	bool AddResource(Resources::Resource* pResource);
	bool RemoveResource(Resources::Resource* pResource);

	Resources::Resource* LoadShaderSource(const std::string& path, Resources::ShaderType type);

	Resources::Resource* GetResourceWithName(const std::string& name);
	Resources::Resource* GetResourceWithFullPath(const std::string& path);

private:

	OptionalReturnWrapper<Container::Vector<DefaultResourceDesc>> LoadDefaultResourcePaths();
	void LoadDefaultResources(const Container::Vector<DefaultResourceDesc>& descs);

private:
	Container::Vector<Resources::Resource*> m_Resources;

	const std::string DEFAULT_RESOURCES_PATH = RESOURCES_PATH + "Default_Resources.dat";
};

