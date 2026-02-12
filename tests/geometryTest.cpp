#include <gtest/gtest.h>
#include "math/Vec.h"

TEST(Vec3Test, NormalizeX) {
    Math::Vec3 v(3.0f, 0.0f, 0.0f);
    Math::Vec3 n = Math::Normalize(v);

    EXPECT_NEAR(n.x, 1.0f, 0.0001f);
    EXPECT_NEAR(n.y, 0.0f, 0.0001f);
    EXPECT_NEAR(n.z, 0.0f, 0.0001f);
}