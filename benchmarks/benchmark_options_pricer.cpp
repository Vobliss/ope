#include "benchmark/benchmark.h"
#include "../include/qf/datamodels/option.hpp"
#include "../include/qf/pricing/options/option_pricer.hpp"
#include <chrono>
#include "qf/datamodels/option.hpp"

BlackScholesPricer blackScholesPricer;
Option option(100.0, 100.0, 1.0, 0.2, 0.05, 0.0, OptionType::Type::CALL, OptionType::Type::PUT, std::chrono::system_clock::now());
std::vector<Option> options(1000, option);
std::vector<double> results(options.size());

static void BM_BlackScholesPricer(benchmark::State& state) {
    for (auto _ : state) {
        blackScholesPricer.price(option);
    }
}

static void BM_MultiBlackScholesPricer(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& option : options) {
            blackScholesPricer.price(option);
        }
    }
}

static void BM_ParallelBlackScholesPricer(benchmark::State& state) {
    for (auto _ : state) {
        blackScholesPricer.prices(options, results);  
    }
}
        

BENCHMARK(BM_BlackScholesPricer);
BENCHMARK(BM_MultiBlackScholesPricer);
BENCHMARK(BM_ParallelBlackScholesPricer);