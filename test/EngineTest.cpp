#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../src/Engine.h"
#include "../src/Object.h"
#include "../src/Scene.h"
#include "gtest/gtest.h"

namespace {

    class EngineTest : public ::testing::Test {
        protected:

        ILEngine::Engine e;

        EngineTest() : e(1,1) {
        }

        virtual ~EngineTest() {
        }


        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
    };

    TEST_F(EngineTest, InitEngine) {
        ASSERT_NO_THROW(e.initEngine());
    }

    TEST_F(EngineTest, SetProgramEngine) {
        e.initEngine();

        /* Create Shaders */
        ILEngine::Shader vert("../src/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
        ILEngine::Shader frag("../src/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);

        std::vector<ILEngine::Shader> shaders;
        shaders.push_back(vert);
        shaders.push_back(frag);

        ASSERT_NO_THROW(e.setDefaultProgram(shaders));
    }

    TEST_F(EngineTest, CleanEngine) {
        e.initEngine();

        /* Create Shaders */
        ILEngine::Shader vert("../src/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
        ILEngine::Shader frag("../src/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);

        std::vector<ILEngine::Shader> shaders;
        shaders.push_back(vert);
        shaders.push_back(frag);

        e.setDefaultProgram(shaders);

        ASSERT_NO_THROW(e.clean());
    }

    TEST_F(EngineTest, EngineData) {
        e.initEngine();

        ASSERT_EQ(glm::lookAt(glm::vec3(0,0,0), glm::vec3(-1,-1,-1), glm::vec3(0,1,0)), e.view());
        ASSERT_EQ(glm::perspective(60.0f, 1.0f, 1.0f, 100.0f), e.proj());

        ASSERT_EQ(glm::lookAt(glm::vec3(0,0,0), glm::vec3(-10,-10,-10), glm::vec3(0,1,0)),
                  e.view(glm::vec3(-10,-10,-10)));
        ASSERT_EQ(glm::perspective(60.0f, (float)2/4, 1.0f, 100.0f), e.proj(2,4));

    }

    TEST_F(EngineTest, SceneCreateEngine) {
        e.initEngine();

        /* Create Shaders */
        ILEngine::Shader vert("../src/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
        ILEngine::Shader frag("../src/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);

        std::vector<ILEngine::Shader> shaders;
        shaders.push_back(vert);
        shaders.push_back(frag);

        e.setDefaultProgram(shaders);

        ILEngine::Scene mainScene(std::string("main"), e.getDefaultEngineProgram());

        ILEngine::Object o1("../test/cube/cube.obj",
                            "test", true, -1,
                            glm::vec3(-2, -2, -2.5),
                            e.view(glm::vec3(-2, -2, -2.5)),
                            e.proj());
        ILEngine::Object o2("../test/cube/cube.obj",
                            "test", true, -1,
                           glm::vec3(-2, -2, -3),
                           e.view(),
                           e.proj());

        ASSERT_NO_THROW(mainScene.addObject(o1));
        ASSERT_NO_THROW(mainScene.addObject(o2));

        ASSERT_NO_THROW(mainScene.init());

        std::vector<ILEngine::Object> ov;
        ov.push_back(o1);
        ov.push_back(o2);

        ASSERT_NO_THROW(mainScene.addObjects(ov));

        ASSERT_EQ(4, mainScene.allObjects().size());

        ASSERT_NO_THROW(mainScene.init());

        ASSERT_NO_THROW(mainScene.renderScene());

        e.clean();
    }


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
