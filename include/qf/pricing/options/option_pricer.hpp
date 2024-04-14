#ifndef QF_PRICING_OPTIONS_OPTION_PRICER_HPP
#define QF_PRICING_OPTIONS_OPTION_PRICER_HPP

#include "../../datamodels/option.hpp"
#include <cmath>
#include <numbers>
#include <execution>
#include <algorithm>

template<typename T>
concept Pricer = requires(T t, const Option& option) {
    { t.price(option) } -> std::same_as<double>;
};

class BlackScholesPricer {
public:
    inline constexpr double price(const Option& option) const noexcept {
        const double sqrt_T = std::sqrt(option.days_to_expiration);
        const double d1 = (std::log(option.spot_price / option.strike_price) + (option.risk_free_rate + 0.5 * option.volatility * option.volatility) * option.days_to_expiration) / (option.volatility * sqrt_T);
        const double d2 = d1 - option.volatility * sqrt_T;
        const double exp_rT = std::exp(-option.risk_free_rate * option.days_to_expiration);
        
        const double cdf_d1 = norm_cdf(d1);
        const double cdf_d2 = norm_cdf(d2);
        
        const double result = option.option_type == OptionType::Type::CALL ? option.spot_price * cdf_d1 - option.strike_price * exp_rT * cdf_d2 : option.strike_price * exp_rT * (1.0 - cdf_d2) - option.spot_price * (1.0 - cdf_d1);
        
        return option.option_side == OptionSide::Side::LONG ? result : -result;
    }

    inline void prices(const std::vector<Option>& options, std::vector<double>& results) const noexcept {
        std::transform(std::execution::par_unseq, options.begin(), options.end(), results.begin(),
            [this](const Option& option) {
                return price(option);
            });
    }

private:
    inline constexpr double norm_cdf(double x) const noexcept {
        // TODO: Fix the inv sqrt 2
        return 0.5 * std::erfc(-x * (1.0 / std::numbers::sqrt2));
    }
};

template<Pricer P>
class OptionPricingStrategy {
    P pricer;
public:
    constexpr OptionPricingStrategy(P pricer) noexcept : pricer(std::move(pricer)) {}

    constexpr double calculatePrice(const Option& option) const noexcept {
        return pricer.price(option);
    }

    template<std::random_access_iterator Iter>
    constexpr std::vector<double> calculatePrices(Iter first, Iter last, Iter result) const noexcept {
        std::vector<double> prices(std::distance(first, last));
        for (auto it = first; it != last; ++it) {
            *result = pricer.price(*it);
            ++result;
        }
        return prices;
    }
};

#endif // QF_PRICING_OPTIONS_OPTION_PRICER_HPP
