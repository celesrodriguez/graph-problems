#ifndef COMPARE_H
#define COMPARE_H

#include <utility>

class CompareDistance
{
public:
    bool operator()(std::pair<int, float> p1, std::pair<int, float> p2) {
        return p1.second > p2.second;
    }

};
#endif
