#ifndef __MODELLOAD_H__
#define __MODELLOAD_H__

#include <vector>

#include "Model.h"

namespace ILEngine {

    class ModelLoader {

    public:
        /* Loads from file. Type determined from extension */
        static std::vector<Model> loadModel(const char *);

    };

}

#endif
