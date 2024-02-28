#include "Shader.h"

namespace Manurocker95
{
    Shader::Shader(const char* _file, GLenum _type)
    {
        auto src = ShaderSourceCode::FromFile(_file);
        m_compiled = LoadShaderFromCode(src, _type);
    }

    Shader::Shader(ShaderSourceCode& _sourceCode, GLenum _type) : m_shaderObjectID(0)
    {
        m_compiled = LoadShaderFromCode(_sourceCode, _type);
    }

    Shader::~Shader()
    {
        // Borrar un shader cuando se ha añadido a un shader program no tiene efectos adversos:

        glDeleteShader(m_shaderObjectID);

        m_shaderObjectID = 0;
    }

	bool Shader::IsCompiled()
	{
		return m_shaderObjectID != 0;
	}

	std::string Shader::GetLog()
	{
		return m_log;
	}	
	
	const char * Shader::GetLogAsChar()
	{
		return m_log.c_str();
	}

	GLuint Shader::GetID()
	{
		return m_shaderObjectID;
	}

    bool Shader::LoadShaderFromCode(ShaderSourceCode & _sourceCode, GLenum _type)
    {
        if (_sourceCode.IsNotEmpty())
        {
            // Se crea el shader object:

            m_shaderObjectID = glCreateShader(_type);

            // Se carga el código del shader:

            const char* shaderCodeList[] = { _sourceCode.GetSourceAsChar() };
            const GLint  shaderSizeList[] = { (GLint)_sourceCode.Size() };

            glShaderSource(m_shaderObjectID, 1, shaderCodeList, shaderSizeList);

            // Se compila el shader:

            glCompileShader(m_shaderObjectID);

            // Se comprueba si la compilación ha tenido éxito:

            GLint succeeded = 0;

            glGetShaderiv(m_shaderObjectID, GL_COMPILE_STATUS, &succeeded);

            if (!succeeded)
            {
                // Se guarda el log del error que ha ocurrido:

                GLint log_length;

                glGetShaderiv(m_shaderObjectID, GL_INFO_LOG_LENGTH, &log_length);

                if (log_length > 0)
                {
                    m_log.resize(log_length);

                    glGetShaderInfoLog(m_shaderObjectID, log_length, NULL, &m_log.front());
                }

                // Se libera el shader object, ya que ahora es un recurso encapsulado no usable:

                glDeleteShader(m_shaderObjectID);

                m_shaderObjectID = 0;
                return false;
            }

            return true;
        }

        return false;
    }
}