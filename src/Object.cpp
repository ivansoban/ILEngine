#include "Object.h"

Object::Object(std::string name, bool visibility) {
    this->objName = name;
    this->hidden = visibility;
}

std::string Object::getName() {
    return this->objName;
}

Model Object::getModel() {
    return this->objModel;
}

bool Object::isHidden() {
    return this->hidden;
}

void Object::setModel(Model m) {
    this->objModel = m;
}
