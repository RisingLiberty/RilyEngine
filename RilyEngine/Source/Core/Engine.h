#pragma once

#undef CreateWindow

namespace Core
{
	enum class EngineState
	{
		INVALID,
		CONSTRUCTING,
		INITIALIZING,
		RUNNING,
		EXITING

	};

	class GameBase;

	class Engine : public Count<Engine>
	{
	public:
		Engine(GameBase* pGame);
		~Engine();

		int Initialize(const Settings::EngineSettings& settings);
		int Update();
		void Shutdown();


		void ChangeState(const EngineState& state, const std::string& message = "");

	private:

		int InitializeManagers(const Settings::EngineSettings& settings) const;

	private:
		EngineState m_State = EngineState::INVALID;
		GameBase* m_pGame = nullptr;
	};
}


