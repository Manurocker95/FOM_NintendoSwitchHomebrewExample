#include "Scene.h"

namespace Manurocker95
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	std::string Scene::GetID() { return m_id; }

	bool Scene::Initialize(GLFWwindow* _window)
	{
		m_id = "Default Scene";

		if (!_window)
			return false;

		m_window = _window;
		m_startTicks = GetTick();

		return true;
	}

	void Scene::HandleInputs(PadState * pad)
	{
		// Scan all the inputs. This should be done once for each frame
		padUpdate(pad);

	}
	
	void Scene::Update()
	{

	}

	void Scene::EndScene()
	{
		glfwSetWindowShouldClose(m_window, true);
	}

	bool Scene::IsKeyPressed(int key)
	{
		if (!m_window) 
			return false;

		return (glfwGetKey(m_window, key) == GLFW_PRESS);
	}

	bool Scene::IsApplicationRunning()
	{
		return !glfwWindowShouldClose(m_window);
	}

	void Scene::Render()
	{

	}

	void Scene::FreeResources()
	{
	
	}

	double Scene::GetElapsedTime()
	{
		return GetTick() - m_startTicks;
	}

	double Scene::GetTick()
	{
		return glfwGetTime();
	}

	void Scene::SaveString(std::string _str)
	{
		std::ofstream outfile;
		outfile.open("sdmc:/sav.txt", std::ios_base::app);
		outfile << _str;
		outfile.close();
	}

	void Scene::DebugLog(std::string _str, bool _saveStrings)
	{
		if (_saveStrings)
			SaveString(_str);

		TRACE(_str);
	}
}