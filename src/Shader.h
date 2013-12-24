#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/gl.h>
#include <string>

namespace ILEngine {

    class Shader {
        std::string filepath;
        GLenum      shadertype;
        GLuint      id;

    public:
                    Shader(std::string, GLenum);
        std::string file(void);
        GLenum      type(void);
        GLuint      getId(void);
        void        setId(GLuint);
    };

}

#endif
