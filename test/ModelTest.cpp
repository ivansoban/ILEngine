#include <vector>
#include <iostream>

#include "../src/Model.h"
#include "../src/Vertex.h"
#include "gtest/gtest.h"

namespace {

    class ModelTest : public ::testing::Test {
        protected:

        ILEngine::Model *m1;

        ModelTest() {
            ILEngine::Vertex v1;
            ILEngine::Vertex v2;

            v1.XYZW[0] = 1;
            v1.XYZW[1] = 1;
            v1.XYZW[2] = 1;
            v1.XYZW[3] = 1;

            v1.RGBA[0] = 1;
            v1.RGBA[1] = 1;
            v1.RGBA[2] = 1;
            v1.RGBA[3] = 1;

            v2.XYZW[0] = -1;
            v2.XYZW[1] = -1;
            v2.XYZW[2] = -1;
            v2.XYZW[3] =  1;

            v2.RGBA[0] = 1;
            v2.RGBA[1] = 1;
            v2.RGBA[2] = 1;
            v2.RGBA[3] = 1;


            std::vector<ILEngine::Vertex> vv;
            std::vector<int>    iv;

            vv.push_back(v1);
            vv.push_back(v2);

            iv.push_back(1);
            iv.push_back(2);

            m1 = new ILEngine::Model(vv, iv);
        }

        virtual ~ModelTest() {
        }


        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
    };

    TEST_F(ModelTest, GetVertices) {
        EXPECT_EQ(2, m1->vertices.size());
    }

    TEST_F(ModelTest, GetIndices) {
        EXPECT_EQ(2, m1->indices.size());
    }

    TEST_F(ModelTest, AddVertices) {
        ILEngine::Vertex n;
        n.XYZW[0] = 1;
        n.XYZW[1] = 1;
        n.XYZW[2] = 1;
        n.XYZW[3] = 1;

        n.RGBA[0] = 1;
        n.RGBA[1] = 1;
        n.RGBA[2] = 1;
        n.RGBA[3] = 1;

        m1->addVert(n);

        EXPECT_EQ(3, m1->vertices.size());
    }

    TEST_F(ModelTest, AddIndices) {
        m1->addIndi(3);
        EXPECT_EQ(3, m1->indices.size());
    }

    TEST_F(ModelTest, ClearModel) {
        std::vector<ILEngine::Vertex> vv = m1->clearVert();
        std::vector<int>              iv = m1->clearIndi();

        EXPECT_EQ(0, m1->vertices.size());
        EXPECT_EQ(0, m1->indices.size());

        m1->setVert(vv);
        m1->setIndi(iv);
        EXPECT_EQ(2, m1->vertices.size());
        EXPECT_EQ(2, m1->indices.size());
    }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
