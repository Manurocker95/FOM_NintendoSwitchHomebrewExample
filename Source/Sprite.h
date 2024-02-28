#pragma once
#include "Common.h"
#include "SceneObject.h"

namespace Manurocker95
{
	class Sprite : public SceneObject
	{
	protected:
		GLuint m_id;
		int m_numFrames;
		int m_sizePerFrameX;
		int m_sizePerFrameY;
		int m_currentFrame;
		int m_secondaryCounter;
		bool m_multipleFrames;

	public:
		Sprite();
		~Sprite();

		void Render(GLFWwindow* _window) override;
		void Update(double ticks) override;
		void Free() override;

		virtual void LoadSprite(const char* filename);

		virtual void SetNumFrames(int _value);
		virtual int GetNumFrames();
		virtual void SetFrameSize(int _value, bool _xAxis);
		virtual int GetFrameSize(bool _xAxis);
	};
}