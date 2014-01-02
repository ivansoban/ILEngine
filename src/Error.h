#ifndef __ERROR_H__
#define __ERROR_H__

#include <string>

namespace ILEngine {
    class Error {
    public:
        static void ExitOnGLError(std::string);
    };
}

#endif
