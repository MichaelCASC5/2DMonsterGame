#include "Lives.hpp"

Lives::Lives(int count, const std::string& heartImage):lives(count){
    if(!heartTexture.loadFromFile(heartImage)){
        throw std::runtime_error("Failed to load heart Image");
    }
    
    float scale=0.02f;
    
    for(int i=0; i<count;i++){
        sf::Sprite heart;
        heart.setTexture(heartTexture);
        heart.setScale(scale,scale);
        hearts.push_back(heart);
    }
}

void Lives::setPosition(float x, float y){
    float spacing=10.0f;
    for(size_t i=0; i<hearts.size(); i++){
        hearts[i].setPosition(x+i*(heartTexture.getSize().x * hearts[i].getScale().x + spacing), y);
    }
}

void Lives::draw(sf::RenderWindow& window){
    for(int i=0;i<lives;i++){
        window.draw(hearts[i]);
    }
}

float Lives::getHeartWidth() const {
    return heartTexture.getSize().x;
}
