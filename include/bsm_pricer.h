#ifndef BSM_PRICER_H
#define BSM_PRICER_H

#include <cmath>

struct alignas(128) OptionContract {
    double strike;
    double price;
    double volatility;
    double risk_free_rate;
    double time_to_maturity;
    double underlying_price;
    double dividend_yield;
    double option_type;
    double d1;
    double d2;
};

class BSMPricer: public OptionContract {
public:
    BSMPricer(OptionContract contract);
    double cdf(double x);
    double price();
    double delta();
    double gamma();
    double vega();
    double theta();
    double rho();
};

#endif // BSM_PRICER_H
