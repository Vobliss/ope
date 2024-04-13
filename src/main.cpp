#include <iostream>
#include "../include/bsm_pricer.h"
#include <gtest/gtest.h>


int main() {
    OptionContract contract = {
        .strike = 100.0,
        .price = 5.0,
        .volatility = 0.2,
        .risk_free_rate = 0.05,
        .time_to_maturity = 1.0,
        .underlying_price = 100.0,
        .dividend_yield = 0.0,
        .option_type = 1.0,
        .d1 = 0.0,
        .d2 = 0.0
    };
    BSMPricer pricer(contract);
    double price = pricer.price();
    std::cout << "Price: " << price << std::endl;
    return 0;
}