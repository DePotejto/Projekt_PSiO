#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Platform : public sf::Sprite
{
private:
    sf::Sprite platform;
    float platform_position_x, platform_position_y;
public:
    Platform(sf::Texture&, float, float);
    //void draw(sf::RenderWindow&);
    void update(float);
};

#endif // PLATFORM_H
