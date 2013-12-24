#define GLFW_INCLUDE_GL_3

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../src/Shader.h"
#include "../src/ShaderProgram.h"
#include "../src/Object.h"
#include "../src/Model.h"
#include "../src/ModelLoader.h"
#include "gtest/gtest.h"

namespace {

    class ShaderTest : public ::testing::Test {
        protected:

        std::vector<ILEngine::Shader> sv;

        ShaderTest() {
            ILEngine::Shader vert("../src/SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
            ILEngine::Shader frag("../src/SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);

            sv.push_back(vert);
            sv.push_back(frag);

            if (!glfwInit()) {
                exit(EXIT_FAILURE);
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            GLFWwindow *WindowHandle = glfwCreateWindow(1, 1, "test", NULL, NULL);
            if (!WindowHandle) {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            glfwMakeContextCurrent(WindowHandle);

            glewExperimental = true; // Need for core profile.
            if(glewInit() != GLEW_OK) {
                exit(EXIT_FAILURE);
            }
        }

        virtual ~ShaderTest() {
        }

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
    };

    TEST_F(ShaderTest, CreateProgram) {
        ILEngine::ShaderProgram prog(sv);
    }

    TEST_F(ShaderTest, UseStopProgram) {
        ILEngine::ShaderProgram prog(sv);
        prog.use();
        prog.stop();
    }

    TEST_F(ShaderTest, FetchUniformAttribute) {
        ILEngine::ShaderProgram prog(sv);
        prog.use();

        EXPECT_EQ(0, prog.attribute("vert"));
        EXPECT_EQ(1, prog.attribute("color"));

        EXPECT_EQ(8, prog.uniform("ModelMatrix"));
        EXPECT_EQ(0, prog.uniform("ViewMatrix"));
        EXPECT_EQ(4, prog.uniform("ProjectionMatrix"));

        prog.stop();
    }

    TEST_F(ShaderTest, DetachDestroyProgram) {
        ILEngine::ShaderProgram prog(sv);
        prog.use();
        prog.stop();
        prog.detachAll();
    }

    TEST_F(ShaderTest, TestModelLoading) {
        std::vector<ILEngine::Model> models = ILEngine::ModelLoader::loadModel("../test/untitled.obj");
        ASSERT_EQ(1, models.size());
    }

    TEST_F(ShaderTest, ObjectCreation) {
        ILEngine::ShaderProgram prog(sv);
        std::vector<ILEngine::Model> models = ILEngine::ModelLoader::loadModel("../test/untitled.obj");
        ILEngine::Object o("test object", false, prog.programId());

        EXPECT_STREQ("test object", o.getName().c_str());

        o.setModel(models[0]);

        EXPECT_EQ(models[0], o.getModel());
    }


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
