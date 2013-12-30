#include <glm/gtc/matrix_transform.hpp>

#include "Engine.h"

namespace ILEngine {

Engine::Engine(int CurrentWidth, int CurrentHeight)
: camera(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)), ViewMatrix(1.0f), ProjMatrix(1.0f)
{
    this->ViewMatrix = this->view(glm::vec3(0, 0, -5));
    this->ProjMatrix = this->proj(CurrentWidth, CurrentHeight);
}

glm::mat4 Engine::view() {
    return this->ViewMatrix;
}

glm::mat4 Engine::proj() {
    return this->ProjMatrix;
}

glm::mat4 Engine::view(glm::vec3 look) {
    return (this->ViewMatrix = this->camera.lookAt(look));
}

glm::mat4 Engine::proj(int CurrentWidth, int CurrentHeight) {
    return (this->ProjMatrix =  glm::perspective(
        60.0f,
        (float)CurrentWidth / CurrentHeight,
        1.0f,
        100.0f
    ));
}

}
