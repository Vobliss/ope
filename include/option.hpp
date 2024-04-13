#pragma once

#include <chrono>
#include <cstdint>

// Struct representing an option
struct alignas(64) Option {
    std::uint64_t id;
    std::uint64_t symbol_id;
    double strike_price;
    double underlying;
    double risk_free_rate;
    double dividend_yield;
    std::chrono::steady_clock::time_point expiry;
    std::int8_t option_type;
    std::int8_t side;
};

// Concept for an option configuration
template <typename T>
concept OptionConfig = requires(T t) {
    { t.id } -> std::same_as<std::uint64_t>;
    { t.symbol_id } -> std::same_as<std::uint64_t>;
    { t.strike_price } -> std::same_as<double>;
    { t.expiry } -> std::same_as<std::chrono::steady_clock::time_point>;
    { t.underlying } -> std::same_as<double>;
    { t.option_type } -> std::same_as<std::int8_t>;
    { t.side } -> std::same_as<std::int8_t>;
    { t.risk_free_rate } -> std::same_as<double>;
    { t.dividend_yield } -> std::same_as<double>;
};

// Class for building an option configuration
class alignas(64) OptionConfigBuilder {
public:
    std::uint64_t id;
    std::uint64_t symbol_id;
    double strike_price;
    std::chrono::steady_clock::time_point expiry;
    double underlying;
    std::int8_t option_type;
    std::int8_t side;
    double risk_free_rate;
    double dividend_yield;

    template<OptionConfig T>
    inline OptionConfigBuilder& operator=(const T& config) {
        id = config.id;
        symbol_id = config.symbol_id;
        strike_price = config.strike_price;
        expiry = config.expiry;
        underlying = config.underlying;
        option_type = config.option_type;
        side = config.side;
        risk_free_rate = config.risk_free_rate;
        dividend_yield = config.dividend_yield;

        return *this;
    }

    [[nodiscard]] inline Option getOption() const {
        return Option{id, symbol_id, strike_price, underlying, risk_free_rate, dividend_yield, expiry, option_type, side};
    }
};

// Concept for an option pricing model
template <typename T>
concept OptionPricingModel = requires(T t, const Option& option) {
    { t.calculatePrice(option) } -> std::same_as<double>;
    { t.getModelParameters() } -> std::same_as<std::array<std::pair<std::string_view, double>, T::param_count>>;
};

// Class for an option pricing engine
class OptionPricingEngine {
public:
    template <OptionPricingModel T, typename... Args>
    [[nodiscard]] inline double calculatePrice(const Option& option, const T& model, Args&&... args) const {
        return model.calculatePrice(option, std::forward<Args>(args)...);
    }
};

// Functions for normal distribution
[[nodiscard]] inline double normDF(double x);
[[nodiscard]] inline double normPDF(double x);

// Class for Black-Scholes model
class BlackScholesModel {
public:
    static constexpr std::size_t param_count = 1;

    [[nodiscard]] double calculatePrice(const Option& option, double volatility) const;
    [[nodiscard]] std::array<std::pair<std::string_view, double>, param_count> getModelParameters() const;
};

// Class for binomial model
class BinomialModel {
public:
    static constexpr std::size_t param_count = 2;

    [[nodiscard]] double calculatePrice(const Option& option, std::uint64_t steps, double volatility) const;
    [[nodiscard]] std::array<std::pair<std::string_view, double>, param_count> getModelParameters() const;
};

// Class for Heston model
class HestonModel {
public:
    static constexpr std::size_t param_count = 4;

    [[nodiscard]] double calculatePrice(const Option& option, double kappa, double theta, double sigma, double rho) const;
    [[nodiscard]] std::array<std::pair<std::string_view, double>, param_count> getModelParameters() const;
};