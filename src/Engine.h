#ifndef __ENGINE_H__
#define __ENGINE_H__

#define GLFW_INCLUDE_GL_3
#define WINDOW_TITLE "ILEngine"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "common.h"

#include "ShaderProgram.h"

#include "Camera.h"

namespace ILEngine {

    class Engine {
        int CurrentWidth;
        int CurrentHeight;

        Camera camera;

        glm::mat4 ViewMatrix;
        glm::mat4 ProjMatrix;

        ShaderProgram *gProg;
        GLFWwindow    *WindowHandle;

        GLFWwindow *InitWindow(int, int);

    public:
        Engine(int, int);

        glm::mat4 & view(void);
        glm::mat4 & proj(void);

        glm::mat4 & view(glm::vec3);
        glm::mat4 & proj(int, int);

        GLFWwindow *window(void);

        void   initEngine(void);
        void   clean(void);
        void   setDefaultProgram(std::vector<Shader>);
        GLuint getDefaultEngineProgram(void);
    };

}

#endif
