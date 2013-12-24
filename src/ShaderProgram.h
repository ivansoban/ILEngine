#ifndef __SHADERPROG_H__
#define __SHADERPROG_H__

#include <vector>

#include "Shader.h"

namespace ILEngine {

    class ShaderProgram {
        GLuint program_id;
        std::vector<GLuint> shader_ids;

    public:
                      ShaderProgram(std::vector<Shader> &);
                     ~ShaderProgram();
               GLuint programId(void);
               void   use();
               void   stop();
               GLuint uniform(const char *);
               GLuint attribute(const char *);
               void   detachAll(void);
        static GLuint LoadShader(const char *, GLenum);
    };

}

#endif
