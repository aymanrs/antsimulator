#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "space.hpp"
#include "ant.hpp"
#include <iostream>

Grid space(W, H, home);

sf::Color pixelColor(Pixel s){
    switch(s.state){
    case PixelState::NONE:
        return sf::Color::Black;
        break;
    case PixelState::PHER:
        return sf::Color((s.redIntensity / maxSteps) * 255, 0, (s.blueIntensity / maxSteps) * 255);
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
    app.create(sf::VideoMode(W * S, H * S), "ant simulation", sf::Style::Titlebar | sf::Style::Close);
    Ant ants[numAnts];
    sf::Event e;
    sf::Font font;
    font.loadFromFile("res/Ubuntu-Regular.ttf");
    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color::White);
    bool simulationON = false;
    PixelState s = WALL;
    while(app.isOpen()){
        while(app.pollEvent(e)){
            if(e.type == sf::Event::Closed){
                app.close();
            } else if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left){
                Coords c = {e.mouseButton.x/S, e.mouseButton.y/S};
                for(int x = c.x - 2;x <= c.x+2;x++){
                    for(int y = c.y - 2;y <= c.y+2;y++){
                        if(space.inside({x, y}) && space.get({x, y}).state != HOME) {
                            space.set({x, y}, {s, 0, 0});
                        }
                    }
                }
            } else if(e.type == sf::Event::KeyPressed){
                switch(e.key.code){
                case sf::Keyboard::Space:
                    simulationON = !simulationON;
                    break;
                case sf::Keyboard::Num1:
                    s = NONE;
                    break;
                case sf::Keyboard::Num2:
                    s = WALL;
                    break;
                case sf::Keyboard::Num3:
                    s = FOOD;
                    break;
                default:
                    break;
                }
            }
        }
        app.clear();
        if(simulationON){
            for(Ant& a : ants){
                a.move();
            }
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
                    space.set({i, j}, {PixelState::PHER, std::max(0., p.redIntensity-evaporation), std::max(0., p.blueIntensity-evaporation)});
                    if(p.redIntensity-evaporation <= 0 && p.blueIntensity-evaporation <= 0) space.set({i, j}, Pixel());
                }
            }
        }
        score.setString(std::to_string(space.getScore()));
        app.draw(score);
        app.display();
    }
}