#include "../include/qf/datamodels/option.hpp"

Option Option(double strike_price, double spot_price, double days_to_expiration, double volatility,
    double risk_free_rate, double dividend_yield, OptionSide option_side, OptionType option_type, std::chrono::system_clock::time_point expiration
)
{
    return Option(strike_price, spot_price, days_to_expiration, volatility, risk_free_rate, dividend_yield, option_side, option_type, expiration);
}