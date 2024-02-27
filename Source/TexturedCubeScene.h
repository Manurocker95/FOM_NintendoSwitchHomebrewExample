#pragma once
#include "Scene.h"

#include "stb_image.h"
#include "Cube.h"

namespace Manurocker95
{
	class TexturedCubeScene : public Scene
	{
	private:
		// -----------------------------------------------------------------
		// * Shaders
		// -----------------------------------------------------------------
		GLuint m_vertexShaderID = 0;
		GLuint m_fragmentShaderID = 0;
		GLuint m_programID = 0;

		// -----------------------------------------------------------------
		// * Uniform Variables
		// -----------------------------------------------------------------
		GLint m_uModelID = -1;
		GLint m_uProjectionID = -1;

		GLint m_uLightPosID = -1;
		GLint m_uAmbientID = -1;
		GLint m_uDiffuseID = -1;
		GLint m_uSpecularID = -1;
		GLint m_uColorMapID;

		// -----------------------------------------------------------------
		// * Attribute Variables
		// -----------------------------------------------------------------
		GLint m_inVertexID = -1;
		GLint m_inTexCoordsID = -1;
		GLint m_inNormalsID = -1;

		// -----------------------------------------------------------------
		// * Buffers
		// -----------------------------------------------------------------
		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_texUnit0;

		// -----------------------------------------------------------------
		// * Others
		// -----------------------------------------------------------------
		double m_startTicks;//u64 m_startTicks;
		double m_rotationSpeed = 0.1;


	public:
		TexturedCubeScene();
		~TexturedCubeScene();

		bool Initialize(GLFWwindow* _window) override;
		void Update() override;
		void Render() override;
		void HandleInputs(PadState * pad) override;
		void FreeResources() override;

	protected:
		GLuint LoadShader(const char* _fileName, GLenum _type);
		bool InitializeShaders();
		void ConfigureDepthTest();
		void ConfigureVertexData();
		void ConfigureTextureData();
		void SetUniformVariablesValues();
	};
}