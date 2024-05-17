#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    // constructor for Enemy, initial position, size of enemy
    Enemy(const sf::Vector2f &position, const sf::Vector2f &size);
    // update enemy, time elapsed since last update, player position, map for collision
    void update(const sf::Time &deltaTime, const sf::Vector2f &playerPosition, const Map &map);
    // draw enemy on screen
    void draw(sf::RenderWindow &window) const;
    // get bounding box of enemy
    sf::FloatRect getGlobalBounds() const;
    // enemy hsoots lazer, never used in game
    void shoot(const sf::Vector2f &targetPos);
    // update lasers
    void updateLasers(sf::Time deltaTime, sf::RenderWindow &window);
    // reduce enemy liffe if hit
    void hit();
    // check if enemy is alive
    bool isAlive() const;
    // check fro collision with map
    bool isCollision(const sf::Vector2f &newPos, const Map &map);

private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float speed;
    sf::Clock movementTimer;
    sf::Vector2f movementDirection;
    std::vector<Laser> lasers;
    float laserCooldown;
    sf::Clock laserTimer;
    int life;
};

#include "Enemy.cpp"
#endif
