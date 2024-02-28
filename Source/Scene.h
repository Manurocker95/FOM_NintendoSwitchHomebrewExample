#pragma once

#include "Sprite.h"

namespace Manurocker95
{
	class Scene
	{
	protected:
		GLFWwindow* m_window;
		double m_startTicks;
		std::string m_id;
		bool m_saveStrings = false;
	public:
		Scene();
		~Scene();
		virtual std::string GetID();
		virtual bool Initialize(GLFWwindow* _window);
		virtual bool IsApplicationRunning();
		virtual void Update();
		virtual void Render();
		virtual double GetElapsedTime();
		virtual double GetTick();
		virtual bool IsKeyPressed(int key);
		virtual void HandleInputs(PadState * pad);
		virtual void FreeResources();
		virtual void EndScene();
		virtual void SaveString(std::string _str);
		virtual void DebugLog(std::string _str, bool _saveStrings = false);
	};
}