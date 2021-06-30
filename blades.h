#ifndef BLADES_H
#define BLADES_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Blades : public sf::Sprite
{
private:
    sf::Vector2f velocity;
    float blade_position_x, blade_position_y, total_time;
    sf::IntRect frame;
public:
    Blades(sf::Texture&, float, float, float, float);
    void update(float);
};

#endif // BLADES_H
