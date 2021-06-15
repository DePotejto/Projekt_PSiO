#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "platform.h"

Platform::Platform(sf::Texture& platform_texture_, float platform_position_x_, float platform_position_y_)
{
    setTexture(platform_texture_);
    setPosition(platform_position_x_, platform_position_y_);
}
