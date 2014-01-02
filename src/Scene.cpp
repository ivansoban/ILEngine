#include "Scene.h"

namespace ILEngine {

Scene::Scene(std::string name, GLuint prog_id) {
    this->sceneName = name;
    this->defaultShaderProgram = prog_id;
}

void Scene::init() {
    for (auto it  = this->sceneObjs.begin();
              it != this->sceneObjs.end(); it++)
    {
        it->second.init(this->defaultShaderProgram);
    }
}

template <class T>
void Scene::deleteByName(const char *name, std::unordered_multimap<std::string, T> & map) {
    std::string toDelete(name);

    map.erase(name);
}

template <class T>
void Scene::deleteByNames(std::vector<std::string> names, std::unordered_multimap<std::string, T> & map) {
    int i;
    for (i = 0; i < names.size(); i++) {
        map.erase(names[i]);
    }
}

template <class T>
void Scene::addObject(T o, std::unordered_multimap<std::string, T> & map) {
    std::pair<std::string, T> newEntry(o.getName(), o);
    map.insert(newEntry);
}

template <class T>
void Scene::addObjects(std::vector<T> objects, std::unordered_multimap<std::string, T> & map) {
    int i;
    for (i = 0; i < objects.size(); i++) {
        std::pair<std::string, T> newEntry(objects[i].getName(), objects[i]);
        map.insert(newEntry);
    }
}

template <class T>
std::vector<T> Scene::getObjectsByName(const char *name, std::unordered_multimap<std::string, T> & map) {
    std::string toGet(name);
    std::vector<T> foundObjs;

    for (auto it  = map.find(name);
              it != map.end(); it++)
    {
        foundObjs.push_back(it->second);
    }

    return foundObjs;
}

template <class T>
std::vector<T> Scene::allObjects(std::unordered_multimap<std::string, T> & map) {
    std::vector<T> foundObjs;

    for (auto it  = map.begin();
              it != map.end(); it++)
    {
        foundObjs.push_back(it->second);
    }

    return foundObjs;

}

void Scene::addObject(Object o) {
    this->addObject(o, this->sceneObjs);
}

void Scene::addLight(LightSource l) {
    this->addObject(l, this->lights);
}

void Scene::addObjects(std::vector<Object> ov) {
    this->addObjects(ov, this->sceneObjs);
}

void Scene::addLights(std::vector<LightSource> lv) {
    this->addObjects(lv, this->lights);
}

void Scene::deleteObject(std::string name) {
    this->deleteByName(name.c_str(), this->sceneObjs);
}

void Scene::deleteObjects(std::vector<std::string> names) {
    this->deleteByNames(names, this->sceneObjs);
}

void Scene::deleteLight(std::string name) {
    this->deleteByName(name.c_str(), this->lights);
}

void Scene::deleteLights(std::vector<std::string> names) {
    this->deleteByNames(names, this->lights);
}

std::vector<Object>      Scene::getObject(std::string name) {
    return this->getObjectsByName(name.c_str(), this->sceneObjs);
}

std::vector<LightSource> Scene::getLights(std::string name) {
    return this->getObjectsByName(name.c_str(), this->lights);
}

std::vector<Object>      Scene::allObjects(void) {
    return this->allObjects(this->sceneObjs);
}

std::vector<LightSource> Scene::allLights(void) {
    return this->allObjects(this->lights);
}

GLuint Scene::sceneShader() {
    return this->defaultShaderProgram;
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
