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
  // shape.move(direction * speed * deltaTime.asSeconds());
  sf::Vector2f newPos = shape.getPosition() + (direction * speed * deltaTime.asSeconds());
  // sf::Vector2f oldPos = shape.getPosition();
  // move enemy to player direction

  // int mapX=static_cast<int>(newPos.x/20);
  // int mapY=static_cast<int>(newPos.y/20);
  // if(!map.isBlocked(mapX,mapY)){
  double newX = (newPos.x - 250.0) / 20.0;
  double newY = newPos.y / 20.0;
  if (newX > 0 && newY > 0 && newX < map.getMap().size() && newY < map.getMap()[0].size() && !map.getMap()[newX][newY]) {
    // std::cout << "newPos: " << (newPos.x - 250.0) / 20.0 << ", " << newPos.y / 20.0 << std::endl;
    shape.setPosition(newPos);
  }
  // else{
  // shape.setPosition(newPos);
  // movementDirection=-movementDirection;
  // shape.move(-direction*speed*deltaTime.asSeconds());

  //}
}

bool Enemy::isCollision(const sf::Vector2f &newPos, const Map &map)
{
  int mapX = static_cast<int>(position.x / 20);
  int mapY = static_cast<int>(position.y / 20);
  if (mapX > 0 && mapX < map.getMap().size() && mapY > 0 && mapY < map.getMap()[0].size())
  {
    return map.getMap()[mapX][mapY];
  }
  return true;
}

// enemy position
void Enemy::draw(sf::RenderWindow &window) const
{
  // Set the dimensions of the rectangle
  sf::RectangleShape drawShape(sf::Vector2f(50.0f, 50.0f));
  // std::cout << "over here" << std::endl;
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

void Enemy::hit()
{
  if (life > 0)
  {
    life--;
  }
}

bool Enemy::isAlive() const
{
  return life > 0;
}
