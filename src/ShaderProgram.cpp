#include <vector>
#include <stdexcept>
#include <GL/glew.h>
#include <stdlib.h>

#include "Shader.h"
#include "ShaderProgram.h"
#include "Error.h"

namespace ILEngine {

ShaderProgram::ShaderProgram(std::vector<Shader> & shaders) {
    this->program_id = 0;

    if (shaders.size() == 0) {
        throw std::runtime_error("ERROR: No shaders were passed in.");
    }

    glGetError();
    this->program_id = glCreateProgram();
    if (!(this->program_id)) {
        ILEngine::Error::ExitOnGLError("ERROR: Could not create the shader program");
    }

    int i;
    for(i = 0; i < shaders.size(); i++) {
        Shader cur = shaders[i];
        GLuint s_id = LoadShader(cur.file().c_str(), cur.type());
        cur.setId(s_id);
        glAttachShader(this->program_id, s_id);
    }
    ILEngine::Error::ExitOnGLError("ERROR: Could not attach the shader program");

    glLinkProgram(this->program_id);
    ILEngine::Error::ExitOnGLError("ERROR: Could not link the shader program");

}

ShaderProgram::~ShaderProgram() {

    glGetError();
    this->detachAll();
    int i;
    for(i = 0; i < shader_ids.size(); i++) {
        glDeleteShader(shader_ids[i]);
    }
    ILEngine::Error::ExitOnGLError("ERROR: Could not delete the shaders");

    glGetError();
    if (this->program_id != 0) {
        fprintf(stderr, "%d\n", this->program_id);
        glDeleteProgram(this->program_id);
        this->program_id = 0;
    }
    ILEngine::Error::ExitOnGLError("ERROR: Could not delete the shader program");

}

GLuint ShaderProgram::programId() {
    return this->program_id;
}

void ShaderProgram::use() {
    glGetError();
    glUseProgram(this->program_id);
    ILEngine::Error::ExitOnGLError("ERROR: Could not use the shader program");
}

void ShaderProgram::stop() {
    glGetError();
    glUseProgram(0);
    ILEngine::Error::ExitOnGLError("ERROR: Could not stop the shader program");
}

GLuint ShaderProgram::uniform(const char *uniformName) {

    /* Check if name is valid */
    if (!uniformName) {
        throw std::runtime_error("ERROR: uniformName is NULL.");
    }

    glGetError();
    GLuint uni = glGetUniformLocation(this->program_id, uniformName);
    if (uni == -1) {
        ILEngine::Error::ExitOnGLError((std::string("Program uniform not found: ") + std::string(uniformName)).c_str());
    }

    return uni;
}

GLuint ShaderProgram::attribute(const char *attribName) {

    /* Check if name is valid */
    if (!attribName) {
        throw std::runtime_error("ERROR: attribName is NULL.");
    }

    glGetError();
    GLuint attrib = glGetAttribLocation(this->program_id, attribName);
    if (attrib == -1) {
        ILEngine::Error::ExitOnGLError((std::string("Program attribute not found: ") + std::string(attribName)).c_str());
    }

    return attrib;
}

void ShaderProgram::detachAll() {
    glGetError();

    int i;
    for(i = 0; i < shader_ids.size(); i++) {
        glDetachShader(this->program_id, shader_ids[i]);
    }
    ILEngine::Error::ExitOnGLError("ERROR: Could not detach the shader program");
}

GLuint ShaderProgram::LoadShader(const char* filename, GLenum shader_type) {
    GLuint shader_id = 0;
    FILE  *file;
    long  file_size = -1;
    char  *glsl_source;

    glGetError(); /* Clear Error */

    if (NULL != (file = fopen(filename, "rb")) &&
         0 == fseek(file, 0, SEEK_END) &&
        -1 != (file_size = ftell(file)))
    {
        rewind(file);

        if (NULL != (glsl_source = (char*)malloc(file_size + 1))) {
            if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file)) {
                glsl_source[file_size] = '\0';

                if (0 != (shader_id = glCreateShader(shader_type))) {
                    ILEngine::Error::ExitOnGLError("ERROR: Could not create a shader");
                    glShaderSource(shader_id, 1, (const GLchar **)&glsl_source, NULL);
                    ILEngine::Error::ExitOnGLError("ERROR: Could not source a shader");
                    glCompileShader(shader_id);
                    ILEngine::Error::ExitOnGLError("ERROR: Could not compile a shader");
                } else {
                    fprintf(stderr, "ERROR: Could not create a shader.\n");
                }
            } else {
                fprintf(stderr, "ERROR: Could not read file %s\n", filename);
            }

            free(glsl_source);
        } else {
            fprintf(stderr, "ERROR: Could not allocate %ld bytes.\n", file_size);
        }

        fclose(file);
    } else {
        fprintf(stderr, "ERROR: Could not open file %s\n", filename);
    }

    return shader_id;
}

}
