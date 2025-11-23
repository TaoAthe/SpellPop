#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <set>
#include "../worddb/Topics.h"

enum class HangmanState {
    PLAYING,
    WORD_RESULT, // Show if they got the word right/wrong briefly? Or just go to next?
    LEVEL_SUMMARY
};

class HangmanSystem {
public:
    HangmanSystem();
    void Initialize();
    void ResetLevel(int chapter);
    void NextWord();
    void Update(float dt);
    void Render(sf::RenderWindow& window);
    
    void HandleInput(sf::Keyboard::Key key);

private:
    // Game State
    HangmanState m_state;
    int m_currentChapter;
    std::vector<WordEntry> m_levelWords;
    int m_currentWordIndex;
    
    // Scoring
    int m_correctWordsCount;
    std::vector<std::string> m_missedWords; // Store words missed in this level

    // Current Word State
    std::string m_targetWord;
    std::string m_currentClue;
    std::set<char> m_guessedLetters;
    int m_wrongGuesses;
    const int MAX_WRONG_GUESSES = 6;
    
    bool m_wordWon;
    bool m_wordLost;

    // Visuals
    sf::Font m_font;
    sf::Text m_wordDisplay;
    sf::Text m_clueDisplay;
    sf::Text m_statusText;
    sf::Text m_usedLettersText;
    sf::Text m_levelInfoText; // "Chapter 1: 3/10"

    // Drawing shapes
    void DrawGallows(sf::RenderWindow& window);
    void DrawSummary(sf::RenderWindow& window);
};
