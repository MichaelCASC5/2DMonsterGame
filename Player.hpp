//player.hpp
#ifndef PLAYER_hpp
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
    public:
        //X and Y Coordinate of the player
        Player(sf::Vector2f position=sf::Vector2f(0.0f,0.0f));
        void loadSprite(const std::string& sprite);
        void handleMovement();
        void handleRotation();
        void setSize(float w, float h);
        void drawPlayer(sf::RenderWindow& window);

        //stats
        void setHealth(int health);
        int  getHealth() const;

    private:
        sf::RectangleShape shape;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        float rotation;

        //player stats
        int health;
      
};

#include "Player.cpp"
#endif