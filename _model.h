#include <vector>

#include "_primitive.h"

class Model {
    std::vector<Vertex> vertices;
    std::vector<int>    indices;

public:
    std::vector<Vertex> vert();
    std::vector<int>    indi();

    std::vector<Vertex> clearVert();
    std::vector<int>    clearIndi();

    void addVert(Vertex);
    void addIndi(int);

    void setVert(std::vector<Vertex>);
    void setIndi(std::vector<int>);
};
