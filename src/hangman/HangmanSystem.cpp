#include "HangmanSystem.h"
#include <iostream>
#include <sstream>

HangmanSystem::HangmanSystem() 
    : m_wrongGuesses(0), m_wordWon(false), m_wordLost(false), 
      m_state(HangmanState::PLAYING), m_currentChapter(1), m_currentWordIndex(0), m_correctWordsCount(0)
{}

void HangmanSystem::Initialize() {
    if (!m_font.loadFromFile("assets/fonts/arial.ttf")) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }
    }
    
    m_wordDisplay.setFont(m_font);
    m_wordDisplay.setCharacterSize(40);
    m_wordDisplay.setFillColor(sf::Color::White);
    m_wordDisplay.setPosition(400, 400);

    m_clueDisplay.setFont(m_font);
    m_clueDisplay.setCharacterSize(24);
    m_clueDisplay.setFillColor(sf::Color::Yellow);
    m_clueDisplay.setPosition(400, 350);

    m_statusText.setFont(m_font);
    m_statusText.setCharacterSize(30);
    m_statusText.setPosition(400, 200);

    m_usedLettersText.setFont(m_font);
    m_usedLettersText.setCharacterSize(20);
    m_usedLettersText.setFillColor(sf::Color(200, 200, 200));
    m_usedLettersText.setPosition(400, 500);

    m_levelInfoText.setFont(m_font);
    m_levelInfoText.setCharacterSize(20);
    m_levelInfoText.setFillColor(sf::Color::Cyan);
    m_levelInfoText.setPosition(20, 20);

    ResetLevel(1);
}

void HangmanSystem::ResetLevel(int chapter) {
    m_currentChapter = chapter;
    m_levelWords = WordDB::GetWordsForChapter(m_currentChapter);
    m_currentWordIndex = 0;
    m_correctWordsCount = 0;
    m_missedWords.clear();
    m_state = HangmanState::PLAYING;
    
    if (m_levelWords.empty()) {
        // Fallback if chapter empty
        m_statusText.setString("No words for Chapter " + std::to_string(chapter));
        return;
    }

    NextWord();
}

void HangmanSystem::NextWord() {
    if (m_currentWordIndex >= m_levelWords.size()) {
        m_state = HangmanState::LEVEL_SUMMARY;
        return;
    }

    WordEntry entry = m_levelWords[m_currentWordIndex];
    m_targetWord = entry.word;
    m_currentClue = entry.clue;

    m_guessedLetters.clear();
    m_wrongGuesses = 0;
    m_wordWon = false;
    m_wordLost = false;
    m_statusText.setString("");
}

void HangmanSystem::Update(float dt) {
    if (m_state == HangmanState::LEVEL_SUMMARY) {
        // Logic handled in Render/Input
        return;
    }

    // Update Level Info
    std::stringstream ss;
    ss << "Chapter " << m_currentChapter << " | Word " << (m_currentWordIndex + 1) << "/" << m_levelWords.size();
    m_levelInfoText.setString(ss.str());

    if (m_wordWon || m_wordLost) return;

    // Check win condition for current word
    bool allGuessed = true;
    std::string displayStr = "";
    for (char c : m_targetWord) {
        if (m_guessedLetters.count(c)) {
            displayStr += c;
            displayStr += " ";
        } else {
            displayStr += "_ ";
            allGuessed = false;
        }
    }
    m_wordDisplay.setString(displayStr);
    m_clueDisplay.setString("Clue: " + m_currentClue);

    std::string usedStr = "Used: ";
    for(char c : m_guessedLetters) {
        usedStr += c;
        usedStr += " ";
    }
    m_usedLettersText.setString(usedStr);

    if (allGuessed) {
        m_wordWon = true;
        m_correctWordsCount++;
        m_statusText.setString("CORRECT! Press Enter for Next Word");
        m_statusText.setFillColor(sf::Color::Green);
    } else if (m_wrongGuesses >= MAX_WRONG_GUESSES) {
        m_wordLost = true;
        m_missedWords.push_back(m_targetWord);
        m_statusText.setString("MISSED! Word: " + m_targetWord + "\nPress Enter for Next Word");
        m_statusText.setFillColor(sf::Color::Red);
    }
}

void HangmanSystem::Render(sf::RenderWindow& window) {
    if (m_state == HangmanState::LEVEL_SUMMARY) {
        DrawSummary(window);
        return;
    }

    window.draw(m_wordDisplay);
    window.draw(m_clueDisplay);
    window.draw(m_statusText);
    window.draw(m_usedLettersText);
    window.draw(m_levelInfoText);
    DrawGallows(window);
}

