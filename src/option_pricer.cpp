#include "../include/qf/pricing/options/option_pricer.hpp"

BlackScholesPricer BlackScholesPricer(const Option& option)
{
    return BlackScholesPricer(option);
}

template<typename T>
OptionPricingStrategy<T> createOptionPricingStrategy(T pricer)
{
    return OptionPricingStrategy<T>(pricer);
}