#include "stdafx.h"

#include "ResourceManager.h"

#include "Resources/Files/TextFile.h"
#include "Resources/Shaders/ShaderSource.h"
#include "Resources/Resource.h"

struct DefaultResourceDesc
{
	DefaultResourceDesc(const std::string& path, Resources::ResourceType type) :
		Path(path),
		Type(type)
	{
	}

	std::string Path;
	Resources::ResourceType Type;
};

ResourceManager::ResourceManager()
{
	m_Resources.DeleteAllPointers();
}


ResourceManager::~ResourceManager()
{
	for (Resources::Resource* pResource : m_Resources)
	{
		Debug::Log(Debug::LogType::WARNING, "Resource not yet deleted\nWith name: ", pResource->GetName(), "\n");
		delete pResource;
	}
}

int ResourceManager::Initialize()
{
	LoadDefaultResources(LoadDefaultResourcePaths());
	return OK;
}

bool ResourceManager::AddResource(Resources::Resource* pResource)
{
	auto it = std::find_if(m_Resources.Begin(), m_Resources.End(),
		[&](Resources::Resource* pOldResource)
	{
		return pOldResource->GetFullPath() == pResource->GetFullPath();
	});

	if (it != m_Resources.End())
	{
		Debug::Log(Debug::LogType::WARNING, "Resource with name ", pResource->GetName(), " already added\n");
		return false;
	}
	
	m_Resources.AddC(pResource);
	return true;
}

Resources::Resource* ResourceManager::LoadShaderSource(const std::string& path, Resources::ShaderType type)
{
	const std::string fullPath = SHADER_PATH + path;
	Resources::Resource* pSource = this->GetResourceWithFullPath(fullPath);
	if (pSource)
		return pSource;

	pSource = new Resources::ShaderSource(fullPath, type);

	if (!pSource)
	{
		Debug::Log(Debug::LogType::WARNING, "Failed to load shader at path\n", fullPath, "\n");
		return nullptr;
	}

	dynamic_cast<Resources::ShaderSource*>(pSource)->LoadCode();
	return pSource;
}

bool ResourceManager::RemoveResource(Resources::Resource* pResource)
{
	m_Resources.Remove(pResource);
	return true;
}

Resources::Resource* ResourceManager::GetResourceWithName(const std::string& name)
{
	auto it = std::find_if(m_Resources.Begin(), m_Resources.End(),
		[&](Resources::Resource* pResource)
	{
		return pResource->GetName() == name;
	});

	if (it == m_Resources.End())
		return nullptr;

	return *it;
}

Resources::Resource* ResourceManager::GetResourceWithFullPath(const std::string& path)
{
	auto it = std::find_if(m_Resources.Begin(), m_Resources.End(),
		[&](Resources::Resource* pResource)
	{
		return pResource->GetFullPath() == path;
	});

	if (it == m_Resources.End())
		return nullptr;

	return *it;
}

OptionalReturnWrapper<Container::Vector<DefaultResourceDesc>> ResourceManager::LoadDefaultResourcePaths()
{
	Resources::TextFile file = std::move(Resources::TextFile(DEFAULT_RESOURCES_PATH));
	file.Open(std::ios::in);
	if (!file.IsOpen())
		return COULD_NOT_OPEN_RESOURCE;

	Container::Vector<DefaultResourceDesc> defaultResources;
	while (!file.EndOfFile())
	{
		std::string path = std::move(file.ReadLine());
		Resources::ResourceType type = (Resources::ResourceType)std::move(std::stoi(std::move(file.ReadLine())));
		defaultResources.AddM(std::move(DefaultResourceDesc(path, type)));
	}

	file.Close();
	return defaultResources;
}

void ResourceManager::LoadDefaultResources(const Container::Vector<DefaultResourceDesc>& descs)
{
	for (DefaultResourceDesc desc : descs)
	{
		switch (desc.Type)
		{
		case Resources::ResourceType::TEXT_FILE:
		{
			Resources::TextFile* pFile = new Resources::TextFile(desc.Path);
			if (!pFile->Exists())
				Debug::Log(Debug::LogType::WARNING, "Could not open default resource with path\n", pFile->GetFullPath());
			else
			{
				pFile->ReadFullFile();
				this->AddResource(pFile);
			}
			break;
		}
		case Resources::ResourceType::VERTEX_SHADER:
		{
			Resources::ShaderSource* pShader = new Resources::ShaderSource(desc.Path, Resources::ShaderType::VERTEX);
			pShader->LoadCode();
			break;
		}
		case Resources::ResourceType::GEOMETRY_SHADER:
		{
			Resources::ShaderSource* pShader = new Resources::ShaderSource(desc.Path, Resources::ShaderType::GEOMETRY);
			pShader->LoadCode();
			break;
		}
		case Resources::ResourceType::FRAGMENT_SHADER:
		{
			Resources::ShaderSource* pShader = new Resources::ShaderSource(desc.Path, Resources::ShaderType::FRAGMENT);
			pShader->LoadCode();
			break;
		}
		default:
			ASSERT(false, "resource type not implented yet");
			break;
		}
	}
}