#include "Input.h"

bool Input::m_keys[sf::Keyboard::KeyCount] = { false };
bool Input::m_prevKeys[sf::Keyboard::KeyCount] = { false };
std::string Input::m_textBuffer = "";

void Input::Update() {
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        m_prevKeys[i] = m_keys[i];
        m_keys[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
    }
}

void Input::ProcessEvent(const sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128 && event.text.unicode > 31) { // Printable ASCII
            m_textBuffer += static_cast<char>(event.text.unicode);
        }
    }
}

bool Input::IsKeyDown(sf::Keyboard::Key key) {
    return m_keys[key];
}

bool Input::IsKeyPressed(sf::Keyboard::Key key) {
    return m_keys[key] && !m_prevKeys[key];
}

std::string Input::GetTextBuffer() {
    return m_textBuffer;
}

void Input::ClearTextBuffer() {
    m_textBuffer.clear();
}

void Input::PopLastChar() {
    if (!m_textBuffer.empty()) {
        m_textBuffer.pop_back();
    }
}
