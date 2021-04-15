#include <SFML/Graphics.hpp>
#include "space.hpp"
#include "ant.hpp"
#include <iostream>

#define H 300
#define W 300
#define S 2

Grid space(W, H, {143, 234});

sf::Color pixelColor(Pixel s){
    switch(s.state){
    case PixelState::NONE:
        return sf::Color::Black;
        break;
    case PixelState::PHER:
        return sf::Color((s.redIntensity / 1100) * 255, 0, (s.blueIntensity / 1100) * 255);
    case PixelState::FOOD:
        return sf::Color::Green;
        break;
    case PixelState::WALL:
        return sf::Color(128, 128, 128);
        break;
    case PixelState::HOME:
        return sf::Color::White;
        break;
    }
    return sf::Color::Black;
}
int main(){
    sf::RenderWindow app;
    app.create(sf::VideoMode(W * S, H * S), "ant simulation");
    Ant ants[800];
    sf::Event e;
    for(int i = 220;i < 289;i++){
        for(int j = 128;j < 169;j++){
            space.set({i, j}, {PixelState::FOOD, 0, 0});
        }
    }
    sf::Font font;
    font.loadFromFile("res/Ubuntu-Regular.ttf");
    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color::White);
    while(app.isOpen()){
        while(app.pollEvent(e)){
            if(e.type == sf::Event::Closed){
                app.close();
            } else if(e.type == sf::Event::MouseButtonPressed){
                Coords c = {e.mouseButton.x/S, e.mouseButton.y/S};
                for(int x = c.x - 2;x <= c.x+2;x++){
                    for(int y = c.y - 2;y <= c.y+2;y++){
                        if(space.contains({x, y}) && space.get({x, y}).state != HOME) {
                            space.set({x, y}, {WALL, 0, 0});
                        }
                    }
                }
                space.set({e.mouseButton.x/S, e.mouseButton.y/S}, {WALL, 0, 0});
            }
        }
        app.clear();
        for(Ant& a : ants){
            a.move();
            //std::cout << a.getCoords().x << std::endl;
        }
        sf::RectangleShape re;
        for(int i = 0;i < W;i++){
            for(int j = 0;j < H;j++){
                re.setSize(sf::Vector2f(S, S));
                re.setPosition(i * S, j * S);
                re.setFillColor(pixelColor(space.get({i, j})));
                app.draw(re);
                Pixel p = space.get({i, j});
                if(p.state == PixelState::PHER){
                    space.set({i, j}, {PixelState::PHER, std::max(0., p.redIntensity-0.6), std::max(0., p.blueIntensity-0.6)});
                    if(p.redIntensity-0.6 <= 0 && p.blueIntensity-0.6 <= 0) space.set({i, j}, Pixel());
                }
            }
        }
        score.setString(std::to_string(space.getScore()));
        app.draw(score);
        app.display();
    }
}