#include "../include/bsm_pricer.h"

BSMPricer::BSMPricer(OptionContract contract) {
    strike = contract.strike;
    double price = contract.price;
    volatility = contract.volatility;
    risk_free_rate = contract.risk_free_rate;
    time_to_maturity = contract.time_to_maturity;
    underlying_price = contract.underlying_price;
    dividend_yield = contract.dividend_yield;
    option_type = contract.option_type;
    d1 = 0.0;
    d2 = 0.0;
}

double BSMPricer::cdf(double x) {
    return 0.5 * erfc(-x * M_SQRT1_2);
}

double BSMPricer::price() {
    double d1 = (log(underlying_price / strike) + (risk_free_rate + 0.5 * volatility * volatility) * time_to_maturity) / (volatility * sqrt(time_to_maturity));
    double d2 = d1 - volatility * sqrt(time_to_maturity);
    return option_type * (underlying_price * cdf(option_type * d1) - strike * exp(-risk_free_rate * time_to_maturity) * cdf(option_type * d2));
}

double BSMPricer::delta() {
    d1 = (log(underlying_price / strike) + (risk_free_rate + 0.5 * volatility * volatility) * time_to_maturity) / (volatility * sqrt(time_to_maturity));
    return option_type * cdf(option_type * d1);
}

double BSMPricer::gamma() {
    d1 = (log(underlying_price / strike) + (risk_free_rate + 0.5 * volatility * volatility) * time_to_maturity) / (volatility * sqrt(time_to_maturity));
    return cdf(option_type * d1) / (underlying_price * volatility * sqrt(time_to_maturity));
}

double BSMPricer::vega() {
    d1 = (log(underlying_price / strike) + (risk_free_rate + 0.5 * volatility * volatility) * time_to_maturity) / (volatility * sqrt(time_to_maturity));
    return underlying_price * sqrt(time_to_maturity) * cdf(option_type * d1);
}

double BSMPricer::theta() {
    d1 = (log(underlying_price / strike) + (risk_free_rate + 0.5 * volatility * volatility) * time_to_maturity) / (volatility * sqrt(time_to_maturity));
    d2 = d1 - volatility * sqrt(time_to_maturity);
    return -underlying_price * volatility * cdf(option_type * d1) / (2 * sqrt(time_to_maturity)) - risk_free_rate * strike * exp(-risk_free_rate * time_to_maturity) * cdf(option_type * d2) + option_type * dividend_yield * strike * exp(-dividend_yield * time_to_maturity) * cdf(option_type * (d1 - volatility * sqrt(time_to_maturity)));
}

double BSMPricer::rho() {
    d2 = (log(underlying_price / strike) + (risk_free_rate + 0.5 * volatility * volatility) * time_to_maturity) / (volatility * sqrt(time_to_maturity));
    return option_type * strike * time_to_maturity * exp(-risk_free_rate * time_to_maturity) * cdf(option_type * d2);
}