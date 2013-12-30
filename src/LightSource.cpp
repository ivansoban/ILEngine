#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "LightSource.h"

namespace ILEngine {

LightSource::LightSource(std::string meshFile,
                         std::string name,
                         GLuint prog_id,
                         glm::vec3 loc,
                         float intensity) : Object(meshFile, name, false, prog_id, loc) {

   this->intensity = intensity;

}

void LightSource::draw() {

}

}
