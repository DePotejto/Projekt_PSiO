#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "platform.h"

int main(){

    sf::RenderWindow window(sf::VideoMode(640, 480), "Starman");
    sf::View view1(sf::FloatRect(0, 0, 640, 480));
    sf::View view2(sf::FloatRect(640, 480, 640, 480));

    sf::Sprite background;
    sf::Texture background_texture;
    if(!background_texture.loadFromFile("images/map_background.png")){std::cout<<"Error"<<std::endl;}
    background.setTexture(background_texture);

    sf::Texture player_texture;
    if(!player_texture.loadFromFile("images/player.png")){std::cout<<"Error"<<std::endl;}

    sf::Texture platform_texture;
    if(!platform_texture.loadFromFile("images/platform.png")){std::cout<<"Error"<<std::endl;}

    //PLAYER(TEXTURE, POSITION X, POSITION Y)
    Player player(player_texture, {32, 448});

    std::vector<std::unique_ptr<Platform>> platforms;
    platforms.emplace_back(std::make_unique<Platform>(platform_texture, 100, 442));
    platforms.emplace_back(std::make_unique<Platform>(platform_texture, 200, 350));
    platforms.emplace_back(std::make_unique<Platform>(platform_texture, 300, 250));
    platforms.emplace_back(std::make_unique<Platform>(platform_texture, 400, 150));
    platforms.emplace_back(std::make_unique<Platform>(platform_texture, 500, 150));

    sf::FloatRect next_player_position;

    bool pause=false;

    sf::Clock clock;

    while (window.isOpen()){

        //EVENTS

        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape){
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                    pause=true;
                    std::cout<<"PAUSED"<<std::endl;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                    pause=false;
                    std::cout<<"RESUMED"<<std::endl;
            }
        }

        //LOGIC

        float elapsed = clock.restart().asSeconds();

        //Collision with platforms
        for(auto &platform: platforms){
            sf::FloatRect player_bounds = player.getGlobalBounds();
            sf::FloatRect platform_bounds = platform->getGlobalBounds();

            next_player_position = player_bounds;
            next_player_position.left += player.get_velocity().x*elapsed;
            next_player_position.top += player.get_velocity().y*elapsed;

            if(platform_bounds.intersects(next_player_position)){
                //down
                if(player_bounds.top < platform_bounds.top&&
                        player_bounds.top + player_bounds.height < platform_bounds.top + platform_bounds.height&&
                        player_bounds.left < platform_bounds.left + platform_bounds.width&&
                        player_bounds.left + player_bounds.width > platform_bounds.left)
                {
                    player.set_velocity({player.get_velocity().x, 0});
                    player.can_jump=true;
                    player.setPosition(player_bounds.left, platform_bounds.top - player_bounds.height);
                }
                //up
                else if(player_bounds.top > platform_bounds.top&&
                        player_bounds.top + player_bounds.height > platform_bounds.top + platform_bounds.height&&
                        player_bounds.left < platform_bounds.left + platform_bounds.width&&
                        player_bounds.left + player_bounds.width > platform_bounds.left)
                {
                    player.set_velocity({player.get_velocity().x, 0});
                    player.setPosition(player_bounds.left, platform_bounds.top + platform_bounds.height);
                }
                //right
                if(player_bounds.left < platform_bounds.left&&
                        player_bounds.left + player_bounds.width < platform_bounds.left + platform_bounds.width&&
                        player_bounds.top < platform_bounds.top + platform_bounds.height&&
                        player_bounds.top + player_bounds.height - 2 > platform_bounds.top)
                {
                    player.setPosition(platform_bounds.left-player_bounds.width, player_bounds.top);
                }
                //left
                else if(player_bounds.left > platform_bounds.left&&
                        player_bounds.left + player_bounds.width > platform_bounds.left + platform_bounds.width&&
                        player_bounds.top < platform_bounds.top + platform_bounds.height&&
                        player_bounds.top + player_bounds.height -2 > platform_bounds.top)
                {
                    player.setPosition(platform_bounds.left+platform_bounds.width, player_bounds.top);
                }
            }


        }
        if(!pause){
            player.update(elapsed);
        }

        //DISPLAY

        window.clear();

        window.draw(background);
        window.setView(view1);

        for(auto& platform:platforms){
            window.draw(*platform);
        }

        window.draw(player);
        window.display();
    }

    return 0;
}
