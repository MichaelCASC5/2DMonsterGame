#include <math.h>

#include <cstdlib>
#include <iostream>

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
  life=1;
}

void Enemy::update(const sf::Time &deltaTime, const sf::Vector2f &playerPosition, const Map& map)
{
  //calculate vector direction pointing from enemy to player. Player-Enemy position
  sf::Vector2f direction = playerPosition - shape.getPosition();
  //distance length of vector of enemy and player
  float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  if(length>0){
    direction /= length;
  }
  shape.move(direction * speed * deltaTime.asSeconds());
  sf::Vector2f newPos= shape.getPosition()+(direction * speed * deltaTime.asSeconds());
  sf::Vector2f oldPos = shape.getPosition();
  //move enemy to player direction
  if(!isCollision(newPos, map)){
    shape.setPosition(newPos);
  }
  else{
    shape.setPosition(oldPos);
    movementDirection=-movementDirection;
   
  }
  
}

bool Enemy::isCollision(const sf::Vector2f& newPos, const Map& map){
  int mapX=static_cast<int>(position.x);
  int mapY=static_cast<int>(position.y);
  if(mapX > 0 && mapX < map.getMap().size() && mapY > 0 && mapY < map.getMap()[0].size()){
    return map.getMap()[mapX][mapY];
  }
  return true;
}

//enemy position
void Enemy::draw(sf::RenderWindow &window) const
{
  // Set the dimensions of the rectangle
  sf::RectangleShape drawShape(sf::Vector2f(50.f, 50.f));
  // std::cout << "over here" << std::endl;
  std::cout <<"Enemy Position "<< shape.getPosition().x << ", " << shape.getPosition().y << std::endl;
  // Set the position of the rectangle
  sf::Vector2f screenPos = {(float)shape.getPosition().x * 20.f + 250, (float)shape.getPosition().y * 20.f};
  drawShape.setPosition(screenPos);
  drawShape.setFillColor(sf::Color::Red);
  window.draw(drawShape);

  //Original Code
   window.draw(shape);
}

//global bounding box of enemy for collision of player
sf::FloatRect Enemy::getGlobalBounds() const { 
  return shape.getGlobalBounds(); 
}

void Enemy::hit(){
  if(life>0){
    life--;
  }
}

bool Enemy::isAlive() const {
  return life>0;
}

