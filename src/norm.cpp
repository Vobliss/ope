#include "../include/qf/stats/dists/norm.hpp"
#include <boost/math/special_functions/erf.hpp>
#include <cmath>


double NormalDistribution::cdf(double x) const {
    return 0.5 * (1 + std::erf((x - mean_) / (sd_ * std::sqrt(2))));
}

double NormalDistribution::quantile(double p) const {
    return mean_ + sd_ * std::sqrt(2) * boost::math::erf_inv(2 * p - 1);
}

double NormalDistribution::pdf(double x) const {
    return std::exp(-0.5 * std::pow((x - mean_) / sd_, 2)) / (sd_ * std::sqrt(2 * M_PI));
}