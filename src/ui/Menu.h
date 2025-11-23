#pragma once
#include <SFML/Graphics.hpp>
#include "../engine/GameState.h"

class Menu {
public:
    Menu();
    void Initialize();
    void Update(float dt);
    void Render(sf::RenderWindow& window);
    
    void HandleInput(sf::Keyboard::Key key, GameState& currentState);

private:
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_option1;
    sf::Text m_option2;
    sf::Text m_option3;
    sf::Text m_option4; // C++ CrossFill
    int m_selectedOption;
};
