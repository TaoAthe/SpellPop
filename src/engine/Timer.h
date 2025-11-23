#pragma once
#include <SFML/System/Clock.hpp>

class Timer {
public:
    Timer();
    void Reset();
    float GetDeltaTime(); // Returns time in seconds since last call
    float GetTotalTime();

private:
    sf::Clock m_clock;
    sf::Time m_lastTime;
};
