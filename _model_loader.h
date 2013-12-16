#include <vector>

#include "_model.h"

class ModelLoader {

public:
    /* Loads from file. Type determined from extension */
    static std::vector<Model> loadModel(const char *);

};
