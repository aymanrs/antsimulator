#include "space.hpp"

void Coords::apply(Coords offset) {
    x += offset.x;
    y += offset.y;
}

Pixel::Pixel() : state(PixelState::NONE), redIntensity(0), blueIntensity(0) {}

Pixel::Pixel(const Pixel& copy){
    state = copy.state;
    redIntensity = copy.redIntensity;
    blueIntensity = copy.blueIntensity;
}

Pixel::Pixel(PixelState st, double redIntens, double blueIntens) : state(st), redIntensity(redIntens), blueIntensity(blueIntens) {}

Grid::Grid() {}

Grid::Grid(int width, int height, Coords home) : W(width), H(height), score(0) {
    pixels.resize(width);
    for(auto& v : pixels){
        v.resize(height);
    }
    pixels[home.x][home.y].state = PixelState::HOME;
    _home = home;
}

void Grid::set(Coords c, Pixel p){
    pixels[c.x][c.y] = p;
}

Pixel Grid::get(Coords c) const {
    return pixels[c.x][c.y];
}

void Grid::increaseScore() {
    score++;
}

int Grid::getScore() const {
    return score;
}

Coords Grid::getDimensions() const {
    return {W, H};
}

bool Grid::inside(Coords c) const {
    return 0 <= c.x && 0 <= c.y && c.x < W && c.y < H;
}

bool Grid::contains(Coords c) const {
    return inside(c) && get(c).state != WALL;
}

double Grid::attraction(Coords Tl, Coords Br, bool hasFood, double beta){
    double ans = 0;
    Coords tl = {std::min(Tl.x, Br.x), std::min(Tl.y, Br.y)};
    Coords br = {std::max(Tl.x, Br.x), std::max(Tl.y, Br.y)};
    for(int x = std::max(tl.x, 0); x <= std::min(br.x, W-1);x++){
        for(int y = std::max(tl.y, 0); y <= std::min(br.y, H-1);y++){
            switch(pixels[x][y].state){
            case PixelState::NONE:
                ans = std::max(beta, ans);
                break;
            case PixelState::WALL:
                break;
            case PixelState::HOME:
                if(hasFood) ans = 1e14;
                break;
            case PixelState::FOOD:
                if(!hasFood) ans = 1e14;
                break;
            case PixelState::PHER:
                if(hasFood) ans = std::max(pixels[x][y].redIntensity*1000+beta, ans);
                else ans = std::max(pixels[x][y].blueIntensity*1000+beta, ans);
                break;
            }
        }
    }
    return ans;
}