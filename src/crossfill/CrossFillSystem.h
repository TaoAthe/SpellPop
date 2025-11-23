#pragma once
#include <SFML/Graphics.hpp>
#include "CrosswordPuzzle.h"

class CrossFillSystem {
public:
    CrossFillSystem();
    void Initialize();
    void SetChapter(int chapter); // New method
    void Update(float dt);
    void Render(sf::RenderWindow& window);
    
    void HandleInput(sf::Keyboard::Key key);
    void HandleTextInput(char c);
    void HandleMouseClick(int x, int y);

private:
    CrosswordPuzzle m_puzzle;
    sf::Font m_font;
    
    int m_cursorR;
    int m_cursorC;
    int m_currentChapter; // Track chapter
    
    // Visual settings
    float m_cellSize;
    float m_gridOffsetX;
    float m_gridOffsetY;
    
    bool m_directionAcross; // True = Across, False = Down
    sf::Text m_clueText;
};
