//Player class

//constructor of Player class
Player::Player (sf::Vector2f position):position (position), rotation (2.0f)
{
  //size of player shape
  //set position of player
  sprite.setPosition (position);
  sprite.setOrigin (sprite.getLocalBounds ().width / 2,
					sprite.getLocalBounds ().height / 2);
}

void Player::loadSprite (const std::string & textures)
{
  if (!texture.loadFromFile (textures))
	{
	  std::cerr << "Failed to load sprite" << std::endl;
	  return;
	}
  sprite.setTexture (texture);
}

//handle movement function
void Player::handleMovement ()
{
  //movement key pressed
  float movementAmount = 5.0f;

  //check if W is pressed move shape up, decrease y coordiante
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
	  position.y -= movementAmount;
	}

  //check if A is pressed move shape left, decrease X coordiante
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
	  position.x -= movementAmount;
	}

  //check if S is pressed move shape down, increase y coordiante
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
	  position.y += movementAmount;
	}

  //check if D is pressed move shape Right, increaseing X coordiante
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
	  position.x += movementAmount;
	}
  sprite.setPosition (position);
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

void Player::setHealth (int h)
{
  health = h;
}

int Player::getHealth () const
{
  return health;
}