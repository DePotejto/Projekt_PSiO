 #include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "player.h"

Player::Player(sf::Texture& Texture_, sf::Vector2f player_position_)
{
    setTexture(Texture_);
    setPosition(player_position_);
    speed = 150;
}

void Player::update(float time)
{
    velocity.x=0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        velocity.x -= speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        velocity.x += speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && can_jump){
        can_jump=false;
        velocity.y=-500;
    }

    if(getPosition().x<0.f){
       setPosition(0.f, getPosition().y);
    }
    if(getPosition().x+getGlobalBounds().width>640){
        setPosition(640-getGlobalBounds().width, getPosition().y);
    }
    if(getPosition().y+getGlobalBounds().height>480){
        setPosition(getPosition().x, 480-getGlobalBounds().height);
        can_jump=true;
    }
    else{
        velocity.y += 1000*time;
    }
    move(velocity*time);
}
sf::Vector2f Player::get_velocity()
{
    return velocity;
}
void Player::set_velocity(sf::Vector2f velocity_)
{
    velocity.x=velocity_.x;
    velocity.y=velocity_.y;
}
