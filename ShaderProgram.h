#include "Shader.h"

class ShaderProgram {
    GLuint program_id;
    std::vector<GLuint> shader_ids;

public:
                  ShaderProgram(std::vector<Shader> &);
           GLuint uniform(const char *);
    static GLuint LoadShader(const char *, GLenum);
};
