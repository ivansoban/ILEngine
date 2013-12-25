#define GLFW_INCLUDE_GL_3
#define WINDOW_TITLE "ILEngine"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Scene.h"
#include "ShaderProgram.h"
#include "ModelLoader.h"
#include "Error.h"

/* Globals */

int CurrentWidth = 800,
    CurrentHeight = 600;

ILEngine::ShaderProgram *gProg = NULL; /* Default shaderProgram */

GLFWwindow *WindowHandle = NULL;

/* Engine Functions */

GLFWwindow *InitWindow(int, int);
void Init(void);
void MainLoop(void);
void Clean(void);

/* Functions begin */

int main(int argc, char *argv[]) {
    Init();

    /* Create Shaders */
    ILEngine::Shader vert("../src/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
    ILEngine::Shader frag("../src/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);

    std::vector<ILEngine::Shader> shaders;
    shaders.push_back(vert);
    shaders.push_back(frag);

    /* Create Program */
    gProg = new ILEngine::ShaderProgram(shaders);

    MainLoop();
    Clean();
}

void Init() {

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
    ILEngine::Error::ExitOnGLError("ERROR: Could not set OpenGL depth testing options");

    glGetError();
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    ILEngine::Error::ExitOnGLError("ERROR: Could not set OpenGL culling options");
}

GLFWwindow *InitWindow(int w, int h) {
    GLFWwindow* window;

    window = glfwCreateWindow(w, h, WINDOW_TITLE, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    return window;
}

void MainLoop() {

    std::vector<ILEngine::Object> objects;

    ILEngine::Object o("../test/untitled.obj", "test", true, gProg->programId());
    objects.push_back(o);

    ILEngine::Scene mainScene(std::string("main"), objects);

    while(!glfwWindowShouldClose(WindowHandle)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainScene.renderScene();

        glfwSwapBuffers(WindowHandle);
        glfwPollEvents();
    }

}

void Clean() {
    delete gProg;
    glfwDestroyWindow(WindowHandle);
    glfwTerminate();
}
