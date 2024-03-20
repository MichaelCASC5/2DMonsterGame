#include <math.h>

#include <cstdlib>
#include <iostream>

#include "Enemy.hpp"

// Constructor of Enemy
Enemy::Enemy(const sf::Vector2f &position, const sf::Vector2f &size)
{
  speed = 50.0f;
  movementDirection = sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1);
  shape.setSize(size);
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(position);
  laserCooldown = 1.0f;
}

void Enemy::update(const sf::Time &deltaTime, const sf::Vector2f &playerPosition)
{
  //calculate vector direction pointing from enemy to player. Player-Enemy position
  sf::Vector2f direction = playerPosition - shape.getPosition();
  //distance length of vector of enemy and player
  float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  direction /= length;
  //move enemy to player direction
  shape.move(direction * speed * deltaTime.asSeconds());
}

//enemy position
void Enemy::draw(sf::RenderWindow &window) const
{
  window.draw(shape);
}

//global bounding box of enemy for collision of player
sf::FloatRect Enemy::getGlobalBounds() const { 
  return shape.getGlobalBounds(); 
}

// void Enemy::shoot(const sf::Vector2f& targetPos) {
//   if(lasers.size()<5 &&
//   laserTimer.getElapsedTime().asSeconds()>=laserCooldown){
//     sf::Vector2f direction = targetPos-shape.getPosition();
//     float angle=std::atan2(direction.y, direction.x)*180/3.14159f;

//     lasers.push_back(Laser(shape.getPosition(), angle, 1.0));
//     laserTimer.restart();
//   }
// }

// // update laser path throughout the screen
// void Enemy::updateLasers(sf::Time deltaTime, sf::RenderWindow& window) {
//   for (size_t i = 0; i < lasers.size();) {  // go through all lasers
//     lasers[i].Update();                     // update position of laser

//     // remove laser off screen
//     if (lasers[i].offScreen(window)) {
//       lasers.erase(lasers.begin() + i);
//     } else {
//       i++;  // move to next laser
//     }
//   }
//   for (auto& laser : lasers) {  // draw each laser on window
//     laser.draw(window);
//   }
// }