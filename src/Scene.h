#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <unordered_map>

#include "Object.h"
#include "LightSource.h"

namespace ILEngine {

    class Scene {
        std::string sceneName;
        std::unordered_multimap<std::string, Object>      sceneObjs;
        std::unordered_multimap<std::string, LightSource> lights;

        GLuint defaultShaderProgram;

        template <class T>
            void addObject(T, std::unordered_multimap<std::string, T> &);

        template <class T>
            void addObjects(std::vector<T>, std::unordered_multimap<std::string, T> &);

        template <class T>
            std::vector<T> getObjectsByName(const char *, std::unordered_multimap<std::string, T> &);

        template <class T>
            void deleteByName(const char *, std::unordered_multimap<std::string, T> &);

        template <class T>
            void deleteByNames(std::vector<std::string>, std::unordered_multimap<std::string, T> &);

        template <class T>
            std::vector<T> allObjects(std::unordered_multimap<std::string, T> &);

    public:
        Scene(std::string, GLuint);

        void init();

        void addObject(Object);
        void addLight(LightSource);
        void addObjects(std::vector<Object>);
        void addLights(std::vector<LightSource>);

        void deleteObject(std::string);
        void deleteObjects(std::vector<std::string>);
        void deleteLight(std::string);
        void deleteLights(std::vector<std::string>);

        std::vector<Object>      getObject(std::string);
        std::vector<LightSource> getLights(std::string);

        std::vector<Object>      allObjects(void);
        std::vector<LightSource> allLights(void);

        GLuint sceneShader(void);

        std::string name(void);
        void        renderScene(void);
    };

}

#endif
