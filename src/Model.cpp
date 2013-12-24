#include "Model.h"

namespace ILEngine {

Model::Model() {
    std::vector<Vertex> vv;
    std::vector<int> iv;

    this->vertices = vv;
    this->indices  = iv;
}

Model::Model(std::vector<Vertex> vv, std::vector<int> iv) {
    setVert(vv);
    setIndi(iv);
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
    this->vertices.~vector<Vertex>();
    this->vertices = vv;
}

void Model::setIndi(std::vector<int> iv) {
    this->indices.~vector<int>();
    this->indices = iv;
}

bool Model::operator==(const Model &rhs) const {
    if (rhs.vertices.size() != this->vertices.size()
     || rhs.indices.size()  != this->indices.size())
    {
        return false;
    }

    int i;
    for (i = 0; i < rhs.vertices.size(); i++) {
        if (rhs.vertices[i].XYZW[0] == this->vertices[i].XYZW[0]
         && rhs.vertices[i].XYZW[1] == this->vertices[i].XYZW[1]
         && rhs.vertices[i].XYZW[2] == this->vertices[i].XYZW[2]
         && rhs.vertices[i].XYZW[3] == this->vertices[i].XYZW[3]

         && rhs.vertices[i].RGBA[0] == this->vertices[i].RGBA[0]
         && rhs.vertices[i].RGBA[1] == this->vertices[i].RGBA[1]
         && rhs.vertices[i].RGBA[2] == this->vertices[i].RGBA[2]
         && rhs.vertices[i].RGBA[3] == this->vertices[i].RGBA[3])
        {
            return true;
        } else {
            return false;
        }
    }

    for (i = 0; i < rhs.indices.size(); i++) {
        if (rhs.indices[i] == this->indices[i]) {
            return true;
        } else {
            return false;
        }
    }

}

bool Model::operator!=(const Model &rhs) const {
    if (rhs.vertices.size() != this->vertices.size()
     || rhs.indices.size()  != this->indices.size())
    {
        return true;
    }

    int i;
    for (i = 0; i < rhs.vertices.size(); i++) {
        if (rhs.vertices[i].XYZW[0] == this->vertices[i].XYZW[0]
         && rhs.vertices[i].XYZW[1] == this->vertices[i].XYZW[1]
         && rhs.vertices[i].XYZW[2] == this->vertices[i].XYZW[2]
         && rhs.vertices[i].XYZW[3] == this->vertices[i].XYZW[3]

         && rhs.vertices[i].RGBA[0] == this->vertices[i].RGBA[0]
         && rhs.vertices[i].RGBA[1] == this->vertices[i].RGBA[1]
         && rhs.vertices[i].RGBA[2] == this->vertices[i].RGBA[2]
         && rhs.vertices[i].RGBA[3] == this->vertices[i].RGBA[3])
        {
            return false;
        } else {
            return true;
        }
    }

    for (i = 0; i < rhs.indices.size(); i++) {
        if (rhs.indices[i] == this->indices[i]) {
            return false;
        } else {
            return true;
        }
    }

}

}
