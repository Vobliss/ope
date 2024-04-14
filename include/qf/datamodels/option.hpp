#ifndef QF_DATAMODELS_OPTION_HPP
#define QF_DATAMODELS_OPTION_HPP

#include <cstdint>
#include <chrono>

struct OptionSide {
    OptionSide() = default;
    ~OptionSide() = default;
    enum class Side : std::int8_t {
        LONG = 1,
        SHORT = -1
    };

    Side side;

    constexpr OptionSide(Side side) noexcept : side(side) {}

    constexpr bool operator==(const OptionSide& other) const noexcept {
        return side == other.side;
    }

    constexpr bool operator!=(const OptionSide& other) const noexcept {
        return side != other.side;
    }
};

struct OptionType {
    OptionType() = default;
    ~OptionType() = default;

    enum class Type : std::int8_t {
        CALL = 1,
        PUT = -1
    };

    Type type;

    constexpr OptionType(Type type) noexcept : type(type) {}

    constexpr bool operator==(const OptionType& other) const noexcept {
        return type == other.type;
    }

    constexpr bool operator!=(const OptionType& other) const noexcept {
        return type != other.type;
    }
};

struct alignas(64) Option {
    Option() = default;
    ~Option() = default;

    Option(const Option& other) = default;
    Option& operator=(const Option& other) = default;

    Option(double strike_price, double spot_price, double days_to_expiration, double volatility,
        double risk_free_rate, double dividend_yield, OptionType option_side, OptionType option_type, std::chrono::system_clock::time_point expiration
    )
        : strike_price(strike_price), spot_price(spot_price), days_to_expiration(days_to_expiration), volatility(volatility), risk_free_rate(risk_free_rate), dividend_yield(dividend_yield), option_type(option_type), expiration(expiration) {}

    double strike_price;
    double spot_price;
    double days_to_expiration;
    double volatility;
    double risk_free_rate;
    double dividend_yield;
    OptionSide option_side;
    OptionType option_type;
    std::chrono::system_clock::time_point expiration;
};

#endif // QF_DATAMODELS_OPTION_HPP