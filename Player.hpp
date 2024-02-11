//player.hpp
#ifndef PLAYER_hpp
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
    public:
    //X and Y Coordinate of the player
    Player(sf::Vector2f position=sf::Vector2f(0.0f,0.0f), sf::Vector2f size=sf::Vector2f(3.0f, 3.0f));

    void handleMovement();
    void drawPlayer(sf::RenderWindow& window);

    private:
    sf::RectangleShape shape;
    sf::Vector2f position;
};

#include "Player.cpp"
#endif