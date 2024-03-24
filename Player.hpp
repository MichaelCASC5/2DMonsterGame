#ifndef PLAYER_hpp
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
//#include <SFML/Audio.hpp>
#include "Laser.hpp"
#include "Map.hpp"

class Enemy;
class Map;

class Player{
    public:
        //X and Y coordinate of the Player
        Player(sf::Vector2f position=sf::Vector2f(0.0f,0.0f));
        void loadSprite(const std::string& sprite);
        void handleMovement(const sf::Time& deltaTime,const Map& map);
        void handleRotation();
        void setSize(float w, float h);
        void drawPlayer(sf::RenderWindow& window);
        bool collidesWith(const Enemy& enemy) const;
        void loseLife();
        
        //stats 
        void setHealth(int health);
        int getHealth() const;

        //laser
        void shoot();
        void updateLasers(sf::RenderWindow& window, std::vector<Enemy>&enemies);


        bool isCollision(const Map& map, const sf::Vector2f& newPos) const;
        
        sf::Vector2f getPosition() const;

        void makeInvinsible();
        bool isInvinsible() const;
        void updateInvinsiblity(const sf::Time& deltaTime);

        
    private:
        sf::RectangleShape shape;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        sf::Vector2f normalize(const sf::Vector2f& v);
        float rotation;
        // sf::SoundBuffer laser;
        //sf::Sound laserSound;
        
        int health;
        std::vector<Laser> lasers;
        int lives;

        sf::Clock invisibleTimer;
        bool invinsible;
        const float invinsibleDuration=2.0f;
};

#include "Player.cpp"
#endif
