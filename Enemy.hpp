#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    Enemy(const sf::Vector2f &position, const sf::Vector2f &size);
    void update(const sf::Time &deltaTime, const sf::Vector2f &playerPosition, const Map& map);
    void draw(sf::RenderWindow &window) const;
    sf::FloatRect getGlobalBounds() const;
    void shoot(const sf::Vector2f &targetPos);
    void updateLasers(sf::Time deltaTime, sf::RenderWindow &window);
    void hit();
    bool isAlive() const;
    bool isCollision(const sf::Vector2f& newPos, const Map& map);

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
