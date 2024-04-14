#include "../include/qf/stats/dists/dist.hpp"

template<typename T>
Distribution<T> dist = Distribution<T>();

template<typename T>
ContinuousDistribution<T> cont_dist = ContinuousDistribution<T>();

template<typename T>
DiscreteDistribution<T> disc_dist = DiscreteDistribution<T>();

template class Distribution<double>;
template class ContinuousDistribution<double>;
template class DiscreteDistribution<double>;
