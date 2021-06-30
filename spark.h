#ifndef SPARK_H
#define SPARK_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Spark : public sf::Sprite
{
private:
    float spark_position_x, spark_position_y;
public:
    Spark(sf::Texture&, float, float);
};

#endif // SPARK_H
