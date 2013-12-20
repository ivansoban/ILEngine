#define GLFW_INCLUDE_GL_3

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int CurrentWidth = 800,
    CurrentHeight = 600;

ShaderProgram gProg;
GLuint gVBO, gVAO;
