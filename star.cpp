#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "star.h"

Star::Star(sf::Texture& star_texture_, float star_position_x_, float star_position_y_)
{
    setTexture(star_texture_);
    setPosition(star_position_x_, star_position_y_);
}
