#include "Scene.h"

namespace ILEngine {

Scene::Scene(std::string name, std::vector<Object> objs) {
    this->sceneName = name;
    this->addObjects(objs);
}

void Scene::deleteByName(const char *name) {
    std::string toDelete(name);

    this->sceneObjs.erase(name);
}

void Scene::deleteByNames(std::vector<std::string> names) {
    int i;
    for (i = 0; i < names.size(); i++) {
        this->sceneObjs.erase(names[i]);
    }
}

void Scene::addObject(Object o) {
    std::pair<std::string, Object> newEntry(o.getName(), o);
    this->sceneObjs.insert(newEntry);
}

void Scene::addObjects(std::vector<Object> objects) {
    int i;
    for (i = 0; i < objects.size(); i++) {
        std::pair<std::string, Object> newEntry(objects[i].getName(), objects[i]);
        this->sceneObjs.insert(newEntry);
    }
}

std::vector<Object> Scene::getObjectsByName(const char *name) {
    std::string toGet(name);
    std::vector<Object> foundObjs;

    for (auto it  = this->sceneObjs.find(name);
              it != this->sceneObjs.end(); it++)
    {
        foundObjs.push_back(it->second);
    }

    return foundObjs;
}

std::vector<Object> Scene::allObjects() {
    std::vector<Object> foundObjs;

    for (auto it  = this->sceneObjs.begin();
              it != this->sceneObjs.end(); it++)
    {
        foundObjs.push_back(it->second);
    }

    return foundObjs;

}

std::string Scene::name() {
    return this->sceneName;
}

void Scene::renderScene() {

    for (auto it  = this->sceneObjs.begin();
              it != this->sceneObjs.end(); it++)
    {
        it->second.draw();
    }

}


}
