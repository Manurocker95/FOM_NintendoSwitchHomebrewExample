#include "SceneManager.h"

constexpr uint32_t WINDOW_WIDTH = 1280;
constexpr uint32_t WINDOW_HEIGHT = 720;
constexpr const char* WINDOW_TITLE = "Hello World";



bool InitializeOpenGLLibrary()
{
    return glfwInit();
}

bool InitializeGLExtensionLibrary()
{
    // Load OpenGL routines using glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    return true;
}

void WindowRescaling(GLFWwindow* _window, GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    // BuildProjectionMatrix(40.0f, w / h, 0.1f, 1000.0f);
}

GLFWwindow* InitWindowContext(const char* _title, int _width, int _height)
{
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    if (!_window)
    {
        return NULL;
    }

    /* Make the window's context current */
    // Configure window
    glfwSwapInterval(1);
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GLFW_TRUE);

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);
    glfwSetFramebufferSizeCallback(_window, WindowRescaling);

    return _window;
}


void FreeOpenGLLibraries()
{
    glfwTerminate();
}

void SwapBuffers(GLFWwindow* _window)
{
    glfwSwapBuffers(_window);
}

void SaveString(std::string _str)
{
    std::ofstream outfile;
    outfile.open("sdmc:/sav.txt", std::ios_base::app);
    outfile << _str;
    outfile.close();
}

void DebugLog(std::string _str, bool _saveStrings)
{
    if (_saveStrings)
        SaveString(_str);

    TRACE(_str);
}

void DebugOpenGLInfo()
{
    std::string strVendor = (const char*)glGetString(GL_VENDOR);
    std::string strRender = (const char*)glGetString(GL_RENDERER);
    std::string strVersion = (const char*)glGetString(GL_VERSION);

    DebugLog(std::string("GL Vendor: ") + strVendor + "\n", true);
    DebugLog(std::string("GL Renderer: ") + strRender + "\n", true);
    DebugLog(std::string("GL Version: ") + strVersion + "\n", true);
}


int main(int argc, char* argv[])
{
    Result rc = romfsInit();
    if (R_FAILED(rc))
        printf("romfsInit: %08X\n", rc);

    // Initialize GLFW (OpenGL library)
    if (!InitializeOpenGLLibrary())
    {
        DebugLog("GLFW couldn't be initialized!\n", true);
        return EXIT_FAILURE;
    }

    GLFWwindow* window = InitWindowContext("Hello World", 1280, 720);

    if (window == NULL)
    {
        DebugLog("GLFW: failed to create window!\n", true);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Initialize OpenGL Extensions (GLEW)
    if (!InitializeGLExtensionLibrary())
    {
        DebugLog("Extensions couldn't be initialized!\n", true);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    Manurocker95::SceneManager * sceneManager = &Manurocker95::SceneManager::Instance();

    sceneManager->Initialize(window);

    DebugOpenGLInfo();

    if (!sceneManager->LoadScene(0))
    {
        DebugLog("The scene couldn't be initialized!\n", true);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    while (sceneManager->NeedToUpdateScene())
    {
        sceneManager->UpdateCurrentScene();

        /* Swap front and back buffers */
        SwapBuffers(window);
    }

    sceneManager->FreeResources();

    FreeOpenGLLibraries();

    return EXIT_SUCCESS;
}