#include "../include/qf/stats/dists/norm.hpp"
#include <boost/math/special_functions/erf.hpp>
#include <cmath>
#include <random>


double NormalDistribution::cdf(double x) const {
    return 0.5 * (1.0 + boost::math::erf((x - mean_) / (sd_ * std::sqrt(2.0))));
}

double NormalDistribution::quantile(double p) const {
    return mean_ + sd_ * std::sqrt(2.0) * boost::math::erf_inv(2.0 * p - 1.0);
}

std::vector<double> NormalDistribution::sample(size_t n) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(mean_, sd_);
    std::vector<double> samples(n);
    for (size_t i = 0; i < n; ++i) {
        samples[i] = d(gen);
    }
    return samples;
}

double NormalDistribution::entropy() const {
    return 0.5 * std::log(2.0 * M_PI * std::exp(1.0) * sd_ * sd_);
}

double NormalDistribution::pdf(double x) const {
    return std::exp(-0.5 * std::pow((x - mean_) / sd_, 2)) / (sd_ * std::sqrt(2.0 * M_PI));
}


