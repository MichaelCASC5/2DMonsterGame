#include <iostream>
#include <cstdlib>
#include <math.h>
#include "Enemy.hpp"

// Constructor of Enemy
Enemy::Enemy(const sf::Vector2f &position, const sf::Vector2f &size)
{
  speed = 30.0f;
  movementDirection = sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1);
  shape.setSize(size);
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(position);
  laserCooldown = 1.0f;
  life = 1;
}

void Enemy::update(const sf::Time &deltaTime, const sf::Vector2f &playerPosition, const Map &map)
{
  // calculate vector direction pointing from enemy to player. Player-Enemy position
  sf::Vector2f direction = playerPosition - shape.getPosition();
  // distance length of vector of enemy and player
  float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  if (length > 0)
  {
    direction /= length;
  }
  // gets new position based on current direction, position
  sf::Vector2f newPos = shape.getPosition() + (direction * speed * deltaTime.asSeconds());

  // convert positon to map coordinates using this scale measurement
  double newX = (newPos.x - 250.0) / 20.0;
  double newY = newPos.y / 20.0;

  // check if position of enemy is inside the map and not colliding with obstacle
  if (newX > 0 && newY > 0 && newX < map.getMap().size() && newY < map.getMap()[0].size() && !map.getMap()[newX][newY])
  {
    // update enemy position to the new position
    shape.setPosition(newPos);
  }
}

bool Enemy::isCollision(const sf::Vector2f &newPos, const Map &map)
{
  // convert position to map coordinates scale
  int mapX = static_cast<int>(position.x / 20);
  int mapY = static_cast<int>(position.y / 20);
  // check if position is in the map
  if (mapX > 0 && mapX < map.getMap().size() && mapY > 0 && mapY < map.getMap()[0].size())
  {
    // return true if there is a collision
    return map.getMap()[mapX][mapY];
  }
  return true;
}

// enemy position
void Enemy::draw(sf::RenderWindow &window) const
{
  // Set the dimensions of the rectangle
  sf::RectangleShape drawShape(sf::Vector2f(50.0f, 50.0f));
  // Set the position of the rectangle
  sf::Vector2f screenPos = {(float)shape.getPosition().x * 20.f + 250, (float)shape.getPosition().y * 20.f};
  drawShape.setPosition(screenPos);
  drawShape.setFillColor(sf::Color::Red);
  window.draw(drawShape);

  // Original Code
  window.draw(shape);
}

// global bounding box of enemy for collision of player
sf::FloatRect Enemy::getGlobalBounds() const
{
  return shape.getGlobalBounds();
}

// if player collides with enemy looses a heart
void Enemy::hit()
{
  if (life > 0)
  {
    life--;
  }
}

// checks if enemy is alive or not
bool Enemy::isAlive() const
{
  return life > 0;
}
