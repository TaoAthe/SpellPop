#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class HUD {
public:
    HUD();
    void Initialize();
    void Render(sf::RenderWindow& window, int score, const std::string& buffer, int level = 1);

private:
    sf::Font m_font;
    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Text m_bufferText;
};
