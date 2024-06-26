#ifndef QF_STATS_DISTS_NORM_HPP
#define QF_STATS_DISTS_NORM_HPP

#include "dist.hpp"
#include <vector>

class NormalDistribution : public ContinuousDistribution<double> {
public:

    NormalDistribution(double mean = 0.0, double sd = 1.0) : mean_(mean), sd_(sd) {}

    double cdf(double x) const override;
    double quantile(double p) const override;
    std::vector<double> sample(size_t n) const override;
    double entropy() const override;
    double pdf(double x) const override;
    double mean() const { return mean_; }
    double sd() const { return sd_; }

private:
    double mean_;
    double sd_;
};

#endif