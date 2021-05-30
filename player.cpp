 #include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "player.h"

Player::Player(sf::Texture& Texture_, sf::Vector2f player_position_)
{
    player.setTexture(Texture_);
    player.setPosition(player_position_);
    speed = 200;
}

void Player::spawn(sf::RenderWindow &window)
{
    window.draw(player);
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

    if(player.getPosition().x<0.f){
        player.setPosition(0.f, player.getPosition().y);
    }
    if(player.getPosition().x+player.getGlobalBounds().width>640){
        player.setPosition(640-player.getGlobalBounds().width, player.getPosition().y);
    }
    if(player.getPosition().y+player.getGlobalBounds().height>480){
        player.setPosition(player.getPosition().x, 480-player.getGlobalBounds().height);
        can_jump=true;
    }
    else{
        velocity.y += 1000*time;
    }
    player.move(velocity*time);
}


