#ifndef QF_STATS_DISTS_DIST_HPP
#define QF_STATS_DISTS_DIST_HPP


template <typename T>
class Distribution {
public:
    Distribution() = default;

    virtual double cdf(T x) const = 0;
    virtual double quantile(T p) const = 0;

};

template <typename T>
class ContinuousDistribution : public Distribution<T> {
public:
    virtual double pdf(T x) const = 0;
};

template <typename T>
class DiscreteDistribution : public Distribution<T> {
public:
    virtual double pmf(T x) const = 0;
};

#endif