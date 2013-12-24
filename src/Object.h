#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "Model.h"
#include "ShaderProgram.h"

namespace ILEngine {

    class Object {
        Model       objModel;
        std::string objName;
        bool        hidden;
        GLuint      VBO; // Vertex Buffer Object
        GLuint      IBO; // Index Buffer Object
        GLuint      VAO; // Vertex Array Object

        GLuint      program_id;

        glm::mat4 ModelMatrix;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjMatrix;

    void   GenAndBindBuffers(void);
    void   useProgram(GLuint);
    void   stopProgram(void);
    GLuint getAttribute(GLuint, const char *);
    GLuint getUniform(GLuint, const char *);
    //void   populateModelBuffer(void);

    public:
        Object(std::string, bool, GLuint);
        ~Object();
        std::string getName();
        Model       getModel();
        bool        isHidden();

        void setModel(Model);

        void draw();
    };

}

#endif
