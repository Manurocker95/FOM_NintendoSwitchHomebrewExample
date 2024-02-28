#include "SceneManager.h"

namespace Manurocker95
{
	SceneManager::SceneManager()
	{
	
	}

	SceneManager::~SceneManager()
	{

	}

	SceneManager& SceneManager::Instance()
	{
		static SceneManager m_instance; // Guaranteed to be destroyed and instantiated on first use.
		return m_instance;
	}

	bool SceneManager::LoadScene(size_t _id)
	{
		if (m_currentSceneID == _id && m_currentScene)
			return false;

		if (_id == 0)
		{
			std::shared_ptr<TexturedCubeScene> scene = std::make_shared<TexturedCubeScene>();
			if (!scene->Initialize(m_window))
				return false;
			
			EndScene();

			m_currentScene = scene;
		}

		m_currentSceneID = _id;
		return true;
	}

	bool SceneManager::NeedToUpdateScene()
	{
		return !m_currentScene || m_currentScene->IsApplicationRunning();
	}

	void SceneManager::Initialize(GLFWwindow* _window)
	{
		m_currentSceneID = -1;
		m_window = _window;

		InitializeInputs();
	}

	void SceneManager::InitializeInputs()
	{
		m_pad = std::make_shared<PadState>();

		// Configure our supported input layout: a single player with standard controller styles
		padConfigureInput(1, HidNpadStyleSet_NpadStandard);
		padInitializeDefault(m_pad.get());
	}

	void SceneManager::UpdateCurrentScene()
	{
		if (!m_currentScene)
			return;

		// Update the scene
		m_currentScene->Update();

		// Render the scene
		m_currentScene->Render();

		// Manage key inputs
		m_currentScene->HandleInputs(m_pad.get());
	}

	void SceneManager::EndScene()
	{
		if (m_currentScene)
		{
			m_currentScene->EndScene();
		}
	}

	// Cleanup: Destroy the window
	void SceneManager::FreeResources()
	{
		glfwDestroyWindow(m_window);
	}
}
