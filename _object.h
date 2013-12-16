#include <vector>
#include <string>

#include "_model.h"

class Object {
    Model       objModel;
    std::string objName;
    bool        hidden;

public:
    Object(std::string, bool);
    std::string getName();
    Model       getModel();
    bool        isHidden();

    void setModel(Model);
};
