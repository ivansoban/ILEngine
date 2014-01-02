#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Error.h"

namespace ILEngine {

void Error::ExitOnGLError(std::string error_message) {
    const GLenum ErrorValue = glGetError();

    if (ErrorValue != GL_NO_ERROR) {

        std::cerr << error_message << ": "
                  << std::string((const char *)gluErrorString(ErrorValue))
                  << std::endl;

        throw std::runtime_error(error_message);
    }
}

}
