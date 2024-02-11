//Player class 

//constructor of Player class
Player::Player(sf::Vector2f position, sf::Vector2f size):position(position){
    //size of player shape 
    shape.setSize(size);
    //set position of player
    shape.setPosition(position);
    //fill collor of player shape
    shape.setFillColor(sf::Color::Red);
}

//handle movement fucntion
void Player::handleMovement(){

    //movement key pressed
    float movementAmount=10.0f;

    //check if W is pressed move shape up, decrease y coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
{
    position.y-=movementAmount;
}
    //check if A is pressed move shape left, decrease x coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
{
    position.x-=movementAmount;
}
    //check if S is pressed move shape down, increase y coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
{
    position.y+=movementAmount;
}
    //check if D is pressed move shape right, increasing x coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
{
   position.x+=movementAmount;
}
//set position of player position
shape.setPosition(position);
}

//drawPlayer class 
void Player::drawPlayer(sf::RenderWindow& window){
    window.draw(shape);
}