#include <glm/gtc/matrix_transform.hpp>

#include "Error.h"
#include "Engine.h"

namespace ILEngine {

Engine::Engine(int CurrentWidth, int CurrentHeight)
: camera(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)), ViewMatrix(1.0f), ProjMatrix(1.0f)
{
    this->CurrentWidth  = CurrentWidth;
    this->CurrentHeight = CurrentHeight;

    this->ViewMatrix = this->view(glm::vec3(-1, -1, -1));
    this->ProjMatrix = this->proj(CurrentWidth, CurrentHeight);
}

glm::mat4 & Engine::view() {
    return this->ViewMatrix;
}

glm::mat4 & Engine::proj() {
    return this->ProjMatrix;
}

glm::mat4 & Engine::view(glm::vec3 look) {
    return (this->ViewMatrix = this->camera.lookAt(look));
}

glm::mat4 & Engine::proj(int CurrentWidth, int CurrentHeight) {
    return (this->ProjMatrix =  glm::perspective(
        60.0f,
        (float)CurrentWidth / CurrentHeight,
        1.0f,
        100.0f
    ));
}

GLFWwindow * Engine::InitWindow(int w, int h) {
    GLFWwindow* window;

    window = glfwCreateWindow(w, h, WINDOW_TITLE, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;
}

GLFWwindow * Engine::window() {
    return this->WindowHandle;
}

void Engine::initEngine() {

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    /*
     * This wierd shit below is needed? Apple . . .
     * Request 3.3 and get 4.1. Whatever, better
     * than 2.1.
     * */

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    WindowHandle = InitWindow(CurrentWidth, CurrentHeight);

    glfwMakeContextCurrent(WindowHandle);
    //glfwSetErrorCallback(error_callback);
    //glfwSetWindowSizeCallback(WindowHandle, window_size_callback);
    //glfwSetKeyCallback(WindowHandle, key_callback);

    /*
     * Important GLEW init. Needs to be done after context creation.
     * */
    glewExperimental = true; // Need for core profile.
    if(glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }


    fprintf(
        stdout,
        "INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
    );

    glGetError();
    glClearColor(255.0f, 255.0f, 255.0f, 255.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    Error::ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

    glGetError();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    Error::ExitOnGLError("ERROR: Could not set OpenGL culling options");
}

void Engine::clean() {
    delete gProg;
    glfwDestroyWindow(WindowHandle);
    glfwTerminate();
}

void Engine::setDefaultProgram(std::vector<Shader> shaders) {
    this->gProg = new ShaderProgram(shaders);
}

GLuint Engine::getDefaultEngineProgram() {
    return this->gProg->programId();
}

}
