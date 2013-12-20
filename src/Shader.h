#include <GL/gl.h>
#include <string>

class Shader {
    std::string filepath;
    GLenum      shadertype;
    GLuint      id;

public:
                Shader(std::string, GLenum);
    std::string file(void);
    GLenum      type(void);
    void        setId(GLuint);
};
