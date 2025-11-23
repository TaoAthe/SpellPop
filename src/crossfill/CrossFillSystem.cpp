#include "CrossFillSystem.h"
#include <iostream>

CrossFillSystem::CrossFillSystem() 
    : m_cursorR(0), m_cursorC(0), m_cellSize(40.f), m_gridOffsetX(50.f), m_gridOffsetY(50.f), m_directionAcross(true), m_currentChapter(1)
{
}

void CrossFillSystem::Initialize() {
    if (!m_font.loadFromFile("assets/fonts/arial.ttf")) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }
    }
    
    m_clueText.setFont(m_font);
    m_clueText.setCharacterSize(20);
    m_clueText.setFillColor(sf::Color::Yellow);
    m_clueText.setPosition(50, 660);

    // Default load
    SetChapter(1);
}

void CrossFillSystem::SetChapter(int chapter) {
    m_currentChapter = chapter;
    m_puzzle.GenerateFromChapter(chapter);
    
    // Reset cursor to first non-block
    m_cursorR = 0;
    m_cursorC = 0;
    for(int r=0; r<CrosswordPuzzle::ROWS; ++r) {
        for(int c=0; c<CrosswordPuzzle::COLS; ++c) {
            if (!m_puzzle.GetCell(r,c).isBlock) {
                m_cursorR = r;
                m_cursorC = c;
                return;
            }
        }
    }
}

void CrossFillSystem::Update(float dt) {
    // Logic for checking win condition, etc.
}

void CrossFillSystem::Render(sf::RenderWindow& window) {
    sf::RectangleShape cellShape(sf::Vector2f(m_cellSize - 2.f, m_cellSize - 2.f));
    cellShape.setOutlineThickness(1.f);
    
    sf::Text letterText;
    letterText.setFont(m_font);
    letterText.setCharacterSize(24);
    letterText.setFillColor(sf::Color::Black);

    // Calculate active word range for highlighting
    int activeStart = -1;
    int activeEnd = -1;
    
    if (m_directionAcross) {
        // Find start
        int c = m_cursorC;
        while (c >= 0 && !m_puzzle.GetCell(m_cursorR, c).isBlock) c--;
        activeStart = c + 1;
        
        // Find end
        c = m_cursorC;
        while (c < CrosswordPuzzle::COLS && !m_puzzle.GetCell(m_cursorR, c).isBlock) c++;
        activeEnd = c - 1;
    } else {
        // Find start
        int r = m_cursorR;
        while (r >= 0 && !m_puzzle.GetCell(r, m_cursorC).isBlock) r--;
        activeStart = r + 1;
        
        // Find end
        r = m_cursorR;
        while (r < CrosswordPuzzle::ROWS && !m_puzzle.GetCell(r, m_cursorC).isBlock) r++;
        activeEnd = r - 1;
    }

    for(int r=0; r<CrosswordPuzzle::ROWS; ++r) {
        for(int c=0; c<CrosswordPuzzle::COLS; ++c) {
            float x = m_gridOffsetX + c * m_cellSize;
            float y = m_gridOffsetY + r * m_cellSize;
            
            CrosswordCell& cell = m_puzzle.GetCell(r, c);
            
            cellShape.setPosition(x, y);
            
            if (cell.isBlock) {
                cellShape.setFillColor(sf::Color::Black);
                cellShape.setOutlineColor(sf::Color::Black);
            } else {
                // Determine highlight
                bool isHighlighted = false;
                if (m_directionAcross) {
                    if (r == m_cursorR && c >= activeStart && c <= activeEnd) isHighlighted = true;
                } else {
                    if (c == m_cursorC && r >= activeStart && r <= activeEnd) isHighlighted = true;
                }

                if (isHighlighted) {
                    cellShape.setFillColor(sf::Color(200, 255, 200)); // Light Green for active word
                } else {
                    cellShape.setFillColor(sf::Color::White);
                }
                cellShape.setOutlineColor(sf::Color::Black);
                
                // Highlight cursor
                if (r == m_cursorR && c == m_cursorC) {
                    cellShape.setOutlineColor(sf::Color::Yellow);
                    cellShape.setOutlineThickness(3.f);
                } else {
                    cellShape.setOutlineThickness(1.f);
                }
            }
            
            window.draw(cellShape);
            
            if (!cell.isBlock && cell.input != ' ') {
                letterText.setString(std::string(1, cell.input));
                // Center text
                sf::FloatRect bounds = letterText.getLocalBounds();
                letterText.setOrigin(bounds.left + bounds.width/2.0f, bounds.top + bounds.height/2.0f);
                letterText.setPosition(x + m_cellSize/2.0f, y + m_cellSize/2.0f);
                window.draw(letterText);
            }
        }
    }
    
    // Draw Clue
    std::string clue = m_puzzle.GetClue(m_cursorR, m_cursorC, m_directionAcross);
    if (clue.empty()) {
        // Try other direction if current is empty
        clue = m_puzzle.GetClue(m_cursorR, m_cursorC, !m_directionAcross);
    }
    std::string dirStr = m_directionAcross ? "ACROSS: " : "DOWN: ";
    m_clueText.setString(dirStr + clue);
    window.draw(m_clueText);
}

