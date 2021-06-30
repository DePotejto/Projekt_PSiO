#ifndef PICKUP_INVINCIBLE_H
#define PICKUP_INVINCIBLE_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Pickup_invincible : public sf::Sprite
{
private:
    float pickup_position_x, pickup_position_y;
public:
    Pickup_invincible(sf::Texture&, float, float);
};

#endif // PICKUP_INVINCIBLE_H
