#include "Core.h"
#include "Input.h"
#include <iostream>

#include "../spellpop/SpellPopSystem.h"
#include "../crossfill/CrossFillSystem.h"
#include "../hangman/HangmanSystem.h"
#include "../ui/Menu.h"
#include "../ui/HUD.h"

Core* Core::s_instance = nullptr;

Core::Core() : m_gameState(GameState::MENU) {
    s_instance = this;
}

Core::~Core() {
    Shutdown();
}

bool Core::Initialize() {
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720), "SpellPop - Dual Mode Word Gauntlet");
    m_window->setFramerateLimit(60);
    
    m_spellPop = std::make_unique<SpellPopSystem>();
    m_spellPop->Initialize();

    m_crossFill = std::make_unique<CrossFillSystem>();
    m_crossFill->Initialize();

    m_hangman = std::make_unique<HangmanSystem>();
    m_hangman->Initialize();

    m_menu = std::make_unique<Menu>();
    m_menu->Initialize();

    m_hud = std::make_unique<HUD>();
    m_hud->Initialize();
    
    return true;
}

void Core::Shutdown() {
    if (m_window && m_window->isOpen()) {
        m_window->close();
    }
}

void Core::Run() {
    m_timer.Reset();
    while (m_window->isOpen()) {
        float dt = m_timer.GetDeltaTime();
        HandleEvents();
        Update(dt);
        Render();
    }
}

void Core::HandleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window->close();
        
        Input::ProcessEvent(event);

        if (event.type == sf::Event::KeyPressed) {
            if (m_gameState == GameState::MENU) {
                GameState prevState = m_gameState;
                m_menu->HandleInput(event.key.code, m_gameState);
                
                // Initialize specific modes if we just switched
                if (prevState == GameState::MENU && m_gameState == GameState::CROSSFILL_CPP) {
                    m_crossFill->SetChapter(1);
                } else if (prevState == GameState::MENU && m_gameState == GameState::CROSSFILL) {
                    // Load default demo puzzle
                    // m_crossFill->LoadDemo(); // We haven't implemented this, but SetChapter(1) overwrites it anyway.
                    // For now, let's just let CrossFill be whatever it was or reset it.
                    // Ideally we'd have a Reset() method.
                }
            } else if (m_gameState == GameState::CROSSFILL || m_gameState == GameState::CROSSFILL_CPP) {
                m_crossFill->HandleInput(event.key.code);
                if (event.key.code == sf::Keyboard::Escape) m_gameState = GameState::MENU;
            } else if (m_gameState == GameState::HANGMAN) {
                m_hangman->HandleInput(event.key.code);
                if (event.key.code == sf::Keyboard::Escape) m_gameState = GameState::MENU;
            } else if (m_gameState == GameState::SPELLPOP) {
                if (event.key.code == sf::Keyboard::Escape) m_gameState = GameState::MENU;
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                    m_spellPop->CheckInput(Input::GetTextBuffer());
                    Input::ClearTextBuffer();
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    Input::PopLastChar();
                }
            }
        }
        
        if (event.type == sf::Event::TextEntered && (m_gameState == GameState::CROSSFILL || m_gameState == GameState::CROSSFILL_CPP)) {
             if (event.text.unicode < 128 && event.text.unicode > 31) {
                 m_crossFill->HandleTextInput(static_cast<char>(event.text.unicode));
             }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (m_gameState == GameState::CROSSFILL || m_gameState == GameState::CROSSFILL_CPP) {
                m_crossFill->HandleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
    Input::Update();
}

void Core::Update(float dt) {
    if (m_gameState == GameState::MENU) {
        m_menu->Update(dt);
    } else if (m_gameState == GameState::SPELLPOP) {
        m_spellPop->Update(dt);
    } else if (m_gameState == GameState::CROSSFILL || m_gameState == GameState::CROSSFILL_CPP) {
        m_crossFill->Update(dt);
    } else if (m_gameState == GameState::HANGMAN) {
        m_hangman->Update(dt);
    }
}

void Core::Render() {
    m_window->clear(sf::Color(20, 20, 30)); // Dark blue-ish background
    
    if (m_gameState == GameState::MENU) {
        m_menu->Render(*m_window);
    } else if (m_gameState == GameState::SPELLPOP) {
        m_spellPop->Render(*m_window);
        m_hud->Render(*m_window, m_spellPop->GetScore(), Input::GetTextBuffer(), m_spellPop->GetLevel());
    } else if (m_gameState == GameState::CROSSFILL || m_gameState == GameState::CROSSFILL_CPP) {
        m_crossFill->Render(*m_window);
    } else if (m_gameState == GameState::HANGMAN) {
        m_hangman->Render(*m_window);
    }
    
    m_window->display();
}
