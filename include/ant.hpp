#ifndef __ANT_HPP__
#define __ANT_HPP__

#include <random>
#include "space.hpp"

class Ant {
public:
    static std::mt19937 rng;
    Ant();
    void move();
    Coords getCoords() const;
private:
    int _steps;
    Coords _co;
    Direction _dir;
    double _beta;
    bool _hasFood;
};

#endif