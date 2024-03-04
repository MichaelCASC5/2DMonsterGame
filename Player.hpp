#ifndef PLAYER_hpp
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Laser.hpp"

class Player{
    public:
        //X and Y coordinate of the Player
        Player(sf::Vector2f position=sf::Vector2f(0.0f,0.0f));
        void loadSprite(const std::string& sprite);
        void handleMovement();
        void handleRotation();
        void setSize(float w, float h);
        void drawPlayer(sf::RenderWindow& window);
        
        //stats 
        void setHealth(int health);
        int getHealth() const;

        //laser
        void shoot();
        void updateLasers(sf::RenderWindow& window);
        
    private:
        sf::RectangleShape shape;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        float rotation;
        
        int health;
        std::vector<Laser> lasers;
};

#include "Player.cpp"
#endif