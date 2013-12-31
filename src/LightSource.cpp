#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "LightSource.h"

namespace ILEngine {

LightSource::LightSource(std::string meshFile,
                         std::string name,
                         GLuint prog_id,
                         glm::vec3 loc,
                         float intensity,
                         glm::mat4 &v,
                         glm::mat4 &p)
: Object(meshFile, name, false, prog_id, loc, v, p) {

   this->intensity = intensity;

}

void LightSource::draw() {

}

}