void CrossFillSystem::HandleInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Up)    { m_cursorR = std::max(0, m_cursorR - 1); }
    if (key == sf::Keyboard::Down)  { m_cursorR = std::min((int)CrosswordPuzzle::ROWS - 1, m_cursorR + 1); }
    if (key == sf::Keyboard::Left)  { m_cursorC = std::max(0, m_cursorC - 1); }
    if (key == sf::Keyboard::Right) { m_cursorC = std::min((int)CrosswordPuzzle::COLS - 1, m_cursorC + 1); }
    
    // Adjust direction if we moved to a cell that only supports the other direction
    if (key == sf::Keyboard::Up || key == sf::Keyboard::Down || key == sf::Keyboard::Left || key == sf::Keyboard::Right) {
        if (!m_puzzle.GetCell(m_cursorR, m_cursorC).isBlock) {
             bool hasAcross = ((m_cursorC > 0 && !m_puzzle.GetCell(m_cursorR, m_cursorC-1).isBlock) || 
                               (m_cursorC < CrosswordPuzzle::COLS-1 && !m_puzzle.GetCell(m_cursorR, m_cursorC+1).isBlock));
             bool hasDown = ((m_cursorR > 0 && !m_puzzle.GetCell(m_cursorR-1, m_cursorC).isBlock) || 
                             (m_cursorR < CrosswordPuzzle::ROWS-1 && !m_puzzle.GetCell(m_cursorR+1, m_cursorC).isBlock));
             
             if (m_directionAcross && !hasAcross && hasDown) m_directionAcross = false;
             if (!m_directionAcross && !hasDown && hasAcross) m_directionAcross = true;
        }
    }

    if (key == sf::Keyboard::Tab) {
        m_directionAcross = !m_directionAcross;
    }
    
    if (key == sf::Keyboard::BackSpace) {
        CrosswordCell& cell = m_puzzle.GetCell(m_cursorR, m_cursorC);
        if (!cell.isBlock) cell.input = ' ';
        // Optional: Move back on backspace?
        // int prevR = m_cursorR - (m_directionAcross ? 0 : 1);
        // int prevC = m_cursorC - (m_directionAcross ? 1 : 0);
        // if (prevR >= 0 && prevC >= 0 && !m_puzzle.GetCell(prevR, prevC).isBlock) {
        //    m_cursorR = prevR; m_cursorC = prevC;
        // }
    }
}

void CrossFillSystem::HandleTextInput(char c) {
    CrosswordCell& cell = m_puzzle.GetCell(m_cursorR, m_cursorC);
    if (!cell.isBlock) {
        cell.input = toupper(c);
        
        // Auto-advance
        int nextR = m_cursorR + (m_directionAcross ? 0 : 1);
        int nextC = m_cursorC + (m_directionAcross ? 1 : 0);
        
        if (nextR < CrosswordPuzzle::ROWS && nextC < CrosswordPuzzle::COLS) {
            if (!m_puzzle.GetCell(nextR, nextC).isBlock) {
                m_cursorR = nextR;
                m_cursorC = nextC;
            }
        }
    }
}

void CrossFillSystem::HandleMouseClick(int x, int y) {
    // Convert screen to grid
    int c = (int)((x - m_gridOffsetX) / m_cellSize);
    int r = (int)((y - m_gridOffsetY) / m_cellSize);

    if (r >= 0 && r < CrosswordPuzzle::ROWS && c >= 0 && c < CrosswordPuzzle::COLS) {
        if (!m_puzzle.GetCell(r, c).isBlock) {
            if (r == m_cursorR && c == m_cursorC) {
                // Toggle direction
                m_directionAcross = !m_directionAcross;
            } else {
                // Move cursor
                m_cursorR = r;
                m_cursorC = c;
                
                // Determine best direction
                bool hasAcross = false;
                bool hasDown = false;
                
                // Check neighbors for Across
                if ((c > 0 && !m_puzzle.GetCell(r, c-1).isBlock) || 
                    (c < CrosswordPuzzle::COLS-1 && !m_puzzle.GetCell(r, c+1).isBlock)) {
                    hasAcross = true;
                }
                
                // Check neighbors for Down
                if ((r > 0 && !m_puzzle.GetCell(r-1, c).isBlock) || 
                    (r < CrosswordPuzzle::ROWS-1 && !m_puzzle.GetCell(r+1, c).isBlock)) {
                    hasDown = true;
                }
                
                if (hasAcross && !hasDown) m_directionAcross = true;
                else if (!hasAcross && hasDown) m_directionAcross = false;
                // If both or neither, keep current
            }
        }
    }
}
