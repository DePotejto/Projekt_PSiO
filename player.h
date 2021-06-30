#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
private:
    sf::Vector2f player_position;
    sf::Vector2f velocity;
    float speed, jump_height, invincibility_countdown;
    sf::IntRect frame;
public:
    bool can_jump, invincibility;
    int score, level, deaths;
    Player(sf::Texture&, sf::Vector2f);
    void update(float);
    sf::Vector2f get_velocity();
    void set_velocity(sf::Vector2f); 
};

#endif // PLAYER_H
