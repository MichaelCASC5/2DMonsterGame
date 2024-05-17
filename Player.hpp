#ifndef PLAYER_hpp
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
// #include <SFML/Audio.hpp>
#include "Laser.hpp"
#include "Map.hpp"

class Enemy;
class Map;

class Player
{
public:
    // X and Y coordinate of the Player
    Player(sf::Vector2f position = sf::Vector2f(0.0f, 0.0f));
    // laod sprite
    void loadSprite(const std::string &sprite);
    // handel movement
    void handleMovement(const sf::Time &deltaTime, const Map &map);
    // upade never used in code
    void update(const sf::Time &deltaTime, const Map &map, const Maze &maze);
    // player rotations
    void handleRotation();
    // size of sprite of player
    void setSize(float w, float h);
    // draw player on screen
    void drawPlayer(sf::RenderWindow &window);
    // check collision of player and enemy
    bool collidesWith(const Enemy &enemy) const;
    // plaeyr looses life if collides with enemy
    void loseLife();
    // get global bounds of player
    sf::FloatRect getGlobalBounds() const;
    // increase health of plaeyr if pikcup heart, never used
    void increaseHealth(int amount);
    // check if player is at goal of the maze
    bool isAtGoal(const std::pair<int, int> &goalPos) const;

    // set health of player to 3
    void setHealth(int health);
    // get health of player
    int getHealth() const;
    // get max lives
    static int getMaxLives();
    // roation of player
    double getRotation();

    // shoot lazer
    void shoot();
    // cooldown of laser
    void updateCooldown();
    // check if laser hits enemy then dissapears
    void updateLasers(sf::RenderWindow &window, std::vector<Enemy> &enemy);

    // collision with player and map
    bool isCollision(const Map &map);

    // positon of player
    sf::Vector2f getPosition() const;
    // set position of player
    void setPosition(sf::Vector2f newPosition);

    // if enemy collides with paleyr, temporary invisibility
    void makeInvinsible();
    // cehck if plaeyr is invinsible
    bool isInvinsible() const;
    // update invisibility
    void updateInvinsiblity(const sf::Time &deltaTime);

    // increase core fo player if htis enemy with laser
    void increaseScore(int points);
    // return score of player
    int getScore() const;

    // spped boost powerups
    void activateSpeedBoost();
    // rapid fire pwoerup
    void activateRapidFire();
    // double score powerup
    void activateDoubleScore();
    // update pwoerup of player
    void updatePowerUps(sf::Time deltaTime);
    // check if player reached exit
    bool reachedExit(const Map &map);

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2f normalize(const sf::Vector2f &v);
    float rotation;
    float speed = 200.0f;
    float movementAmount;

    static const int maxLives = 3;
    int health;
    std::vector<Laser> lasers;
    int lives;

    sf::Clock invisibleTimer;
    bool invinsible;
    const float invinsibleDuration = 2.0f;

    bool isCooldown;
    float cooldownDuration;
    sf::Clock cooldownTimer;

    int score;

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