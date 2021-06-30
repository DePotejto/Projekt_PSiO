#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "player.h"
#include "platform.h"
#include "spark.h"
#include "star.h"
#include "blades.h"
#include "pickup_invincible.h"

int main(){

    //CREATING WINDOW AND VIEWS
    sf::RenderWindow window(sf::VideoMode(640, 480), "Starman");
    window.setFramerateLimit(120);
    sf::View view1(sf::FloatRect(0, 0, 640, 480));
    sf::View view2(sf::FloatRect(640, 0, 640, 480));
    sf::View view3(sf::FloatRect(1280, 0, 640, 480));

    //CREATING BACKGROUND

    sf::Sprite background;
    sf::Texture background_texture;
    if(!background_texture.loadFromFile("images/map_background.png")){std::cout<<"Error"<<std::endl;}
    background.setTexture(background_texture);

    //LOADING TEXTURES

    sf::Texture platform_texture;
    if(!platform_texture.loadFromFile("images/platform.png")){std::cout<<"Error"<<std::endl;}

    sf::Texture spark_texture;
    if(!spark_texture.loadFromFile("images/spark.png")){std::cout<<"Error"<<std::endl;}

    sf::Texture star_texture;
    if(!star_texture.loadFromFile("images/star.png")){std::cout<<"Error"<<std::endl;}

    sf::Texture blade_texture;
    if(!blade_texture.loadFromFile("images/blade.png")){std::cout<<"Error"<<std::endl;}

    sf::Texture pickup_invincible_texture;
    if(!pickup_invincible_texture.loadFromFile("images/pickup_invincible.png")){std::cout<<"Error"<<std::endl;}

    sf::Texture player_texture;
    if(!player_texture.loadFromFile("images/player.png")){std::cout<<"Error"<<std::endl;}

    Player player(player_texture, {1, 447});

    std::vector<std::unique_ptr<Platform>> platforms;
    //LEVEL_1
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 100, 442));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 200, 350));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 300, 250));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 400, 150));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 530, 150));
    //LEVEL_2
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 928, 442));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 828, 342));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 728, 242));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 678, 142));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1028, 342));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1128, 242));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1178, 142));
    //LEVEL_3
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1850, 442));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1700, 350));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1550, 250));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1425, 175));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1300, 150));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1550, 100));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1700, 100));
        platforms.emplace_back(std::make_unique<Platform>(platform_texture, 1856, 75));

    std::vector<std::unique_ptr<Spark>> sparks;
    //LEVEL 1
        sparks.emplace_back(std::make_unique<Spark>(spark_texture, 116, 410));
        sparks.emplace_back(std::make_unique<Spark>(spark_texture, 546, 118));
    //LEVEL 2
        sparks.emplace_back(std::make_unique<Spark>(spark_texture, 944, 410));
        sparks.emplace_back(std::make_unique<Spark>(spark_texture, 694, 110));
        sparks.emplace_back(std::make_unique<Spark>(spark_texture, 1194, 110));
    //LEVEL 3
        sparks.emplace_back(std::make_unique<Spark>(spark_texture, 1316, 118));
        sparks.emplace_back(std::make_unique<Spark>(spark_texture, 1866, 410));

    std::vector<std::unique_ptr<Star>> stars;
        stars.emplace_back(std::make_unique<Star>(star_texture, 1872, 25));

    std::vector<std::unique_ptr<Pickup_invincible>> pickup_invincibles;
    //LEVEL 1
        pickup_invincibles.emplace_back(std::make_unique<Pickup_invincible>(pickup_invincible_texture, 25, 250));
    //LEVEL 2
        pickup_invincibles.emplace_back(std::make_unique<Pickup_invincible>(pickup_invincible_texture, 944, 200));
    //LEVEL 3
        pickup_invincibles.emplace_back(std::make_unique<Pickup_invincible>(pickup_invincible_texture, 1566, 218));

    std::vector<std::unique_ptr<Blades>> blades;
    //LEVEL 1
        blades.emplace_back(std::make_unique<Blades>(blade_texture, 266, 30, 0, -100));
    //LEVEL 2
        blades.emplace_back(std::make_unique<Blades>(blade_texture, 794, 30, 0, -150));
        blades.emplace_back(std::make_unique<Blades>(blade_texture, 1094, 418, 0, -150));
    //LEVEL 3
        blades.emplace_back(std::make_unique<Blades>(blade_texture, 1380, 30, 0, -200));
        blades.emplace_back(std::make_unique<Blades>(blade_texture, 1500, 418, 0, -200));
        blades.emplace_back(std::make_unique<Blades>(blade_texture, 1640, 30, 0, -200));
        blades.emplace_back(std::make_unique<Blades>(blade_texture, 1790, 418, 0, -200));

    //LOADING SOUNDS
        sf::SoundBuffer collect_buffer;
        if(!collect_buffer.loadFromFile("sounds/collect.wav")){std::cout<<"Error"<<std::endl;}
        sf::Sound collect;
        collect.setBuffer(collect_buffer);

    bool pause = false;

    sf::Clock clock;
    sf::Clock timer_clock;

    while (window.isOpen()){

        //EVENTS

        sf::Event event;
        while (window.pollEvent(event)){

            //CLOSING APP
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape){
                window.close();
            }

            //PAUSE
            if(event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::P && pause == false){
                    pause=true;
                    std::cout<<"PAUSED"<<std::endl;
                }
                else if (event.key.code == sf::Keyboard::P && pause == true){
                    pause=false;
                    std::cout<<"RESUMED"<<std::endl;
                }
            }

        }

        //LOGIC

        float elapsed = clock.restart().asSeconds();
        float timer = timer_clock.getElapsedTime().asSeconds();

        //Collision with platforms
        for(auto &platform: platforms){
            sf::FloatRect player_bounds = player.getGlobalBounds();
            sf::FloatRect platform_bounds = platform->getGlobalBounds();
            sf::FloatRect next_player_position;
            next_player_position = player_bounds;
            next_player_position.left += player.get_velocity().x*elapsed;
            next_player_position.top += player.get_velocity().y*elapsed;

            if(platform_bounds.intersects(next_player_position)){
                //down
                if(player_bounds.top < platform_bounds.top&&
                        player_bounds.top + player_bounds.height < platform_bounds.top + platform_bounds.height&&
                        player_bounds.left + 2< platform_bounds.left + platform_bounds.width&&
                        player_bounds.left + player_bounds.width - 2> platform_bounds.left)
                {
                    player.set_velocity({player.get_velocity().x, 0});
                    player.can_jump=true;
                    player.setPosition(player_bounds.left, platform_bounds.top - player_bounds.height);
                }
                //up
                else if(player_bounds.top > platform_bounds.top&&
                        player_bounds.top + player_bounds.height > platform_bounds.top + platform_bounds.height&&
                        player_bounds.left + 2< platform_bounds.left + platform_bounds.width&&
                        player_bounds.left + player_bounds.width - 2> platform_bounds.left)
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
                        player_bounds.top + player_bounds.height - 2 > platform_bounds.top)
                {
                    player.setPosition(platform_bounds.left+platform_bounds.width, player_bounds.top);
                }
            }
        }

        //Collision with sparks
        for(size_t i = 0; i<sparks.size(); i++){
            if(sparks[i]->getGlobalBounds().intersects(player.getGlobalBounds())){
                sparks.erase(std::remove(sparks.begin(), sparks.end(), sparks[i]), sparks.end());
                collect.play();
                player.score += 3;
            }
        }

        //Collision with pickup_invincible
        for(size_t i = 0; i<pickup_invincibles.size(); i++){
            if(pickup_invincibles[i]->getGlobalBounds().intersects(player.getGlobalBounds())){
                pickup_invincibles.erase(std::remove(pickup_invincibles.begin(), pickup_invincibles.end(), pickup_invincibles[i]), pickup_invincibles.end());
                player.invincibility = true;
            }
        }

        //Collision with star - game finish
        for(auto &star: stars){
            if(star->getGlobalBounds().intersects(player.getGlobalBounds())){
                window.close();
                std::cout<<"Thank you for playing, your final score is: "<<player.score<<"!"<<std::endl<<"It took you "
                <<timer<<" seconds to finish the game."<<std::endl;
                if(player.deaths == 1){
                    std::cout<<"You died "<<player.deaths<<" time."<<std::endl;}
                else{
                    std::cout<<"You died "<<player.deaths<<" times."<<std::endl;}
            }
        }

        //Collision with blades - death
        for(auto &blade: blades){
            if(blade->getGlobalBounds().intersects(player.getGlobalBounds()) && player.invincibility == false){
                player.setPosition(1, 447);
                player.set_velocity({0, 0});
                player.deaths++;
                player.score--;
            }
        }

        if(!pause){player.update(elapsed);}

        //DISPLAY
        window.clear();
        window.draw(background);

        //Menaging levels
        if(player.level == 1){window.setView(view1);}
        else if(player.level == 2){window.setView(view2);}
        else if(player.level == 3){window.setView(view3);}

        //Drawing player and objects
        for(auto& platform:platforms){
            window.draw(*platform);
        }
        for(auto& spark:sparks){
            window.draw(*spark);
        }
        for(auto& star:stars){
            window.draw(*star);
        }
        for(auto& pickup_invincible:pickup_invincibles){
            window.draw(*pickup_invincible);
        }
        for(auto& blade:blades){
            window.draw(*blade);
            if(!pause){
            blade->update(elapsed);}
        }
        window.draw(player);

        window.display();
    }

    return 0;
}
