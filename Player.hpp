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
        void update(const sf::Time& deltaTime,const Map& map, const Maze& maze);
        void handleRotation();
        void setSize(float w, float h);
        void drawPlayer(sf::RenderWindow& window);
        bool collidesWith(const Enemy& enemy) const;
        void loseLife();
        sf::FloatRect getGlobalBounds() const;
        void increaseHealth(int amount);
        bool isAtGoal(const std::pair<int,int>& goalPos) const;

        //stats 
        void setHealth(int health);
        int getHealth() const;
        static int getMaxLives();
        double getRotation();

        //laser
        void shoot();
        void updateCooldown();
        void updateLasers(sf::RenderWindow& window, std::vector<Enemy>&enemies);


        bool isCollision(const Map& map);
        
        sf::Vector2f getPosition() const;
        void setPosition(sf::Vector2f newPosition);
        

        void makeInvinsible();
        bool isInvinsible() const;
        void updateInvinsiblity(const sf::Time& deltaTime);

        void increaseScore(int points);
        int getScore() const;

        //powerups
        void activateSpeedBoost();
        void activateRapidFire();
        void activateDoubleScore();

        void updatePowerUps(sf::Time deltaTime);

        bool reachedExit(const Map& map);


        
    private:
        sf::RectangleShape shape;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        sf::Vector2f normalize(const sf::Vector2f& v);
        float rotation;
        // sf::SoundBuffer laser;
        //sf::Sound laserSound;
        float speed=200.0f;
        float movementAmount;
        
        static const int maxLives=3;
        int health;
        std::vector<Laser> lasers;
        int lives;

        sf::Clock invisibleTimer;
        bool invinsible;
        const float invinsibleDuration=2.0f;

        bool isCooldown;
        float cooldownDuration;
        sf::Clock cooldownTimer;

        int score;

        //flag timers power-ups
        bool isSpeedBoost;
        bool isFireActive;
        bool isDoubleScore;
        sf::Clock powerUpTimer;

        float originalSpeed;
        float speedBoost;
        float OriginalFireRate;
        float rapidFireRate;
        bool doubleScoureActive;
        

};

#include "Player.cpp"
#endif