#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

extern std::random_device rd;
extern std::default_random_engine e1;

int generate_random_number(int from = 0, int to = 100);

#endif /* UTILS_HPP */
