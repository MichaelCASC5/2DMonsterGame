#ifndef LIVES_HPP
#define LIVES_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Lives{
    public:
        Lives(int count, const std::string& heart);
        
        void setPosition(float x, float y);
        void draw(sf::RenderWindow& window);
        float getHeartWidth() const;
        
    private:
        std::vector<sf::Sprite> hearts;
        sf::Texture heartTexture;
        int lives;
};

#include "Lives.cpp"
#endif