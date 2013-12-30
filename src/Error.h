#ifndef __ERROR_H__
#define __ERROR_H__

namespace ILEngine {
    class Error {
    public:
        static void ExitOnGLError(const char *);
    };
}

#endif
