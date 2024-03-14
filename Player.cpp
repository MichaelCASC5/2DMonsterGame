
//Player class

//constructor of Player class
Player::Player (sf::Vector2f position):position (position), rotation (2.0f)
{

  //NEED HELP WITH SOUND ERROR

 // if(!laser.loadFromFile("blaster.wav")){
   // std::cerr<<"Failed to load laser sound"<<std::endl;
  //}
 // laserSound.setBuffer(laser);

  //size of player shape
  //set position of player
  sprite.setPosition (position);
  sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
}


//load sprite of charector
void Player::loadSprite (const std::string & textures)
{
  if (!texture.loadFromFile (textures))
	{
	  std::cerr << "Failed to load sprite" << std::endl;
	  return;
	}
  sprite.setTexture(texture);
}


void Player::handleMovement(){
    //Pi used for rotation
    float PI=3.14;

    //movement key pressed
    float movementAmount=5.0f;

    //check if W is pressed move shape up, decrease y coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
{
    position.y -= movementAmount * cos(rotation * (PI/180));
    position.x += movementAmount * sin(rotation * (PI/180));
    sprite.setRotation(270);
}
    //check if A is pressed move shape left, decrease x coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
{
    position.y -= movementAmount * sin(rotation * (PI/180));
    position.x -= movementAmount * cos(rotation * (PI/180));
    sprite.setRotation(180);
}
    //check if S is pressed move shape down, increase y coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
{
    position.y += movementAmount * cos(rotation * (PI/180));
    position.x -= movementAmount * sin(rotation * (PI/180));
    sprite.setRotation(90);
}
    //check if D is pressed move shape right, increasing x coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
{
    position.y += movementAmount * sin(rotation * (PI/180));
    position.x += movementAmount * cos(rotation * (PI/180));
    sprite.setRotation(0);
}
    //set position of player position
    sprite.setPosition(position);
}

void Player::handleRotation ()
{
  //rotate left
  if (sf::Keyboard::isKeyPressed (sf::Keyboard::C))
	{
	  sprite.rotate (-rotation);
	}
  //rotate right
  if (sf::Keyboard::isKeyPressed (sf::Keyboard::V))
	{
	  sprite.rotate (rotation);
	}
}

//set size of sprite charector
void Player::setSize (float w, float h)
{
  sf::FloatRect spriteSize = sprite.getGlobalBounds ();
  float scaleX = w / spriteSize.width;
  float scaleY = h / spriteSize.height;
  sprite.setScale (scaleX, scaleY);
}

//drawPlayer class
void Player::drawPlayer (sf::RenderWindow & window)
{
  window.draw (sprite);
}

//Set Health of Player
void Player::setHealth (int h)
{
  health = h;
}

//get Health of Player
int Player::getHealth () const
{
  return health;
}

//shoot lazer
void Player::shoot(){
  //loads laser starting with the player position with current rotation, moves in direction of player
  lasers.push_back(Laser(position, sprite.getRotation(), 10.0f)); 
 // laserSound.play();
}

//update laser path throughout the screen
void Player::updateLasers(sf::RenderWindow& window){
  for(size_t i=0; i<lasers.size();){ //go through all lasers
    lasers[i].Update(); //update position of laser

    //remove laser off screen
    if(lasers[i].offScreen(window)){
      lasers.erase(lasers.begin()+i);
    }
    else{
      i++; //move to next laser
    }
  }
  for(auto& laser:lasers){ //draw each laser on window
    laser.draw(window);
  }
}

bool Player::isCollision(Map& map) {
  if (position.x < map.getMap().size() && position.y < map.getMap().size())
    std::cout << map.getMap()[position.x][position.y] << std::endl;
  return false;
}