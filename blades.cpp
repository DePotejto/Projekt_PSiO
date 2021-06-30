#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "blades.h"

Blades::Blades(sf::Texture& blade_texture_, float blade_position_x_, float blade_position_y_, float blade_velocity_x, float blade_velocity_y)
{
    frame = {0, 0, 32, 32};
    setTexture(blade_texture_);
    setTextureRect(frame);
    setPosition(blade_position_x_, blade_position_y_);
    velocity = {blade_velocity_x, blade_velocity_y};
    total_time = 0;
}
void Blades::update(float time)
{
    if(getPosition().y<=0||getPosition().y+getGlobalBounds().height>=480){
        velocity={velocity.x, -velocity.y};
    }

    total_time += time;

    if(total_time>=0.2){

        if(frame.left == 0){
            frame.left = 32;
        }
        else if(frame.left == 32){
            frame.left = 0;
        }

        setTextureRect(frame);

        total_time = 0;
    }

    move(velocity*time);
}
