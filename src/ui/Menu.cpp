#include "Menu.h"
#include <iostream>

Menu::Menu() : m_selectedOption(0) {}

void Menu::Initialize() {
    if (!m_font.loadFromFile("assets/fonts/arial.ttf")) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }
    }

    m_titleText.setFont(m_font);
    m_titleText.setString("SPELLPOP");
    m_titleText.setCharacterSize(60);
    m_titleText.setFillColor(sf::Color::Cyan);
    m_titleText.setPosition(400, 100);

    m_option1.setFont(m_font);
    m_option1.setString("> SpellPop 3D Mode");
    m_option1.setCharacterSize(30);
    m_option1.setFillColor(sf::Color::White);
    m_option1.setPosition(400, 300);

    m_option2.setFont(m_font);
    m_option2.setString("  CrossFill Mode");
    m_option2.setCharacterSize(30);
    m_option2.setFillColor(sf::Color(150, 150, 150));
    m_option2.setPosition(400, 350);

    m_option3.setFont(m_font);
    m_option3.setString("  Hangman Mode");
    m_option3.setCharacterSize(30);
    m_option3.setFillColor(sf::Color(150, 150, 150));
    m_option3.setPosition(400, 400);

    m_option4.setFont(m_font);
    m_option4.setString("  C++ CrossFill (Ch 1)");
    m_option4.setCharacterSize(30);
    m_option4.setFillColor(sf::Color(150, 150, 150));
    m_option4.setPosition(400, 450);
}

void Menu::Update(float dt) {
    // Reset all to gray
    m_option1.setString("  SpellPop 3D Mode");
    m_option1.setFillColor(sf::Color(150, 150, 150));
    m_option2.setString("  CrossFill Mode (Demo)");
    m_option2.setFillColor(sf::Color(150, 150, 150));
    m_option3.setString("  Hangman Mode");
    m_option3.setFillColor(sf::Color(150, 150, 150));
    m_option4.setString("  C++ CrossFill (Ch 1)");
    m_option4.setFillColor(sf::Color(150, 150, 150));

    // Highlight selected
    if (m_selectedOption == 0) {
        m_option1.setString("> SpellPop 3D Mode");
        m_option1.setFillColor(sf::Color::White);
    } else if (m_selectedOption == 1) {
        m_option2.setString("> CrossFill Mode (Demo)");
        m_option2.setFillColor(sf::Color::White);
    } else if (m_selectedOption == 2) {
        m_option3.setString("> Hangman Mode");
        m_option3.setFillColor(sf::Color::White);
    } else if (m_selectedOption == 3) {
        m_option4.setString("> C++ CrossFill (Ch 1)");
        m_option4.setFillColor(sf::Color::White);
    }
}

void Menu::Render(sf::RenderWindow& window) {
    window.draw(m_titleText);
    window.draw(m_option1);
    window.draw(m_option2);
    window.draw(m_option3);
    window.draw(m_option4);
}

void Menu::HandleInput(sf::Keyboard::Key key, GameState& currentState) {
    if (key == sf::Keyboard::Up) {
        m_selectedOption--;
        if (m_selectedOption < 0) m_selectedOption = 3;
    }
    if (key == sf::Keyboard::Down) {
        m_selectedOption++;
        if (m_selectedOption > 3) m_selectedOption = 0;
    }
    if (key == sf::Keyboard::Enter) {
        if (m_selectedOption == 0) currentState = GameState::SPELLPOP;
        else if (m_selectedOption == 1) currentState = GameState::CROSSFILL;
        else if (m_selectedOption == 2) currentState = GameState::HANGMAN;
        else if (m_selectedOption == 3) {
            currentState = GameState::CROSSFILL_CPP;
        }
    }
}
