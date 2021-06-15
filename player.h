#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
private:
    sf::Sprite player;
    sf::Vector2f player_position;
    sf::Vector2f velocity;
    float speed;

public:
    Player(sf::Texture&, sf::Vector2f);
    void update(float);
    sf::Vector2f get_velocity();
    void set_velocity(sf::Vector2f);
    bool can_jump;
};

#endif // PLAYER_H
