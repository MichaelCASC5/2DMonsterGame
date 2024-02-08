//player.hpp
#ifndef PLAYER_hpp
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
    public:
    Player(sf::Vector2f size=sf::Vector2f(20.0f,20.0f));

    void handleMovement();
    void drawPlayer(sf::RenderWindow& window);

    private:
    sf::RectangleShape shape;
    float speed;
};

#endif