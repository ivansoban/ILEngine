#include "Shader.h"

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

void Shader::setId(GLuint id) {
    this->id = id;
}
