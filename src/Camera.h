#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

namespace ILEngine {

    class Camera {
        glm::vec3 _position;
        glm::vec3 _up;

    public:
        Camera(glm::vec3, glm::vec3);

        void setPosition(glm::vec3);
        void setUp(glm::vec3);

        glm::vec3 position();
        glm::vec3 up();

        glm::mat4 lookAt(glm::vec3);
    };

}

#endif
