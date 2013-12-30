#include "Camera.h"

namespace ILEngine {

    class Engine {
        Camera camera;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjMatrix;

    public:
        Engine(int, int);

        glm::mat4 view(void);
        glm::mat4 proj(void);

        glm::mat4 view(glm::vec3);
        glm::mat4 proj(int, int);

    };

}
