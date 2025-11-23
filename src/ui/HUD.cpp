#include "HUD.h"
#include <iostream>

HUD::HUD() {}

void HUD::Initialize() {
    if (!m_font.loadFromFile("assets/fonts/arial.ttf")) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }
    }

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::Yellow);
    m_scoreText.setPosition(20, 20);

    m_levelText.setFont(m_font);
    m_levelText.setCharacterSize(24);
    m_levelText.setFillColor(sf::Color::Cyan);
    m_levelText.setPosition(20, 50);

    m_bufferText.setFont(m_font);
    m_bufferText.setCharacterSize(30);
    m_bufferText.setFillColor(sf::Color::Green);
    m_bufferText.setPosition(20, 650);
}

void HUD::Render(sf::RenderWindow& window, int score, const std::string& buffer, int level) {
    m_scoreText.setString("Score: " + std::to_string(score));
    window.draw(m_scoreText);

    m_levelText.setString("Level: " + std::to_string(level));
    window.draw(m_levelText);

    m_bufferText.setString("Input: " + buffer + "_");
    window.draw(m_bufferText);
}
