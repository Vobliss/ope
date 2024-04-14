#include "../include/qf/stats/dists/norm.hpp"
#include <boost/math/special_functions/erf.hpp>
#include <cmath>
#include <random>


double NormalDistribution::cdf(double x) const {
    return 0.5 * (1 + std::erf((x - mean_) / (sd_ * std::sqrt(2))));
}

double NormalDistribution::quantile(double p) const {
    return mean_ + sd_ * std::sqrt(2) * boost::math::erf_inv(2 * p - 1);
}

std::vector<double> NormalDistribution::sample(size_t n) const {
    std::vector<double> samples(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> d(mean_, sd_);
    for (size_t i = 0; i < n; ++i) {
        samples[i] = d(gen);
    }
    return samples;
} 

double NormalDistribution::pdf(double x) const {
    return std::exp(-0.5 * std::pow((x - mean_) / sd_, 2)) / (sd_ * std::sqrt(2 * M_PI));
}

