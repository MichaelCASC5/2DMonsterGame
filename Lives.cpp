#include "Lives.hpp"
// constructor count total amount of lives, get the sprite
Lives::Lives(int count, const std::string &heartImage) : lives(count)
{
    if (!heartTexture.loadFromFile(heartImage))
    {
        throw std::runtime_error("Failed to load heart Image");
    }

    float scale = 0.07f;

    for (int i = 0; i < count; i++)
    {
        sf::Sprite heart;
        heart.setTexture(heartTexture);
        heart.setScale(scale, scale);
        hearts.push_back(heart);
    }
}
// se position of hearts
void Lives::setPosition(float x, float y)
{
    float spacing = 10.0f;
    for (size_t i = 0; i < hearts.size(); i++)
    {
        hearts[i].setPosition(x + i * (heartTexture.getSize().x * hearts[i].getScale().x + spacing), y);
    }
}
// draw hearts
void Lives::draw(sf::RenderWindow &window)
{
    // std::cout<<"Drawing Lives: "<<lives<<std::endl;
    for (int i = 0; i < lives; i++)
    {
        window.draw(hearts[i]);
    }
}
// resize the hearts if needed
float Lives::getHeartWidth() const
{
    return heartTexture.getSize().x;
}

// set number of lives
void Lives::setLives(int count)
{
   
    lives = count;
}
