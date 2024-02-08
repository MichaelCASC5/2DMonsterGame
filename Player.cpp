//Player class 

//constructor of Player class
Player::Player(sf::Vector2f size):speed(1.0f){
    //size of player shape 
    shape.setSize(size);
    //fill collor of player shape
    shape.setFillColor(sf::Color::Red);
}

//handle movement fucntion
void Player::handleMovement(){
    //check if W is pressed move shape up, decrease y coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
{
    shape.move(0,-speed);
}
    //check if A is pressed move shape left, decrease x coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
{
    shape.move(-speed,0);
}
    //check if S is pressed move shape down, increase y coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
{
    shape.move(0,speed);
}
    //check if D is pressed move shape right, increasing x coordinate
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
{
    shape.move(speed,0);
}
}

//drawPlayer class 
void Player::drawPlayer(sf::RenderWindow& window){
    window.draw(shape);
}