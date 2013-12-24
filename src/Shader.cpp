#include "Shader.h"

namespace ILEngine {

Shader::Shader(std::string path, GLenum stype) {
    this->filepath   = path;
    this->shadertype = stype;
}

std::string Shader::file() {
    return this->filepath;
}

GLenum Shader::type() {
    return this->shadertype;
}

GLuint Shader::getId() {
    return this->id;
}

void Shader::setId(GLuint id) {
    this->id = id;
}

}
