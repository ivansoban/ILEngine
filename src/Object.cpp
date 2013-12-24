#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

#include "Object.h"
#include "Error.h"

namespace ILEngine {

float CubeRotation = 0;
clock_t LastTime = 0;

void Object::useProgram(GLuint id) {
    glGetError();
    glUseProgram(id);
    ILEngine::Error::ExitOnGLError("ERROR: Could not use program.");
}

void Object::stopProgram() {
    glGetError();
    glUseProgram(0);
    ILEngine::Error::ExitOnGLError("ERROR: Could not stop program.");
}

GLuint Object::getAttribute(GLuint id, const char *aName) {
    /* Check if name is valid */
    if (!aName) {
        throw std::runtime_error("ERROR: aName is NULL.");
    }

    glGetError();
    GLuint attrib = glGetAttribLocation(id, aName);
    if (attrib == -1) {
        ILEngine::Error::ExitOnGLError((std::string("Program attribute not found: ") + std::string(aName)).c_str());
    }

    return attrib;
}

GLuint Object::getUniform(GLuint id, const char *uName) {
    /* Check if name is valid */
    if (!uName) {
        throw std::runtime_error("ERROR: uName is NULL.");
    }

    glGetError();
    GLuint uni = glGetUniformLocation(id, uName);
    if (uni == -1) {
        ILEngine::Error::ExitOnGLError((std::string("Program uniform not found: ") + std::string(uName)).c_str());
    }

    return uni;
}


Object::Object(std::string name, bool visibility, GLuint prog_id) : ModelMatrix(1.0f), ViewMatrix(1.0f), ProjMatrix(1.0f) {
    this->objName = name;
    this->hidden = visibility;
    this->program_id = prog_id;
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.0f, 0.0f, -4));
}

Object::~Object() {

    // TODO: Delete globally! (Manager?)
    //glDeleteBuffers(1, &(this->VBO));
    //glDeleteBuffers(1, &(this->IBO));
    //glDeleteVertexArrays(1, &(this->VAO));

}

std::string Object::getName() {
    return this->objName;
}

Model Object::getModel() {
    return this->objModel;
}

bool Object::isHidden() {
    return this->hidden;
}

void Object::setModel(Model m) {
    this->objModel = m;
    this->GenAndBindBuffers();
}

void Object::draw() {
    clock_t Now = clock();

    if (LastTime == 0)
        LastTime = Now;

    CubeRotation += 360.0f * ((float)(Now - LastTime) / CLOCKS_PER_SEC);
    LastTime = Now;

    ModelMatrix = glm::rotate(glm::mat4(1.0f), CubeRotation, glm::vec3(1.0f, 1.0f, 0.0f));

    glGetError();
    ProjMatrix = glm::perspective(60.0f, (float)800 / 600, 1.0f, 100.0f);

    this->useProgram(this->program_id);
    glUniformMatrix4fv(this->getUniform(this->program_id, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjMatrix));
    glUniformMatrix4fv(this->getUniform(this->program_id, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    glUniformMatrix4fv(this->getUniform(this->program_id, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    Error::ExitOnGLError("ERROR: Could not set the shader uniforms");

    glBindVertexArray(this->VAO);
    Error::ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

    glDrawElements(GL_TRIANGLES, this->objModel.vertices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
    Error::ExitOnGLError("ERROR: Could not draw the cube");

    glBindVertexArray(0);
    this->stopProgram();
}

void Object::GenAndBindBuffers() {
    glGetError();

    Vertex *t = this->objModel.vertices.data();

    glGenVertexArrays(1, &(this->VAO));
    ILEngine::Error::ExitOnGLError("ERROR: Could not generate the VAO");
    glBindVertexArray(this->VAO);
    ILEngine::Error::ExitOnGLError("ERROR: Could not bind the VAO");

    useProgram(this->program_id);
    glEnableVertexAttribArray(getAttribute(this->program_id, "vert"));
    glEnableVertexAttribArray(getAttribute(this->program_id, "color"));
    ILEngine::Error::ExitOnGLError("ERROR: Could not enable vertex attributes");

    glGenBuffers(1, &(this->VBO));
    ILEngine::Error::ExitOnGLError("ERROR: Could not generate the buffer objects");

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 this->objModel.vertices.size() * sizeof(Vertex),
                 this->objModel.vertices.data(),
                 GL_STATIC_DRAW);
    ILEngine::Error::ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

    glVertexAttribPointer(getAttribute(this->program_id, "vert"), 4,
                          GL_FLOAT, GL_FALSE,
                          sizeof(this->objModel.vertices[0]),
                          (GLvoid*)0);
    glVertexAttribPointer(getAttribute(this->program_id, "color"), 4,
                          GL_FLOAT, GL_FALSE,
                          sizeof(this->objModel.vertices[0]),
                          (GLvoid*)sizeof(this->objModel.vertices[0].XYZW));
    ILEngine::Error::ExitOnGLError("ERROR: Could not set VAO attributes");

    glGenBuffers(1, &(this->IBO));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 this->objModel.indices.size() * sizeof(int),
                 this->objModel.indices.data(),
                 GL_STATIC_DRAW);
    ILEngine::Error::ExitOnGLError("ERROR: Could not bind the IBO to the VAO");

    glBindVertexArray(0);
    ILEngine::Error::ExitOnGLError("ERROR: Could not unbind VAO");

    stopProgram();
}

}
