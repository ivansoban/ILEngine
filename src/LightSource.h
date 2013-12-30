#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <string>

#include "Object.h"

namespace ILEngine {

    class LightSource : public Object {
        float intensity;

    public:
        LightSource(std::string, std::string, GLuint, glm::vec3, float);
        void draw();
    };

}

#endif
