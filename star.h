#ifndef STAR_H
#define STAR_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Star : public sf::Sprite
{
private:
    float star_position_x, star_position_y;
public:
    Star(sf::Texture&, float, float);
};

#endif // STAR_H
