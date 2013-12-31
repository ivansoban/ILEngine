#define GLFW_INCLUDE_GL_3
#define WINDOW_TITLE "ILEngine"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Engine.h"
#include "Scene.h"
#include "ShaderProgram.h"
#include "Error.h"

ILEngine::Engine *engine = NULL;

void MainLoop(void);

int main(int argc, char *argv[]) {
    engine = new ILEngine::Engine(800, 600);
    engine->initEngine();

    /* Create Shaders */
    ILEngine::Shader vert("../src/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
    ILEngine::Shader frag("../src/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);

    std::vector<ILEngine::Shader> shaders;
    shaders.push_back(vert);
    shaders.push_back(frag);

    engine->setDefaultProgram(shaders);

    MainLoop();

    engine->clean();
}


void MainLoop() {
    ILEngine::Scene mainScene(std::string("main"), engine->getDefaultEngineProgram());

    ILEngine::Object o1("../test/cube/cube.obj",
            "test", true, -1,
            glm::vec3(-2, -2, -2.5),
            engine->view(glm::vec3(-2, -2, -2.5)),
            engine->proj());
    ILEngine::Object o2("../test/cube/cube.obj",
            "test", true, -1,
            glm::vec3(-2, -2, -3),
            engine->view(),
            engine->proj());

    mainScene.addObject(o1);
    mainScene.addObject(o2);
/*
    ILEngine::LightSource l("", "MainLight", -1, glm::vec3(0.0f, 0.0f, 3.0f), 100.0f);
    mainScene.addLight(l);
*/
    mainScene.init();

    while(!glfwWindowShouldClose(engine->window())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainScene.renderScene();

        glfwSwapBuffers(engine->window());
        glfwPollEvents();
    }

}


