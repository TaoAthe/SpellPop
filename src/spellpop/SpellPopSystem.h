#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Bubble.h"

class SpellPopSystem {
public:
    SpellPopSystem();
    void Initialize();
    void Update(float dt);
    void Render(sf::RenderWindow& window);
    
    void CheckInput(const std::string& input);
    int GetScore() const { return m_score; }
    int GetLevel() const { return m_level; }

private:
    void SpawnBubble();

    std::vector<Bubble> m_bubbles;
    sf::Font m_font;
    float m_spawnTimer;
    float m_spawnInterval;
    int m_score;
    int m_level;
    int m_nextLevelScore;
    std::string m_currentTopic;
};
