#include "gtest/gtest.h"
#include "../include/qf/stats/dists/norm.hpp"
#include <boost/math/special_functions/erf.hpp>

NormalDistribution norm(0.0, 1.0);

TEST(NormalDistribution, CDF) {
    EXPECT_NEAR(norm.cdf(0.0), 0.5, 1e-6);
    EXPECT_NEAR(norm.cdf(1.0), 0.8413447, 1e-6);
    EXPECT_NEAR(norm.cdf(-1.0), 0.1586553, 1e-6);
}

TEST(NormalDistribution, Quantile) {
    EXPECT_NEAR(norm.quantile(0.5), 0.0, 1e-6);
    EXPECT_NEAR(norm.quantile(0.8413447), 1.0, 1e-6);
    EXPECT_NEAR(norm.quantile(0.1586553), -1.0, 1e-6);
}

TEST(NormalDistribution, Entropy) {
    EXPECT_NEAR(norm.entropy(), 1.4189385, 1e-6);
}

TEST(NormalDistribution, PDF) {
    EXPECT_NEAR(norm.pdf(0.0), 0.3989423, 1e-6);
    EXPECT_NEAR(norm.pdf(1.0), 0.2419707, 1e-6);
    EXPECT_NEAR(norm.pdf(-1.0), 0.2419707, 1e-6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}