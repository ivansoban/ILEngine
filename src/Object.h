#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "ShaderProgram.h"

namespace ILEngine {

    class Object {
        std::string objName;
        bool        hidden;

        GLuint      VBO; // Vertex Buffer Object
        GLuint      IBO; // Index Buffer Object
        GLuint      VAO; // Vertex Array Object
        GLuint      NBO; // Normal Buffer Object
        GLuint      TBO; // Texture Buffer Object

        GLuint      program_id;
        GLuint      texture_id;

        unsigned int numFaces;
        std::vector<unsigned int> indices;
        std::vector<float>        vertices;
        std::vector<float>        normals;
        std::vector<float>        UVcoord;

        glm::mat4 ModelMatrix;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjMatrix;

    void   GenAndBindBuffers(const aiScene *);
    void   LoadTextures(const aiScene *);
    void   useProgram(GLuint);
    void   stopProgram(void);
    GLint  getAttribute(GLuint, const char *);
    GLint  getUniform(GLuint, const char *);

    public:
        Object(std::string, std::string, bool, GLuint);
        ~Object();

        std::string getName();
        bool        isHidden();

        void draw();
    };

}

#endif
