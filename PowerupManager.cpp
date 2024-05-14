// #include "PowerupManager.hpp"

// PowerupManager::PowerupManager(){}

// void PowerupManager::generatePowerUps(const Map& map){
//     // scaling factor to the map
//     const float scales = 20.0f;
//     // position shifting by 250 x-axis
//     const sf::Vector2f offsets = {250.0f, 0.0f};
//     // powerUpTypes, positions in the game
//     std::vector<std::pair<sf::Vector2f, PowerUpType>> powerUpInfo = {
//         {{7.0f, 8.0f}, PowerUpType::SpeedBoost},
//         {{10.0f, 8.0f}, PowerUpType::RapidFire},
//         {{15.0f, 8.0f}, PowerUpType::DoubleScore}};

//     // vector of open spaces in the map
//     std::vector<sf::Vector2f> openSpaces;
//     // get open spaces from map, adjust coordinates by scale, offset
//     for (auto &vertex : map.getOpenSpaces())
//     {
//         openSpaces.emplace_back(vertex.getX() * scales + offsets.x, vertex.getY() * scales + offsets.y);
//     }
//     // loop through each power up type and position and place them in game
//     for (const auto &[pos, type] : powerUpInfo)
//     {
//         // random open location for placing powerup
//         sf::Vector2f powerUpLocation = map.selectSpawnLocation(openSpaces);
//         // create a powerup at selected location and add it to vector
//         powerUps.push_back(PowerUp(type, powerUpLocation));
//     }
// }

// void powerUpManager::draw(sf::RenderWindow& window){
//     for(auto& PowerUp: PowerUps){
//         PowerUp.draw(window);
//     }
// }

// std::vector<PowerUp>& PowerupManager::getPowerUps(){
//     return powerUps;
// }