#include "globals.hpp"
#include "ant.hpp"
#include "space.hpp"
#include <random>
#include <ctime>
#include <iostream>

std::mt19937 Ant::rng(time(0));

Ant::Ant() : _co(space._home), _hasFood(false), _steps(0)
{
    _dir = Direction(rng() % 4);
    _beta = rng() % 5+1;
}

Coords Ant::getCoords() const
{
    return _co;
}

void Ant::move()
{
    Direction newDir;
    double sum, c;
    double weights[4];
    switch (_dir)
    {
    case Direction::UP:
        weights[Direction::LEFT] = space.attraction({_co.x - sense, _co.y - 2}, {_co.x - 1, _co.y}, _hasFood, _beta) * space.contains({_co.x - 1, _co.y});
        weights[Direction::RIGHT] = space.attraction({_co.x + 1, _co.y - 2}, {_co.x + sense, _co.y}, _hasFood, _beta) * space.contains({_co.x + 1, _co.y});
        weights[Direction::DOWN] = 0;
        weights[Direction::UP] = (space.attraction({_co.x, _co.y - 2}, {_co.x, _co.y - 1}, _hasFood, _beta) +
                                  space.attraction({_co.x - 1, _co.y - sense - 1}, {_co.x + 1, _co.y - 3}, _hasFood, _beta)) *
                                 space.contains({_co.x, _co.y - 1});
        sum = weights[0] + weights[1] + weights[2] + weights[3];
        if (sum <= 0)
        {
            _dir = c > 0.5 ? Direction::LEFT : Direction::RIGHT;
            return;
        }
        for (int i = 0; i < 4; i++)
            weights[i] = (i == 0 ? 0 : weights[i - 1]) + weights[i] / sum;
        c = (rng() % 1000001) / 1000000.;
        for (int i = 0; i < 4; i++)
            if (c <= weights[i])
            {
                newDir = Direction(i);
                break;
            }
        break;
    case Direction::DOWN:
        weights[Direction::LEFT] = space.attraction({_co.x - sense, _co.y + 2}, {_co.x - 1, _co.y}, _hasFood, _beta) * space.contains({_co.x - 1, _co.y});
        weights[Direction::RIGHT] = space.attraction({_co.x + 1, _co.y + 2}, {_co.x + sense, _co.y}, _hasFood, _beta) * space.contains({_co.x + 1, _co.y});
        weights[Direction::UP] = 0;
        weights[Direction::DOWN] = (space.attraction({_co.x, _co.y + 2}, {_co.x, _co.y + 1}, _hasFood, _beta) +
                                    space.attraction({_co.x - 1, _co.y + sense + 1}, {_co.x + 1, _co.y + 3}, _hasFood, _beta)) *
                                   space.contains({_co.x, _co.y + 1});
        c = (rng() % 1000001) / 1000000.;
        sum = weights[0] + weights[1] + weights[2] + weights[3];
        if (sum <= 0)
        {
            _dir = c > 0.5 ? Direction::LEFT : Direction::RIGHT;
            return;
        }
        for (int i = 0; i < 4; i++)
            weights[i] = (i == 0 ? 0 : weights[i - 1]) + weights[i] / sum;
        for (int i = 0; i < 4; i++)
            if (c <= weights[i])
            {
                newDir = Direction(i);
                break;
            }
        break;
    case Direction::LEFT:
        weights[Direction::UP] = space.attraction({_co.x - 2, _co.y - sense}, {_co.x, _co.y - 1}, _hasFood, _beta) * space.contains({_co.x, _co.y - 1});
        weights[Direction::DOWN] = space.attraction({_co.x - 2, _co.y + sense}, {_co.x, _co.y+1}, _hasFood, _beta) * space.contains({_co.x, _co.y + 1});
        weights[Direction::RIGHT] = 0;
        weights[Direction::LEFT] = (space.attraction({_co.x-2, _co.y}, {_co.x-1, _co.y}, _hasFood, _beta) +
                                   space.attraction({_co.x - sense -1, _co.y - 1}, {_co.x - 3, _co.y + 1}, _hasFood, _beta)) * space.contains({_co.x-1, _co.y});
        sum = weights[0] + weights[1] + weights[2] + weights[3];
        if (sum <= 0)
        {
            _dir = c > 0.5 ? Direction::UP : Direction::DOWN;
            return;
        }
        for (int i = 0; i < 4; i++)
            weights[i] = (i == 0 ? 0 : weights[i - 1]) + weights[i] / sum;
        c = (rng() % 1000001) / 1000000.;
        for (int i = 0; i < 4; i++)
            if (c <= weights[i])
            {
                newDir = Direction(i);
                break;
            }
        break;
    case Direction::RIGHT:
        weights[Direction::UP] = space.attraction({_co.x + 2, _co.y - sense}, {_co.x, _co.y - 1}, _hasFood, _beta) * space.contains({_co.x, _co.y - 1});
        weights[Direction::DOWN] = space.attraction({_co.x + 2, _co.y + sense}, {_co.x, _co.y+1}, _hasFood, _beta) * space.contains({_co.x, _co.y + 1});
        weights[Direction::LEFT] = 0;
        weights[Direction::RIGHT] = (space.attraction({_co.x+2, _co.y}, {_co.x+1, _co.y}, _hasFood, _beta) +
                                   space.attraction({_co.x + sense + 1, _co.y - 1}, {_co.x + 3, _co.y + 1}, _hasFood, _beta)) * space.contains({_co.x+1, _co.y});
        sum = weights[0] + weights[1] + weights[2] + weights[3];
        if (sum <= 0)
        {
            _dir = c > 0.5 ? Direction::UP : Direction::DOWN;
            return;
        }
        for (int i = 0; i < 4; i++)
            weights[i] = (i == 0 ? 0 : weights[i - 1]) + weights[i] / sum;
        c = (rng() % 1000001) / 1000000.;
        for (int i = 0; i < 4; i++)
            if (c <= weights[i])
            {
                newDir = Direction(i);
                break;
            }
        break;
    }
    //std::cout << weights[0] << ' ' << weights[1] << ' ' << weights[2] << ' ' << weights[3] << std::endl;
    _dir = newDir;
    if(space.get(_co).state == NONE) space.set(_co, {PHER, 0, 0});
    if(!_hasFood && space.get(_co).state == PHER){
        //_steps = std::min(_steps * 1., 700-space.get(_co).redIntensity);
        space.set(_co, {PHER, std::max(1100.-_steps, space.get(_co).redIntensity), space.get(_co).blueIntensity});
    } else if(_hasFood && space.get(_co).state == PHER){
        //_steps = std::min(_steps * 1., 700-space.get(_co).blueIntensity);
        space.set(_co, {PHER, space.get(_co).redIntensity, std::max(1100.-_steps, space.get(_co).blueIntensity)});
    }
    if(_dir == UP) _co.apply({0, -1});
    else if(_dir == DOWN) _co.apply({0, 1});
    else if(_dir == LEFT) _co.apply({-1, 0});
    else _co.apply({1, 0});
    _steps++;
    if(space.get(_co).state == HOME && _hasFood){
        space.increaseScore();
        _hasFood = false;
        _steps = 0;
    } else if(space.get(_co).state == FOOD && !_hasFood){
        _hasFood = true;
        _steps = 0;
        space.set(_co, Pixel());
    }
}