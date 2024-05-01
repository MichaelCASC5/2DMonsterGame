#include "Enemy.hpp"
// Player class

// constructor of Player class
Player::Player(sf::Vector2f position) : position(position), rotation(2.0f), health(3), isCooldown(false), cooldownDuration(0.03f), score(0), originalSpeed(4.0f), speedBoost(300.0f), OriginalFireRate(1.0f), rapidFireRate(1.0f), doubleScoureActive(false), speed(originalSpeed)
{
  sprite.setPosition(position);
  sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

  // std::cout << "Initial Player Health" << health << std::endl;
}

// load sprite of charector
void Player::loadSprite(const std::string &textures)
{
  if (!texture.loadFromFile(textures))
  {
    std::cerr << "Failed to load sprite" << std::endl;
    return;
  }
  sprite.setTexture(texture);
}

void Player::handleMovement(const sf::Time &deltaTime, const Map &map)
{
  // Pi used for rotation
  float PI = 3.14;

  // movement speed
  float movementAmount = 20.0f;
  // movement speed
  //  float movementAmount=30.0f;

  // 2D Vector for movement direction
  sf::Vector2f movement(0.0f, 0.0f);

  // check if W is pressed move shape up, decrease y coordinate
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    movement.y -= movementAmount;
    // position.y -= movementAmount * cos(rotation * (PI/180));
    // position.x += movementAmount * sin(rotation * (PI/180));
  }
  // check if A is pressed move shape left, decrease x coordinate
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    movement.x -= 1.0f;
    // position.y -= movementAmount * sin(rotation * (PI/180));
    // position.x -= movementAmount * cos(rotation * (PI/180));
  }
  // check if S is pressed move shape down, increase y coordinate
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    movement.y += 1.0f;
    // position.y += movementAmount * cos(rotation * (PI/180));
    // position.x -= movementAmount * sin(rotation * (PI/180));
  }
  // check if D is pressed move shape right, increasing x coordinate
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    movement.x += 1.0f;
    // position.y += movementAmount * sin(rotation * (PI/180));
    // position.x += movementAmount * cos(rotation * (PI/180));
  }
  // normalize movement vector. consistent movement 1.0f all directions
  if (movement.x != 0.0f || movement.y != 0.0f)
  {
    movement /= std::sqrt(movement.x * movement.x + movement.y * movement.y);
  }

  // update player position on movement vector, movement amount,time delta
  sf::Vector2f newPosition = position + movement * movementAmount * deltaTime.asSeconds();

  // if (isCollision(map, newPosition))
  // {
  // position = newPosition;
  // }

  /**
   * HARD CODED TEMPORARILY PLS FIX
   */
  // sf::Vector2f savePosition = position;
  double tempPosX = position.x;
  double tempPosY = position.y;
  position = newPosition;

  if (isCollision(map))
  {
    position.x = tempPosX;
    position.y = tempPosY;
    // std::cout << "if col ran" << std::endl;
  }

  // set position of player position
  sprite.setPosition(position);
}

void Player::handleRotation()
{
  // rotate left
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
  {
    sprite.rotate(-rotation);
  }
  // rotate right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
  {
    sprite.rotate(rotation);
  }
}

// set size of sprite charector
void Player::setSize(float w, float h)
{
  sf::FloatRect spriteSize = sprite.getGlobalBounds();
  float scaleX = w / spriteSize.width;
  float scaleY = h / spriteSize.height;
  sprite.setScale(scaleX, scaleY);
}

// drawPlayer class
void Player::drawPlayer(sf::RenderWindow &window)
{

  // Set the dimensions of the rectangle
  sf::RectangleShape shape(sf::Vector2f(20.f, 20.f));

  // std::cout << "over here" << std::endl;
  std::cout <<"Player Position "<< position.x << ", " << position.y << std::endl;

  // Set the position of the rectangle
  sf::Vector2f screenPos = {(float)position.x * 20.f + 250, (float)position.y * 20.f};
  sprite.setPosition(screenPos);

  // Set the color of the rectangle
  // sprite.setFillColor(sf::Color::Blue);

  // Rotate
  //  shape.rotate((float) angle_ * (180 / PI));

  // Draw the rectangle to the target window
  window.draw(sprite);
  // window.draw(sprite);
}

// Set Health of Player
void Player::setHealth(int h) { health = h; }

// get Health of Player
int Player::getHealth() const { return health; }

int Player::getMaxLives() { return maxLives; }

// shoot lazer
void Player::shoot()
{
  if (!isCooldown)
  {
    float playerRotation = sprite.getRotation();
    sf::Vector2f playerPos = {(float)position.x *20.0f+250, (float)position.y*20.0f};

    std::cout << "Player position: " << playerPos.x << ", " << playerPos.y << std::endl;
    // loads laser starting with the player position with current rotation, moves
    // in direction of player
    lasers.push_back(Laser(playerPos, playerRotation, 10.0f));

    isCooldown = true;
    cooldownTimer.restart();
  }
 // else if (cooldownTimer.getElapsedTime().asSeconds() > cooldownDuration)
  //{
   // isCooldown = false;
 // }
}

void Player::updateCooldown()
{
  if (isCooldown)
  {
    if (cooldownTimer.getElapsedTime().asSeconds() > cooldownDuration)
    {
      isCooldown = false;
    }
  }
}

// void Player::increaseScore(int points){
//   score+=points;
// }

int Player::getScore() const
{
  return score;
}

