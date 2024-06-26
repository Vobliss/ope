#include "benchmark/benchmark.h"
#include "../include/qf/stats/dists/norm.hpp"


NormalDistribution norm(0.0, 1.0);
static void BM_NormalDistribution_CDF(benchmark::State& state) {
  for (auto _ : state) {
    norm.cdf(0.0);
  }
}

static void BM_NormalDistribution_Quantile(benchmark::State& state) {
  for (auto _ : state) {
    norm.quantile(0.5);
  }
}

static void BM_NormalDistribution_Sample(benchmark::State& state) {
  for (auto _ : state) {
    norm.sample(10000);
  }
}

static void BM_NormalDistribution_Entropy(benchmark::State& state) {
  for (auto _ : state) {
    norm.entropy();
  }
}

static void BM_NormalDistribution_PDF(benchmark::State& state) {
  for (auto _ : state) {
    norm.pdf(0.0);
  }
}

BENCHMARK(BM_NormalDistribution_CDF);
BENCHMARK(BM_NormalDistribution_Quantile);
BENCHMARK(BM_NormalDistribution_Sample);
BENCHMARK(BM_NormalDistribution_Entropy);
BENCHMARK(BM_NormalDistribution_PDF);

int main(int argc, char **argv) {
  ::benchmark::Initialize(&argc, argv);
  if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
  ::benchmark::RunSpecifiedBenchmarks();
}