#include "../include/qf/pricing/options/option_pricer.hpp"
#include <gtest/gtest.h>

TEST(OptionPricer, BlackScholesPricer) {
    BlackScholesPricer blackScholesPricer;
    Option option(100.0, 100.0, 1.0, 0.2, 0.05, 0.0, OptionType::Type::CALL, OptionType::Type::PUT, std::chrono::system_clock::now());
    EXPECT_NEAR(BlackScholesPricer().price(option), 5.943273, 1e-6);
}

TEST(OptionPricer, OptionPricingStrategy) {
    BlackScholesPricer blackScholesPricer;
    Option option(100.0, 100.0, 1.0, 0.2, 0.05, 0.0, OptionType::Type::CALL, OptionType::Type::PUT, std::chrono::system_clock::now());
    OptionPricingStrategy<BlackScholesPricer> optionPricingStrategy(blackScholesPricer);
    EXPECT_NEAR(optionPricingStrategy.calculatePrice(option), 5.943273, 1e-6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}