#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Timer.h"
#include "GameState.h"

class Core {
public:
    Core();
    ~Core();

    bool Initialize();
    void Run();
    void Shutdown();

    sf::RenderWindow& GetWindow() { return *m_window; }
    static Core& Get() { return *s_instance; }

private:
    void HandleEvents();
    void Update(float dt);
    void Render();

    std::unique_ptr<sf::RenderWindow> m_window;
    Timer m_timer;
    static Core* s_instance;
    
    GameState m_gameState;

    // Systems
    std::unique_ptr<class SpellPopSystem> m_spellPop;
    std::unique_ptr<class CrossFillSystem> m_crossFill;
    std::unique_ptr<class HangmanSystem> m_hangman;
    std::unique_ptr<class Menu> m_menu;
    std::unique_ptr<class HUD> m_hud;
};
