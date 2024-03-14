#ifndef PLAYER_hpp
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "Laser.hpp"
#include "Map.hpp"


class Map;

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

        //collision detection BROKEN
        bool isCollision(Map& map_);
        
    private:
        sf::RectangleShape shape;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        float rotation;
        // sf::SoundBuffer laser;
        //sf::Sound laserSound;
        
        int health;
        std::vector<Laser> lasers;
};

#include "Player.cpp"
#endif
