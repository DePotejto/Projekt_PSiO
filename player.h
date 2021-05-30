#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Sprite player;
    sf::Vector2f player_position;
    sf::Vector2f velocity;
    float speed;
    bool can_jump;
public:
    Player(sf::Texture&, sf::Vector2f);
    void spawn(sf::RenderWindow&);
    void update(float);
};

#endif // PLAYER_H
