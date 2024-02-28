#include "Sprite.h"

namespace Manurocker95
{
	Sprite::Sprite()
	{

	}

	Sprite::~Sprite()
	{

	}

	void Sprite::Render(GLFWwindow* window)
	{

	}

	void Sprite::Update(double ticks)
	{
		if (this->m_multipleFrames)
		{
			this->m_currentFrame = (int)(ticks / 200) % this->m_numFrames;
		}
	}

	void Sprite::Free()
	{

	}

	void Sprite::LoadSprite(const char* filename)
	{

	}

	void Sprite::SetNumFrames(int _value)
	{
		this->m_numFrames = _value;
		this->m_currentFrame = 0;
	}

	int Sprite::GetNumFrames()
	{
		return this->m_numFrames;
	}

	void Sprite::SetFrameSize(int _value, bool _xAxis)
	{
		if (_xAxis)
			this->m_sizePerFrameX = _value;
		else
			this->m_sizePerFrameY = _value;
	}

	int Sprite::GetFrameSize(bool _xAxis)
	{
		if (_xAxis)
			return this->m_sizePerFrameX;
		else
			return this->m_sizePerFrameY;
	}
}