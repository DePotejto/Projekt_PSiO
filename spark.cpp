#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "spark.h"

Spark::Spark(sf::Texture& spark_texture_, float spark_position_x_, float spark_position_y_)
{
    setTexture(spark_texture_);
    setPosition(spark_position_x_, spark_position_y_);
}
