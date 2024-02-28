#pragma once
#include "TexturedCubeScene.h"

namespace Manurocker95
{
	class SceneManager
	{
	protected:
		std::shared_ptr<Scene> m_currentScene;
		size_t m_currentSceneID = -1;
		std::shared_ptr <PadState> m_pad;
		GLFWwindow* m_window;

	protected:
		SceneManager();
		~SceneManager();

		// Private Copy Constructor and Copy Assignment Operator
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

	public:
		static SceneManager& Instance();

	public:
		bool LoadScene(size_t _id);
		void Initialize(GLFWwindow * _window);
		void InitializeInputs();
		void EndScene();
		void FreeResources();
		void UpdateCurrentScene();
		bool NeedToUpdateScene();
	};
}