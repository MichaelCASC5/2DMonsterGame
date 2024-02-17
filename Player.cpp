//Player class 

//constructor of Player class
Player::Player(sf::Vector2f position):position(position), rotation(2.0f){
    // //size of player shape 
    // shape.setSize(size);
    //set position of player
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    // //fill collor of player shape
    // shape.setFillColor(sf::Color::Red);
}

void Player::loadSprite(const std::string& textures){
    if(!texture.loadFromFile(textures)){
        std::cerr<<"Failed to load sprite"<<std::endl;
        return;
    }
    sprite.setTexture(texture);
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
sprite.setPosition(position);
}

void Player::handleRotation(){
    //rotate left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
        sprite.rotate(-rotation); 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
        sprite.rotate(rotation);
    }
}

//drawPlayer class 
void Player::drawPlayer(sf::RenderWindow& window){
    window.draw(sprite);
}