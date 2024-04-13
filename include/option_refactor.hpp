#pragma once

// Confirm Cache Size for Alignment (64 bytes)
#ifdef __GNUC__
#define CACHE_SIZE 64
#endif

#include <chrono>
#include <cstdint>

// Struct representing an option
struct alignas(CACHE_SIZE) Option {
    std::uint64_t id;
    std::uint64_t symbol_id;
    float strike_price;
    double underlying;
    double risk_free_rate;
    double dividend_yield;
    std::chrono::steady_clock::time_point expiry;
    std::int8_t option_type;
    std::int8_t side;
};
