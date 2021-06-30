 #include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "player.h"

Player::Player(sf::Texture& Texture_, sf::Vector2f player_position_)
{
    frame = {0, 0, 32, 32};
    setTexture(Texture_);
    setTextureRect(frame);
    setPosition(player_position_);
    speed = 150;
    score = 0;
    level = 1;
    jump_height = 500;
    deaths = 0;
    invincibility = false;
    invincibility_countdown = 4;
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
        velocity.y=-jump_height;
    }

    if(getPosition().x<0.f){
       setPosition(0.f, getPosition().y);
    }
    if(getPosition().x+getGlobalBounds().width/2<640){
        level = 1;
    }
    if(getPosition().x+getGlobalBounds().width/2>640){
        level = 2;
    }
    if(getPosition().x+getGlobalBounds().width/2>1280){
        level = 3;
    }
    if(getPosition().x+getGlobalBounds().width>=1920){
        setPosition(1920-getGlobalBounds().width, getPosition().y);
    }
    if(getPosition().y+getGlobalBounds().height>480){
        set_velocity({get_velocity().x, 0});
        setPosition(getPosition().x, 480-getGlobalBounds().height);
        can_jump=true;
    }
    else{
        velocity.y += 1000*time;
    }

    if(velocity.y>0){can_jump=false;}

    if(invincibility){
        frame.left = 32;
        invincibility_countdown -= time;
    }
    if(invincibility_countdown <= 0){
        frame.left = 0;
        invincibility = false;
        invincibility_countdown = 4;
    }
    setTextureRect(frame);

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
