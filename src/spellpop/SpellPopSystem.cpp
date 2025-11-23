#include "SpellPopSystem.h"
#include "../worddb/Topics.h"
#include <iostream>

SpellPopSystem::SpellPopSystem() 
    : m_spawnTimer(0.f), m_spawnInterval(2.0f), m_score(0), m_level(1), m_nextLevelScore(500), m_currentTopic("Astronomy")
{
}

void SpellPopSystem::Initialize() {
    // Try to load a font. Fallback to Windows system font if assets fail.
    if (!m_font.loadFromFile("assets/fonts/arial.ttf")) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }
    }
    WordDB::Initialize();
}

void SpellPopSystem::Update(float dt) {
    m_spawnTimer += dt;
    if (m_spawnTimer >= m_spawnInterval) {
        SpawnBubble();
        m_spawnTimer = 0.f;
    }

    // Level up logic
    if (m_score >= m_nextLevelScore) {
        m_level++;
        m_nextLevelScore += 500 * m_level; // Increase threshold
        m_spawnInterval = std::max(0.5f, m_spawnInterval - 0.2f); // Speed up spawns
    }

    for (auto& bubble : m_bubbles) {
        bubble.Update(dt);
    }

    // Remove inactive bubbles
    m_bubbles.erase(std::remove_if(m_bubbles.begin(), m_bubbles.end(),
        [](const Bubble& b) { return !b.active; }), m_bubbles.end());
}

void SpellPopSystem::Render(sf::RenderWindow& window) {
    for (auto& bubble : m_bubbles) {
        bubble.Render(window);
    }
}

void SpellPopSystem::SpawnBubble() {
    std::string word = WordDB::GetRandomWord(m_currentTopic);
    float x = static_cast<float>(rand() % 1000 + 100); // Random X between 100 and 1100
    float y = 800.f; // Start below screen
    
    // Base speed increases with level
    float baseSpeed = 50.f + (m_level * 10.f);
    float speed = baseSpeed + static_cast<float>(rand() % 50); 

    m_bubbles.emplace_back(word, x, y, speed, m_font);
}

void SpellPopSystem::CheckInput(const std::string& input) {
    for (auto& bubble : m_bubbles) {
        if (bubble.active && bubble.word == input) {
            bubble.active = false;
            m_score += 100;
            // Play sound effect here
            return; // Only pop one at a time
        }
    }
}
