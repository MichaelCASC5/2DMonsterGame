#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    Enemy(const sf::Vector2f &position, const sf::Vector2f &size);
    void update(const sf::Time &deltaTime, const sf::Vector2f &playerPosition);
    void draw(sf::RenderWindow &window) const;
    sf::FloatRect getGlobalBounds() const;
    void shoot(const sf::Vector2f &targetPos);
    void updateLasers(sf::Time deltaTime, sf::RenderWindow &window);

private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float speed;
    sf::Clock movementTimer;
    sf::Vector2f movementDirection;
    // std::vector<Laser> lasers;
    float laserCooldown;
    sf::Clock laserTimer;
};

#include "Enemy.cpp"
#endif
