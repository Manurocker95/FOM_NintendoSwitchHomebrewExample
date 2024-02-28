#pragma once

#include "Shader.h"

namespace Manurocker95
{
	class VertexShader : public Shader
	{
	public:
		VertexShader(ShaderSourceCode& _src) : Shader(_src, GL_VERTEX_SHADER)
		{

		}

		VertexShader(const char* _filePath) : Shader(_filePath, GL_VERTEX_SHADER)
		{

		}
	};
}