void HangmanSystem::DrawSummary(sf::RenderWindow& window) {
    float percentage = 0.0f;
    if (!m_levelWords.empty()) {
        percentage = (static_cast<float>(m_correctWordsCount) / m_levelWords.size()) * 100.0f;
    }

    sf::Text title;
    title.setFont(m_font);
    title.setCharacterSize(40);
    title.setPosition(100, 50);
    
    sf::Text details;
    details.setFont(m_font);
    details.setCharacterSize(24);
    details.setPosition(100, 150);
    details.setFillColor(sf::Color::White);

    std::stringstream ss;
    ss << "Score: " << m_correctWordsCount << "/" << m_levelWords.size() << " (" << (int)percentage << "%)";
    
    if (percentage >= 95.0f) {
        title.setString("CHAPTER COMPLETE!");
        title.setFillColor(sf::Color::Green);
        ss << "\n\nGreat job! You have mastered this chapter.";
        ss << "\nPress ENTER to proceed to Chapter " << (m_currentChapter + 1);
    } else {
        title.setString("CHAPTER FAILED");
        title.setFillColor(sf::Color::Red);
        ss << "\n\nYou need 95% to advance.";
        ss << "\n\nMissed Words:";
        for(const auto& w : m_missedWords) {
            ss << "\n - " << w;
        }
        ss << "\n\nPress ENTER to Retry Chapter " << m_currentChapter;
    }

    details.setString(ss.str());

    window.draw(title);
    window.draw(details);
}

void HangmanSystem::HandleInput(sf::Keyboard::Key key) {
    if (m_state == HangmanState::LEVEL_SUMMARY) {
        if (key == sf::Keyboard::Enter) {
            float percentage = 0.0f;
            if (!m_levelWords.empty()) {
                percentage = (static_cast<float>(m_correctWordsCount) / m_levelWords.size()) * 100.0f;
            }

            if (percentage >= 95.0f) {
                // Next Level
                ResetLevel(m_currentChapter + 1);
            } else {
                // Retry Level (ResetLevel rescrambles words)
                ResetLevel(m_currentChapter);
            }
        }
        return;
    }

    if (m_wordWon || m_wordLost) {
        if (key == sf::Keyboard::Enter) {
            m_currentWordIndex++;
            NextWord();
        }
        return;
    }

    if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z) {
        char letter = static_cast<char>('A' + (key - sf::Keyboard::A));
        if (m_guessedLetters.find(letter) == m_guessedLetters.end()) {
            m_guessedLetters.insert(letter);
            if (m_targetWord.find(letter) == std::string::npos) {
                m_wrongGuesses++;
            }
        }
    }
}

void HangmanSystem::DrawGallows(sf::RenderWindow& window) {
    sf::RectangleShape base(sf::Vector2f(100, 10));
    base.setPosition(100, 600);
    base.setFillColor(sf::Color::White);
    window.draw(base);

    sf::RectangleShape pole(sf::Vector2f(10, 300));
    pole.setPosition(145, 300);
    pole.setFillColor(sf::Color::White);
    window.draw(pole);

    sf::RectangleShape top(sf::Vector2f(100, 10));
    top.setPosition(145, 300);
    top.setFillColor(sf::Color::White);
    window.draw(top);

    sf::RectangleShape rope(sf::Vector2f(5, 50));
    rope.setPosition(240, 300);
    rope.setFillColor(sf::Color(150, 100, 50));
    window.draw(rope);

    if (m_wrongGuesses > 0) { // Head
        sf::CircleShape head(20);
        head.setPosition(222, 350);
        head.setFillColor(sf::Color::Transparent);
        head.setOutlineThickness(3);
        head.setOutlineColor(sf::Color::White);
        window.draw(head);
    }
    if (m_wrongGuesses > 1) { // Body
        sf::RectangleShape body(sf::Vector2f(5, 80));
        body.setPosition(240, 390);
        body.setFillColor(sf::Color::White);
        window.draw(body);
    }
    if (m_wrongGuesses > 2) { // Left Arm
        sf::RectangleShape arm(sf::Vector2f(5, 60));
        arm.setPosition(240, 400);
        arm.setRotation(45);
        arm.setFillColor(sf::Color::White);
        window.draw(arm);
    }
    if (m_wrongGuesses > 3) { // Right Arm
        sf::RectangleShape arm(sf::Vector2f(5, 60));
        arm.setPosition(240, 400);
        arm.setRotation(-45);
        arm.setFillColor(sf::Color::White);
        window.draw(arm);
    }
    if (m_wrongGuesses > 4) { // Left Leg
        sf::RectangleShape leg(sf::Vector2f(5, 60));
        leg.setPosition(240, 470);
        leg.setRotation(30);
        leg.setFillColor(sf::Color::White);
        window.draw(leg);
    }
    if (m_wrongGuesses > 5) { // Right Leg
        sf::RectangleShape leg(sf::Vector2f(5, 60));
        leg.setPosition(240, 470);
        leg.setRotation(-30);
        leg.setFillColor(sf::Color::White);
        window.draw(leg);
    }
}
