#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Bubble {
    std::string word;
    sf::Vector2f position;
    float speed;
    bool active;
    
    // Visuals
    sf::CircleShape shape;
    sf::Text textLabel;
    
    Bubble(const std::string& w, float x, float y, float s, const sf::Font& font);
    void Update(float dt);
    void Render(sf::RenderWindow& window);
};
