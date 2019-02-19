#include <stdafx.h>
#include "RilyGame.h"

#include <Core/System/Systems.h>
#include <Core/Managers/SystemManager.h>
#include <Core/Managers/InputManager.h>
#include <Core/Managers/SceneManager.h>
#include <Core/System/Window.h>
#include <Core/Engine.h>

#include <Geometry/Prefabs/Plane.h>
#include <Geometry/Prefabs/TeaPot.h>
#include <Geometry/Prefabs/EmptyObject.h>

#include <Graphics/Materials/DefaultMaterial.h>

#include <Graphics/Rendering/Renderer.h>
#include <Graphics/Camera.h>

#include <Content/Readers/ObjReader.h>

#include <Resources/ResourceLoader.h>

#include <Scenegraph/Scene.h>

const std::string RilyGame::NAME = "Rily Game";
const std::string RilyGame::SETTINGS_PATH = "Data/Settings/RilyGame.ini";

RilyGame::RilyGame():
	GameBase("Rily Game", Resources::ResourceLoader::LoadGameSettings(SETTINGS_PATH))
{
}


RilyGame::~RilyGame()
{
}

void RilyGame::Start()
{
	this->Initialize();
	
	while (!SystemManager::GetInstance()->GetWindow()->IsClosed())
		this->Update();

	this->Shutdown();
}

int RilyGame::Initialize()
{
	GameBase::Initialize();
	this->InitializeTestScene();

	LogTest();

	return OK;
}

void RilyGame::LogTest() const
{
	Math::Vec3 myVector = ZeroVec3;

	Debug::Log(Debug::LogType::ERROR, "This is an error");
	Debug::Log(Debug::LogType::WARNING, "This is an warning");
	Debug::Log(Debug::LogType::INFO, "This is just info");
	Debug::Log(Debug::LogType::FORCE, "This is an forced log");

	Debug::NewLine();

	Debug::Log(Debug::LogType::INFO, "The value of the vector is: ", myVector);

	Debug::NewLine();
	Debug::NewLine();
}

void RilyGame::Update()
{
	GameBase::Update();

	SceneManager::GetInstance()->GetActiveScene()->Update(SystemManager::GetInstance()->GetClock()->GetDeltaTime());
	SceneManager::GetInstance()->GetActiveScene()->Render();

	Camera* pCamera = SystemManager::GetInstance()->GetWindow()->GetCamera();

	if (InputManager::GetInstance()->IsKeyDown("W"))
		pCamera->Translate(pCamera->GetFoward() * 0.1f);
	if (InputManager::GetInstance()->IsKeyDown("A"))
		pCamera->Translate(pCamera->GetLeft() * 0.1f);
	if (InputManager::GetInstance()->IsKeyDown("S"))
		pCamera->Translate(pCamera->GetBack() * 0.1f);
	if (InputManager::GetInstance()->IsKeyDown("D"))
		pCamera->Translate(pCamera->GetRight() * 0.1f);

	if (InputManager::GetInstance()->IsMouseDown(SDL_BUTTON_MIDDLE))
	{
		Math::Vec2 mouseMovement = InputManager::GetInstance()->GetMouseMovement();

		const float mouseSensivity = 0.005f;
		mouseMovement *= mouseSensivity;
		pCamera->Rotate(Math::Vec3(0, 1.0f, 0), mouseMovement.x);
		pCamera->Rotate(Math::Vec3(1.0f, 0, 0), mouseMovement.y);
	}
}

void RilyGame::Shutdown()
{
	GameBase::Shutdown();
}

void RilyGame::InitializeTestScene()
{
	Scenegraph::Scene* pNewScene = new Scenegraph::Scene("RootScene");

	Geometry::Prefab::EmptyObject* pDrone = new Geometry::Prefab::EmptyObject("DroneTank", new Component::UnitTransformComponent);
	pDrone->SetMesh(new Component::MeshFilter(Content::Reader::ObjReader::Read("Data/Meshes/SniperTank.obj"),new Graphics::Material::DefaultMaterial()));
	pDrone->SetScale(Math::Vec3(0.1f, 0.1f, 0.1f));
	pNewScene->AddObject(pDrone);

	//m_pPrefab = new Geometry::Prefab::Teapot("Plane A", new Component::UnitTransformComponent, new Graphics::Material::DefaultMaterial(Math::Color::White));
	//pNewScene->AddObject(m_pPrefab);

	//m_pPrefab->Translate(Math::Vec3(-10, 0, 0));
	//m_pPrefab->Rotate(Math::Vec3::Left, RL_PI_DIV_2_FLOAT);
	//m_pPrefab->Scale(Math::Vec3(0.1f, 0.1f, 0.1f));

	//m_pPrefab = new Geometry::Prefab::Teapot("Teapot A", new Component::UnitTransformComponent, new Graphics::Material::DefaultMaterial(Math::Color::Red));
	//pNewScene->AddObject(m_pPrefab);

	//m_pPrefab->SetScale(Math::Vec3(0.1f, 0.1f, 0.1f));
	//m_pPrefab->Translate(Math::Vec3(1, 0, 0));

	SceneManager::GetInstance()->AddScene(pNewScene);
	SceneManager::GetInstance()->SetActiveScene(pNewScene);
}