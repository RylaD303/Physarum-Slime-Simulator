#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

int generate_random_number(int from = 0, int to = 100);

std::random_device rd;
std::default_random_engine e1(rd());
int generate_random_number(int from, int to)
{
    std::uniform_int_distribution<int> uniform_dist(from, to);
    return uniform_dist(e1);
}

#endif /* UTILS_HPP*/
