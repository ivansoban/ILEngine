#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <IL/devil_cpp_wrapper.hpp>

#include "Error.h"
#include "Object.h"

namespace ILEngine {

float CubeRotation = 0;
clock_t LastTime = 0;

Object::Object(std::string meshFile,
               std::string name,
               bool visibility,
               GLuint prog_id,
               glm::vec3 loc,
               glm::mat4 &v,
               glm::mat4 &p)
: ModelMatrix(1.0f), ViewMatrix(v), ProjMatrix(p) {

    this->objName = name;
    this->hidden = visibility;
    this->program_id = prog_id;
    this->meshFile = meshFile;

    this->ModelMatrix = glm::translate(ModelMatrix, loc);
}

Object::~Object() {

    // TODO: Delete globally! (Manager?)
    //glDeleteBuffers(1, &(this->VBO));
    //glDeleteBuffers(1, &(this->IBO));
    //glDeleteVertexArrays(1, &(this->VAO));

}

void Object::init(GLuint prog_id) {

    if (this->program_id == -1) {
        this->program_id = prog_id;
    }

    if (meshFile != "") {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(meshFile, aiProcessPreset_TargetRealtime_Fast);

        this->GenAndBindBuffers(scene);
        this->LoadTextures(scene);
    }

}

std::string Object::getName() {
    return this->objName;
}

bool Object::isHidden() {
    return this->hidden;
}

glm::vec3 Object::getLocation() {
    return this->location;
}

void Object::setLocation(glm::vec3 loc) {
    this->location = loc;
}

void Object::draw() {
    glGetError();
    clock_t Now = clock();

    if (LastTime == 0)
        LastTime = Now;

    CubeRotation += 10.0f * ((float)(Now - LastTime) / CLOCKS_PER_SEC);
    LastTime = Now;

    this->ModelMatrix = glm::rotate(this->ModelMatrix, CubeRotation, glm::vec3(1.0f, 1.0f, 0.0f));

    this->useProgram(this->program_id);
    glUniformMatrix4fv(this->getUniform(this->program_id, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(this->ProjMatrix));
    glUniformMatrix4fv(this->getUniform(this->program_id, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(this->ModelMatrix));
    glUniformMatrix4fv(this->getUniform(this->program_id, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(this->ViewMatrix));
    Error::ExitOnGLError("ERROR: Could not set the shader uniforms");

    glBindVertexArray(this->VAO);
    Error::ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

    //Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    Error::ExitOnGLError("ERROR: Could not bind active texture");
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
    Error::ExitOnGLError("ERROR: Could not bind texture");
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(this->getUniform(this->program_id, "textureSampler"), 0);
    Error::ExitOnGLError("ERROR: Could not set texture uniform");

    glDrawElements(GL_TRIANGLES, this->numFaces * 3, GL_UNSIGNED_INT, 0);
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

GLint Object::getAttribute(GLuint id, const char *aName) {
    /* Check if name is valid */
    if (!aName) {
        throw std::runtime_error("ERROR: aName is NULL.");
    }

    glGetError();
    GLint attrib = glGetAttribLocation(id, aName);
    if (attrib == -1) {
        ILEngine::Error::ExitOnGLError((std::string("Program attribute not found: ") + std::string(aName)).c_str());
    }

    return attrib;
}

GLint Object::getUniform(GLuint id, const char *uName) {
    /* Check if name is valid */
    if (!uName) {
        throw std::runtime_error("ERROR: uName is NULL.");
    }

    glGetError();
    GLint uni = glGetUniformLocation(id, uName);
    if (uni == -1) {
        ILEngine::Error::ExitOnGLError((std::string("Program uniform not found: ") + std::string(uName)).c_str());
    }

    return uni;
}

void Object::GenAndBindBuffers(const aiScene *scene) {
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
    Error::ExitOnGLError("ERROR: Could not generate and bind VAO");

    // buffer for faces
    glGenBuffers(1, &(this->IBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(unsigned int) * this->numFaces * 3,
                 &(this->indices[0]),
                 GL_STATIC_DRAW);
    Error::ExitOnGLError("ERROR: Could not bind index data to IBO");

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
        Error::ExitOnGLError("ERROR: Could not bind vertex data to VBO");
    }

    // buffer for vertex normals
    if (mesh->HasNormals()) {
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            this->normals.push_back(mesh->mNormals[i][0]);
            this->normals.push_back(mesh->mNormals[i][1]);
            this->normals.push_back(mesh->mNormals[i][2]);
        }

        glGenBuffers(1, &(this->NBO));
        glBindBuffer(GL_ARRAY_BUFFER, this->NBO);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * this->normals.size(),
                     &(this->normals[0]),
                     GL_STATIC_DRAW);
        glEnableVertexAttribArray(1/*getAttribute(this->program_id, "norm")*/);
        Error::ExitOnGLError("ERROR: Could not bind normal data to NBO4");
        glVertexAttribPointer(1/*getAttribute(this->program_id, "norm")*/, 3, GL_FLOAT, 0, 0, 0);
        Error::ExitOnGLError("ERROR: Could not bind normal data to NBO5");
    }

    // buffer for vertex texture coordinates
    if (mesh->HasTextureCoords(0)) {
        for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
            this->UVcoord.push_back(mesh->mTextureCoords[0][k].x);
            this->UVcoord.push_back(mesh->mTextureCoords[0][k].y);
        }

        glGenBuffers(1, &(this->TBO));
        glBindBuffer(GL_ARRAY_BUFFER, this->TBO);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * this->UVcoord.size(),
                     &(this->UVcoord[0]),
                     GL_STATIC_DRAW);
        glEnableVertexAttribArray(getAttribute(this->program_id, "vertexUV"));
        glVertexAttribPointer(getAttribute(this->program_id, "vertexUV"), 2, GL_FLOAT, 0, 0, 0);
        Error::ExitOnGLError("ERROR: Could not bind texture data");
    }

    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    this->stopProgram();

}

void Object::LoadTextures(const aiScene* scene) { // Only one texture per object
    glGetError();
    ILboolean success;

    /* initialization of DevIL */
    ilInit();

    aiString path;  // filename
    /* scan scene's materials for textures */
    for (unsigned int m = 0; m < scene->mNumMaterials; m++) {
        int texIndex = 0;

        aiReturn texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        while (texFound == AI_SUCCESS) {
            // more textures?
            texIndex++;
            texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        }
    }

    /* create and fill array with DevIL texture ids */
    ILuint imageId;
    ilGenImages(1, &imageId);

    /* create and fill array with GL texture ids */
    glGenTextures(1, &(this->texture_id)); /* Texture name generation */
    Error::ExitOnGLError("ERROR: Could not generate textures");

    //save IL image ID
    std::string filename(std::string("../test/cube/") + path.data);  // get filename

    ilBindImage(imageId); /* Binding of DevIL image name */
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    success = ilLoadImage((ILstring)filename.c_str());
    if (success) {
        /* Convert image to RGBA */
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        /* Create and load textures to OpenGL */
        glBindTexture(GL_TEXTURE_2D, this->texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH),
                     ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     ilGetData());
        Error::ExitOnGLError("ERROR: Could not load textures");
    } else {
        printf("Couldn't load Image: %s\n", filename.c_str());
        // TODO: Better clean up!
    }

    /* Because we have already copied image data into texture data
       we can release memory used by image. */
    ilDeleteImages(1, &imageId);

    glBindTexture(GL_TEXTURE_2D, 0);

}

}
