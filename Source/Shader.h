#pragma once
#include "ShaderSourceCode.h"
#include "glad.h"

namespace Manurocker95
{
	class Shader
	{
	protected:
		GLuint m_shaderObjectID;
		std::string m_log;
		bool m_compiled;
	protected:
		Shader(const char * file, GLenum _type);
		Shader(ShaderSourceCode& code, GLenum _type);
		~Shader();

	public:
		bool LoadShaderFromCode(ShaderSourceCode& _sourceCode, GLenum _type);
		bool IsCompiled();
		std::string GetLog();
		const char * GetLogAsChar();
		GLuint GetID();
	};
}