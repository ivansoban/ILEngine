#include "tiny_obj_loader.h"
#include "ModelLoader.h"

#include <iostream>
#include <cassert>

namespace ILEngine {

std::vector<Model> ModelLoader::loadModel(const char *filepath) {
    std::cout << "Loading: " << filepath << std::endl;

    std::string fp(filepath);

    std::string filename = "";
    std::string basepath = "";

    int i;
    for (i = (fp.size() - 1); (fp[i] != '/' && i >= 0); i--) {
        filename = fp[i]  + filename;
    }

    int j;
    for (j = 0; j <= i; j++) {
        basepath += fp[j];
    }

    assert((basepath + filename) == fp); /* Check proper split. */

    std::vector<tinyobj::shape_t> shapes;
    std::string err = tinyobj::LoadObj(shapes, fp.c_str(), basepath.c_str());

    if (!err.empty()) {
        std::cerr << err << std::endl;
        throw 1; /* TODO: better exceptions */
    } else {
        std::cerr << "Found " << shapes.size() << " objects." << std::endl;
    }

    std::vector<Model> models;

    for(i = 0; i < shapes.size(); i++) {

        Model m;

        assert(shapes[i].mesh.positions.size() % 3 == 0); /* Should be all triangles! */
        for(j = 0; j < shapes[i].mesh.positions.size(); j += 3) {

            Vertex v;

            v.XYZW[0] = shapes[i].mesh.positions[j + 0];
            v.XYZW[1] = shapes[i].mesh.positions[j + 1];
            v.XYZW[2] = shapes[i].mesh.positions[j + 2];
            v.XYZW[3] = 1; /* Homogeneous */

            /* TODO: color, et cetera */
            v.RGBA[0] = 1.0f;
            v.RGBA[1] = 1.0f;
            v.RGBA[2] = 1.0f;
            v.RGBA[3] = 0.0f;

            m.addVert(v);
        }

        for(j = 0; j < shapes[i].mesh.indices.size(); j++) {
            m.addIndi(shapes[i].mesh.indices[j]);
        }

        models.push_back(m);

    }

    return models;

}

}
