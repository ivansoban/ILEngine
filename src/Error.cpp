#include <string.h>
#include <stdlib.h>
#include <stdexcept>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Error.h"

namespace ILEngine {

void Error::ExitOnGLError(const char* error_message) {
    const GLenum ErrorValue = glGetError();

    if (ErrorValue != GL_NO_ERROR) {
        const char* APPEND_DETAIL_STRING = ": %s\n";
        const size_t APPEND_LENGTH = strlen(APPEND_DETAIL_STRING) + 1;
        const size_t message_length = strlen(error_message);
        char* display_message = (char*)malloc(message_length + APPEND_LENGTH);

        memcpy(display_message, error_message, message_length);
        memcpy(&display_message[message_length], APPEND_DETAIL_STRING, APPEND_LENGTH);

        fprintf(stderr, display_message, gluErrorString(ErrorValue));

        free(display_message);
        exit(EXIT_FAILURE);
    }
}

}
