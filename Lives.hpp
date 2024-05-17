#ifndef LIVES_HPP
#define LIVES_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Lives
{
public:
    // Lives constructor count, heart image
    Lives(int count, const std::string &heart);

    // set pisition, draw, resize fucntions
    void setPosition(float x, float y);
    // draw function of lives
    void draw(sf::RenderWindow &window);
    // return the hearts size
    float getHeartWidth() const;
    // set lives
    void setLives(int count);

private:
    std::vector<sf::Sprite> hearts;
    sf::Texture heartTexture;
    int lives;
};

#include "Lives.cpp"
#endif
