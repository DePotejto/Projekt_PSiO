#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "pickup_invincible.h"

Pickup_invincible::Pickup_invincible(sf::Texture& pickup_texture_, float pickup_position_x_, float pickup_position_y_)
{
    setTexture(pickup_texture_);
    setPosition(pickup_position_x_, pickup_position_y_);
}
