#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

#include "Vertex.h"

namespace ILEngine {

    class Model {
    public:
        std::vector<Vertex> vertices;
        std::vector<int>    indices;

        Model();
        Model(std::vector<Vertex>, std::vector<int>);

        std::vector<Vertex> clearVert();
        std::vector<int>    clearIndi();

        void addVert(Vertex);
        void addIndi(int);

        void setVert(std::vector<Vertex>);
        void setIndi(std::vector<int>);

        bool operator==(const Model &) const;
        bool operator!=(const Model &) const;
    };

}

#endif
