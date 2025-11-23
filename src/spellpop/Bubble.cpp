#include "Bubble.h"

Bubble::Bubble(const std::string& w, float x, float y, float s, const sf::Font& font)
    : word(w), position(x, y), speed(s), active(true)
{
    shape.setRadius(40.f);
    shape.setOrigin(40.f, 40.f);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(100, 100, 250, 200));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.f);

    textLabel.setFont(font);
    textLabel.setString(word);
    textLabel.setCharacterSize(14);
    textLabel.setFillColor(sf::Color::White);
    
    // Center text
    sf::FloatRect textRect = textLabel.getLocalBounds();
    textLabel.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
    textLabel.setPosition(position);
}

void Bubble::Update(float dt) {
    if (!active) return;
    
    position.y -= speed * dt;
    shape.setPosition(position);
    textLabel.setPosition(position);
    
    if (position.y < -50.f) {
        active = false;
    }
}

void Bubble::Render(sf::RenderWindow& window) {
    if (!active) return;
    window.draw(shape);
    window.draw(textLabel);
}
