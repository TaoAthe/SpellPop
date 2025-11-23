#include "Timer.h"

Timer::Timer() {
    Reset();
}

void Timer::Reset() {
    m_clock.restart();
    m_lastTime = sf::Time::Zero;
}

float Timer::GetDeltaTime() {
    sf::Time currentTime = m_clock.getElapsedTime();
    float dt = (currentTime - m_lastTime).asSeconds();
    m_lastTime = currentTime;
    return dt;
}

float Timer::GetTotalTime() {
    return m_clock.getElapsedTime().asSeconds();
}
