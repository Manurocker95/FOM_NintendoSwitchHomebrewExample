#include "TexturedCubeScene.h"
#include "stb_image.h"
#include "Cube.h"

namespace Manurocker95
{
	TexturedCubeScene::TexturedCubeScene()
	{
	
	}

	TexturedCubeScene::~TexturedCubeScene()
	{
		
	}

	bool TexturedCubeScene::Initialize(GLFWwindow* _window)
	{
		if (!Scene::Initialize(_window))
			return false;

        m_id = "Textured Cube Scene";

		bool initShaders = InitializeShaders();
		if (!initShaders)
		{
			return false;
		}

		ConfigureDepthTest();

		ConfigureVertexData();
		ConfigureTextureData();

		SetUniformVariablesValues();

        DebugLog(m_id, true);

        return true;
	}

	void TexturedCubeScene::Update()
	{
        auto dt = GetElapsedTime();

        glm::mat4 mdlvMtx{ 1.0 };
        float mv = (float)(m_rotationSpeed * dt * TAU) * 0.234375f;
        mdlvMtx = glm::translate(mdlvMtx, glm::vec3{ 0.0f, 0.0f, -3.0f });
        mdlvMtx = glm::rotate(mdlvMtx, mv, glm::vec3{ 1.0f, 0.0f, 0.0f });
        mdlvMtx = glm::rotate(mdlvMtx, mv * 0.5f, glm::vec3{ 0.0f, 1.0f, 0.0f });

        glUniformMatrix4fv(m_uModelID, 1, GL_FALSE, glm::value_ptr(mdlvMtx));
	}

	void TexturedCubeScene::HandleInputs(PadState * pad)
	{
		Scene::HandleInputs(pad);

        // hidKeysDown returns information about which buttons have been
        // just pressed in this frame compared to the previous one
        u64 kDown = padGetButtonsDown(pad);

        if (kDown & HidNpadButton_A)
        {
            DebugLog("Pressed A button! Adding velocity!\n");
            m_rotationSpeed += 0.1;
        }

        if (kDown & HidNpadButton_B)
        {
            DebugLog("Pressed B button! Reducing velocity!\n");
            m_rotationSpeed -= 0.1;
        }

        if (kDown & HidNpadButton_X)
        {
            DebugLog("Pressed X button!\n");
            m_saveStrings = !m_saveStrings;
        }

        if (kDown & HidNpadButton_Plus || IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(m_window, true);
        }

        /* Poll for and process events */
        glfwPollEvents();
	}

	void TexturedCubeScene::Render()
	{
        glClearColor(0x68 / 255.0f, 0xB0 / 255.0f, 0xD8 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our textured cube
        glBindVertexArray(m_vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, (sizeof(m_cubeVertices) / sizeof(m_cubeVertices[0])));
	}

	void TexturedCubeScene::FreeResources()
	{
        glDeleteTextures(1, &m_texUnit0);
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
        glDeleteProgram(m_programID);
	}

	GLuint TexturedCubeScene::LoadShader(const char* _fileName, GLenum _type)
	{
        /* We load the shader */
        std::ifstream file;
        file.open(_fileName, std::ios::in);

        if (!file)
        {
            DebugLog("\nShader file not found " + std::string(_fileName) + "\n");
            return 0;
        }

        file.seekg(0, std::ios::end);
        unsigned int fileLen = file.tellg();
        file.seekg(std::ios::beg);

        char* source = new char[fileLen + 1];
        int i = 0;

        while (file.good())
        {
            source[i] = file.get();
            if (!file.eof()) i++;
            else fileLen = i;
        }
        source[fileLen] = '\0';
        file.close();

        // Creation and compilation of the shaders
        GLuint shader;
        shader = glCreateShader(_type);
        glShaderSource(shader, 1, (const GLchar**)&source, (const GLint*)&fileLen);
        glCompileShader(shader);
        delete[] source;

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled)
        {
            GLint logLen;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
            char* logString = new char[logLen];
            glGetShaderInfoLog(shader, logLen, NULL, logString);
            DebugLog("Error: " + std::string(logString));
            delete[] logString;
            glDeleteShader(shader);
            return 0;
        }
        return shader;
	}

    bool TexturedCubeScene::InitializeShaders()
    {
        //We compile our vertex and fragment shaders
        m_vertexShaderID = LoadShader(RESOURCES_PATH("Graphics/Shaders/vshader.glsl"), GL_VERTEX_SHADER);
        m_fragmentShaderID = LoadShader(RESOURCES_PATH("Graphics/Shaders/fshader.glsl"), GL_FRAGMENT_SHADER);

        if (m_vertexShaderID == 0 || m_fragmentShaderID == 0)
        {
            DebugLog(std::string("Shaders not loaded: v=" + m_vertexShaderID) + std::string(" f=" + m_fragmentShaderID));
            return false;
        }

        // Create Program
        m_programID = glCreateProgram();

        // Attach shaders to program render pipeline
        glAttachShader(m_programID, m_vertexShaderID);
        glAttachShader(m_programID, m_fragmentShaderID);

        //Link shaders to our program
        glLinkProgram(m_programID);

        //Error debugging
        int linked;
        glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);

        if (!linked)
        {
            // Error msg length
            GLint logLen;
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLen);
            char* logString = new char[logLen];
            glGetProgramInfoLog(m_programID, logLen, NULL, logString);
            DebugLog(std::string("Shader error: ") + std::string(logString));
            delete[] logString;
            glDeleteProgram(m_programID);
            m_programID = 0;
            return false;
        }

        //uniform variables
        m_uModelID = glGetUniformLocation(m_programID, "modelMatrix");
        m_uProjectionID = glGetUniformLocation(m_programID, "projectionMatrix");
        m_uLightPosID = glGetUniformLocation(m_programID, "lightPos");
        m_uAmbientID = glGetUniformLocation(m_programID, "ambient");
        m_uDiffuseID = glGetUniformLocation(m_programID, "diffuse");
        m_uSpecularID = glGetUniformLocation(m_programID, "specular");
        m_uColorMapID = glGetUniformLocation(m_programID, "colorMap");

        // Attributes
        m_inVertexID = glGetAttribLocation(m_programID, "inPos");
        m_inTexCoordsID = glGetAttribLocation(m_programID, "inTexCoord");
        m_inNormalsID = glGetAttribLocation(m_programID, "inNormal");

        return true;
    }

    void TexturedCubeScene::SetUniformVariablesValues()
    {
        glUseProgram(m_programID);
        auto projection = glm::perspective(60.0f * (float)TAU / 360.0f, 1280.0f / 720.0f, 0.01f, 1000.0f);
        glUniformMatrix4fv(m_uProjectionID, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform4f(m_uLightPosID, 0.0f, 0.0f, 0.5f, 1.0f);
        glUniform3f(m_uAmbientID, 0.1f, 0.1f, 0.1f);
        glUniform3f(m_uDiffuseID, 0.4f, 0.4f, 0.4f);
        glUniform4f(m_uSpecularID, 0.5f, 0.5f, 0.5f, 20.0f);
        glUniform1i(m_uColorMapID, 0);
    }

    void TexturedCubeScene::ConfigureDepthTest()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void TexturedCubeScene::ConfigureVertexData()
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_cubeVertices), m_cubeVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);


        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    void TexturedCubeScene::ConfigureTextureData()
    {
        // Textures
        glGenTextures(1, &m_texUnit0);
        glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, m_texUnit0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nchan;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* img = stbi_load(RESOURCES_PATH("Graphics/Textures/colorMap.png"), &width, &height, &nchan, STBI_rgb_alpha);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
        stbi_image_free(img);

    }
}