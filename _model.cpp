#include "_model.h"

std::vector<Vertex> Model::vert() {
    return this->vertices;
}

std::vector<int> Model::indi() {
    return this->indices;
}

std::vector<Vertex> Model::clearVert() {
    std::vector<Vertex> vv = this->vertices;
    this->vertices.clear();
    return vv;
}

std::vector<int> Model::clearIndi() {
    std::vector<int> iv = this->indices;
    this->indices.clear();
    return iv;
}

void Model::addVert(Vertex v) {
    this->vertices.push_back(v);
}

void Model::addIndi(int i) {
    this->indices.push_back(i);
}

void Model::setVert(std::vector<Vertex> vv) {
    this->vertices = vv;
}

void Model::setIndi(std::vector<int> iv) {
    this->indices = iv;
}
