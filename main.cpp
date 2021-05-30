#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "player.h"

int main(){

    sf::RenderWindow window(sf::VideoMode(640, 480), "Starman");

    sf::View view1(sf::FloatRect(0, 0, 640, 480));

    sf::Sprite background;
    sf::Texture background_texture;
    if(!background_texture.loadFromFile("images/map_background.png")){std::cout<<"Error"<<std::endl;}
    background.setTexture(background_texture);

    sf::Texture player_texture;
    if(!player_texture.loadFromFile("images/player.png")){std::cout<<"Error"<<std::endl;}

    //PLAYER(TEXTURE, POSITION X, POSITION Y)
    Player player(player_texture, {32, 448});

    sf::Clock clock;

    while (window.isOpen()){

        //EVENTS

        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        //LOGIC

        float elapsed = clock.restart().asSeconds();

        player.update(elapsed);

        //DISPLAY

        window.clear();

        window.draw(background);
        window.setView(view1);
        player.spawn(window);

        window.display();
    }

    return 0;
}
