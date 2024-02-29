#include "utils.hpp"

std::random_device rd;
std::default_random_engine e1(rd());
int generate_random_number(int from, int to) 
{
    std::uniform_int_distribution<int> dist(from, to);
    return dist(e1);
}