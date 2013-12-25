#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "Model.h"
#include "ShaderProgram.h"

namespace ILEngine {

    class Object {
        std::string objName;
        bool        hidden;
        GLuint      VBO; // Vertex Buffer Object
        //GLuint      IBO; // Index Buffer Object
        GLuint      VAO; // Vertex Array Object

        GLuint      program_id;

        unsigned int numFaces;
        std::vector<unsigned int> indices;
        std::vector<float>        vertices;

        glm::mat4 ModelMatrix;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjMatrix;

    void   GenAndBindBuffers(const aiScene *);
    void   useProgram(GLuint);
    void   stopProgram(void);
    GLuint getAttribute(GLuint, const char *);
    GLuint getUniform(GLuint, const char *);

    public:
        Object(std::string, std::string, bool, GLuint);
        ~Object();

        std::string getName();
        bool        isHidden();

        void draw();
    };

}

#endif
