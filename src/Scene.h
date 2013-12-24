#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <unordered_map>

#include "Object.h"

namespace ILEngine {

    class Scene {
        std::string sceneName;
        std::unordered_multimap<std::string, Object> sceneObjs;

    public:
        Scene(std::string, std::vector<Object>);

        void deleteByName(const char *);
        void deleteByNames(std::vector<std::string>);
        void addObject(Object);
        void addObjects(std::vector<Object>);

        std::vector<Object> getObjectsByName(const char*);
        std::vector<Object> allObjects(void);

        std::string name(void);
        void        renderScene(void);
    };

}

#endif
