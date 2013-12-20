#include <vector>
#include <stdexcept>
#include <GL/glew.h>
#include <stdlib.h>

#include "ShaderProgram.h"

GLuint ShaderProgram::LoadShader(const char* filename, GLenum shader_type) {
    GLuint shader_id = 0;
    FILE  *file;
    long  file_size = -1;
    char  *glsl_source;

    if (NULL != (file = fopen(filename, "rb")) &&
         0 == fseek(file, 0, SEEK_END) &&
        -1 != (file_size = ftell(file)))
    {
        rewind(file);

        if (NULL != (glsl_source = (char*)malloc(file_size + 1))) {
            if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file)) {
                glsl_source[file_size] = '\0';

                if (0 != (shader_id = glCreateShader(shader_type))) {
                    glShaderSource(shader_id, 1, (const GLchar **)&glsl_source, NULL);
                    glCompileShader(shader_id);
                    // TODO: ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    //ExitOnGLError("Could not compile a shader");
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

ShaderProgram::ShaderProgram(std::vector<Shader> & shaders) {
    program_id = 0;

    if (shaders.size() == 0) {
        throw std::runtime_error("ERROR: No shaders were passed in.");
    }

    program_id = glCreateProgram();
    if (!program_id) {
        throw std::runtime_error("ERROR: Could not create the shader program");
    }
    /* TODO: Add error check callback */
    /* ExitOnGLError("ERROR: Could not create the shader program"); */

    int i;
    for(i = 0; i < shaders.size(); i++) {
        Shader cur = shaders[i];
        GLuint s_id = LoadShader(cur.file().c_str(), cur.type());
        cur.setId(s_id);
        glAttachShader(program_id, s_id);
    }

    glLinkProgram(program_id);

    GLint status;
    glGetProgramiv(program_id, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        throw std::runtime_error("ERROR: Could not link shaders.");
    }
    /* ExitOnGLError("ERROR: Could not link the shader program"); */

    /* Here some implem. detach? Not sure why. Look into that. */
}

GLuint ShaderProgram::uniform(const char *uniformName) {

    /* Check if name is valid */
    if (!uniformName) {
        throw std::runtime_error("ERROR: uniformName is NULL.");
    }

    GLuint uniform = glGetUniformLocation(program_id, uniformName);
    if (uniform == -1) {
        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);
    }
    /* ExitOnGLError("ERROR: Could not get shader uniform locations"); */

    return uniform;
}
