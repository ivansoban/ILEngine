#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Object.h"
#include "Error.h"

namespace ILEngine {

float CubeRotation = 0;
clock_t LastTime = 0;

Object::Object(std::string meshFile, std::string name, bool visibility, GLuint prog_id) : ModelMatrix(1.0f), ViewMatrix(1.0f), ProjMatrix(1.0f) {
    this->objName = name;
    this->hidden = visibility;
    this->program_id = prog_id;
    ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0.0f, 0.0f, -4));

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(meshFile, aiProcessPreset_TargetRealtime_Fast);

    this->GenAndBindBuffers(scene);

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

bool Object::isHidden() {
    return this->hidden;
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

    glDrawElements(GL_TRIANGLES, this->numFaces * 3, GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES, this->vertices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
    Error::ExitOnGLError("ERROR: Could not draw the cube");

    glBindVertexArray(0);
    this->stopProgram();
}


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

void Object::GenAndBindBuffers(const aiScene *scene) {
    /* Better suppose for indices needed . . . */
    glGetError();
    useProgram(this->program_id);

    aiMesh *mesh = scene->mMeshes[0];

    if (!mesh) {
        fprintf(stderr, "No Mesh!\n");
        return;
    }

    for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
        const aiFace* face = &mesh->mFaces[t];

        this->indices.push_back(face->mIndices[0]);
        this->indices.push_back(face->mIndices[1]);
        this->indices.push_back(face->mIndices[2]);
    }

    this->numFaces = mesh->mNumFaces;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        this->vertices.push_back(mesh->mVertices[i][0]);
        this->vertices.push_back(mesh->mVertices[i][1]);
        this->vertices.push_back(mesh->mVertices[i][2]);
    }

    // generate Vertex Array for mesh
    glGenVertexArrays(1, &(this->VAO));
    glBindVertexArray(VAO);

    // buffer for faces
    glGenBuffers(1, &(this->VBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(unsigned int) * this->numFaces * 3,
                 &(this->indices[0]),
                 GL_STATIC_DRAW);

    // buffer for vertex positions
    if (mesh->HasPositions()) {
        glGenBuffers(1, &(this->VBO));
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * this->vertices.size(),
                     &(this->vertices[0]),
                     GL_STATIC_DRAW);
        glEnableVertexAttribArray(getAttribute(this->program_id, "vert"));
        glVertexAttribPointer(getAttribute(this->program_id, "vert"), 3, GL_FLOAT, 0, 0, 0);
    }

    // buffer for vertex normals
/*    if (mesh->HasNormals()) {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * 3 * mesh->mNumVertices,
                     mesh->mNormals,
                     GL_STATIC_DRAW);
        glEnableVertexAttribArray(getAttribute(this->program_id, "normal"));
        glVertexAttribPointer(getAttribute(this->program_id, "normal"), 3, GL_FLOAT, 0, 0, 0);
    }*/
      // buffer for vertex texture coordinates
/*    if (mesh->HasTextureCoords(0)) {
        float *texCoords = (float *)malloc(sizeof(float) * 2 * mesh->mNumVertices);
        for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
            texCoords[k * 2]   = mesh->mTextureCoords[0][k].x;
            texCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;
        }
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * 2 * mesh->mNumVertices,
                     texCoords,
                     GL_STATIC_DRAW);
        glEnableVertexAttribArray(getAttribute(this->program_id, "texture"));
        glVertexAttribPointer(getAttribute(this->program_id, "texture"), 2, GL_FLOAT, 0, 0, 0);
    }*/

    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    stopProgram();

}

}
