#include "gamestateManager.hpp"
#include "windowManager.hpp"
#include <SFML/Graphics.hpp>

using namespace sprocket::utils;

GameState *GameStateManager::currentState = nullptr;
std::unordered_map<State, GameState *> GameStateManager::states;
sf::Clock GameStateManager::clock;
float GameStateManager::lastDt = 0.0f;

void GameStateManager::update() {
  double dt = clock.restart().asMilliseconds();
  lastDt = dt;
  if (currentState) {
    currentState->update(dt);
  }
}

void GameStateManager::render() {
  if (currentState) {
    currentState->render(Utils::WindowManager::getWindow());
  }
}

void GameStateManager::handleEvent(const sf::Event &event) {
  if (currentState) {
    currentState->handleEvent(event);
  }
}

void GameStateManager::switchState(State newState,
                                   Transition transition = Transition::None) {
  if (currentState) {
    currentState->onExit();
  }

  currentState = states[newState];

  if (currentState) {
    currentState->onEnter();
  }
}
