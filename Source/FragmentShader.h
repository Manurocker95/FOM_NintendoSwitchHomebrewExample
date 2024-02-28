#pragma once

#include "Shader.h"

namespace Manurocker95
{
	class FragmentShader : public Shader
	{
	public:
		FragmentShader(ShaderSourceCode& _src) : Shader(_src, GL_FRAGMENT_SHADER)
		{

		}

		FragmentShader(const char* _filePath) : Shader(_filePath, GL_FRAGMENT_SHADER)
		{

		}
	};
}