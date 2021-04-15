#ifndef __SPACE_HPP__
#define __SPACE_HPP__

#include <vector>

const int sense = 10;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Coords {
    int x, y;
    void apply(Coords offset);
};

enum PixelState {
    NONE,
    HOME,
    FOOD,
    PHER,
    WALL
};

struct Pixel {
    Pixel();
    Pixel(const Pixel& copy);
    Pixel(PixelState st, double redIntens, double blueIntens);
    PixelState state;
    double redIntensity;
    double blueIntensity;
};

class Grid {
public:
    Grid(int width, int height, Coords home);
    Grid();
    void set(Coords c, Pixel p);
    Pixel get(Coords c) const;
    void increaseScore();
    int getScore() const;
    Coords getDimensions() const;
    bool contains(Coords c) const;
    double attraction(Coords tl, Coords br, bool hasFood, double beta);
    Coords _home;
private:
    int W, H;
    int score;
    std::vector<std::vector<Pixel>> pixels;
};

#endif