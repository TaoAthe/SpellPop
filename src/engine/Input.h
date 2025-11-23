#pragma once
#include <SFML/Window/Event.hpp>
#include <string>
#include <vector>

class Input {
public:
    static void Update();
    static void ProcessEvent(const sf::Event& event);
    
    static bool IsKeyDown(sf::Keyboard::Key key);
    static bool IsKeyPressed(sf::Keyboard::Key key); // True only on the frame it was pressed
    
    static std::string GetTextBuffer();
    static void ClearTextBuffer();
    static void PopLastChar();

private:
    static bool m_keys[sf::Keyboard::KeyCount];
    static bool m_prevKeys[sf::Keyboard::KeyCount];
    static std::string m_textBuffer;
};
