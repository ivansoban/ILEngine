#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>

namespace ILEngine {

    class Object {

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

        void   GenAndBindBuffers(const aiScene *);
        void   LoadTextures(const aiScene *);
        void   useProgram(GLuint);
        void   stopProgram(void);
        GLint  getAttribute(GLuint, const char *);
        GLint  getUniform(GLuint, const char *);

    protected:
        std::string objName;
        bool        hidden;
        std::string meshFile;

        glm::mat4  ModelMatrix;
        glm::mat4 &ViewMatrix;
        glm::mat4 &ProjMatrix;

        glm::vec3 location;

    public:
        Object(std::string, std::string, bool, GLuint, glm::vec3, glm::mat4 &, glm::mat4 &);
        ~Object();

        void init(GLuint);

        std::string getName();
        bool        isHidden();
        glm::vec3   getLocation();
        void        setLocation(glm::vec3);

        virtual void draw();
    };

}

#endif