// update laser path throughout the screen
void Player::updateLasers(sf::RenderWindow &window, std::vector<Enemy> &enemies)
{
  sf::Vector2f playerPos = {(float)position.x*20.0f+250, (float)position.y*20.0f};
  for (size_t i = 0; i < lasers.size();) // go through all lasers
  {
    lasers[i].Update(); // update position of laser

    bool laserRemoved = false;

    if (lasers[i].offScreen(window))
    {
      lasers.erase(lasers.begin() + i);
      laserRemoved = true;
    }

    else
    {
      for (auto &enemy : enemies)
      {
        if (lasers[i].getBounds().intersects(enemy.getGlobalBounds()) && enemy.isAlive())
        {
          enemy.hit();
          lasers.erase(lasers.begin() + i);
          laserRemoved = true;
          break;
        }
      }
    }

    if (!laserRemoved)
    {
      ++i;
    }
  }

  for (auto &laser : lasers)
  { // draw each laser on window
    laser.draw(window);
  }

  //   // remove laser off screen
  //   if (lasers[i].offScreen(window))
  //   {
  //     lasers.erase(lasers.begin() + i);
  //   }
  //   else
  //   {
  //     i++; // move to next laser
  //   }
  // }
}

bool Player::isCollision(const Map &map)
{
  bool output = true;
  //std::cout << position.x << ", " << position.y << std::endl;
  if (position.x > 0 && position.x < map.getMap().size() && position.y > 0 && position.y < map.getMap()[0].size())
  {
  //  std::cout << "if " << std::endl;
    std::cout << map.getMap()[(int)position.x][(int)position.y] << std::endl;
    output = map.getMap()[(int)position.x][(int)position.y];
  }
  return output;
  /*
  // scale to render map
  const float scalex = 20.0f;
  const float offsetx = 250.0f;
  const float scaley = 20.0f;

  // bounding box of player
  sf::FloatRect playerBounds = sprite.getGlobalBounds();

  // calculate position of four corners of player to detect collision all sides.
  std::vector<sf::Vector2f> check = {
      {newPos.x - playerBounds.width / 2, newPos.y - playerBounds.height / 2},
      {newPos.x + playerBounds.width / 2, newPos.y - playerBounds.height / 2},
      {newPos.x - playerBounds.width / 2, newPos.y + playerBounds.height / 2},
      {newPos.x + playerBounds.width / 2, newPos.y + playerBounds.height / 2}};

  // cehck each corner for collision
  for (const auto &point : check)
  {
    // player position to map coordinate scale
    int x = static_cast<int>((point.x - offsetx) / scalex);
    int y = static_cast<int>(point.y / scaley);

    // check for collision, if its outszie map boundry or if it a wall(true)
    if (x < 0 || y < 0 || x >= map.getMap().size() ||
        y >= map.getMap()[0].size() || map.getMap()[x][y])
    {
      return true; // collision detected
    }
  }
  return false; // no collisions detected*/
}

// player current position
sf::Vector2f Player::getPosition() const
{
  return sprite.getPosition();
}

void Player::setPosition(sf::Vector2f newPosition){
  position=newPosition;
  sprite.setPosition(position.x*20+250,position.y*20);
}

// check if collides with enemy bounding box
bool Player::collidesWith(const Enemy &enemy) const
{
  return sprite.getGlobalBounds().intersects(enemy.getGlobalBounds());
}

// Player looses life if touches enemy
void Player::loseLife()
{
  if (health > 0)
  {
    health--;
    makeInvinsible();
   // std::cout << "Player lost life. Remaining lives: " << health << std::endl;
  }
}

sf::FloatRect Player::getGlobalBounds() const
{
  return sprite.getGlobalBounds();
}

void Player::increaseHealth(int amount)
{
  health += amount;
  if (health > maxLives)
  {
    health = maxLives;
  }
}

// if player looses life wait time then can loose again
void Player::makeInvinsible()
{
  invinsible = true;
  invisibleTimer.restart();
}

// time for player to be invincible
bool Player::isInvinsible() const
{
  return invinsible;
}

// check if invinsibility is done
void Player::updateInvinsiblity(const sf::Time &deltaTime)
{
  if (invinsible && invisibleTimer.getElapsedTime().asSeconds() > invinsibleDuration)
  {
    invinsible = false;
  }
}

void Player::activateSpeedBoost()
{
  speed = speedBoost;
  isSpeedBoost = true;
  powerUpTimer.restart();
}

void Player::activateRapidFire()
{
  cooldownDuration = rapidFireRate;
  isFireActive = true;
  powerUpTimer.restart();
}

void Player::activateDoubleScore()
{
  doubleScoureActive = true;
  std::cout << "Double Score" << std::endl;
  powerUpTimer.restart();
}

void Player::updatePowerUps(sf::Time deltaTime)
{
  if (isSpeedBoost || isFireActive || doubleScoureActive)
  {
    if (powerUpTimer.getElapsedTime().asSeconds() > 5.0f)
    {
      speed = originalSpeed;
      OriginalFireRate = 1.0f;
      doubleScoureActive = false;
      isSpeedBoost = false;
      isFireActive = false;
    }
  }
}

void Player::increaseScore(int points)
{
  if (doubleScoureActive)
  {
    std::cout << "double Score! Adding" << 2 * points << "points" << std::endl;
    score += 2 * points;
  }
  else
  {
    std::cout << "Regular score" << points << "points" << std::endl;
    score += points;
  }
}

bool Player::reachedExit(const Map& map){
  sf::Vector2f exitPos=map.getExit();
  sf::Vector2f playerPos=getPosition();
  if(fabs(playerPos.x-(exitPos.x*20+250))<20 && fabs(playerPos.y-(exitPos.y*20))<20){
    return true;
  }
  return false;
}