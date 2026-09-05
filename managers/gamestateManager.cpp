#include "gamestateManager.hpp"
#include "windowManager.hpp"
#include <SFML/Graphics.hpp>

using namespace sprocket::managers;
using namespace sprocket::utils;

GameState *GameStateManager::currentState = nullptr;
std::unordered_map<game::State, GameState *> GameStateManager::states;
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
    currentState->render(WindowManager::getWindow());
  }
}

void GameStateManager::handleEvent(const sf::Event &event) {
  if (currentState) {
    currentState->handleEvent(event);
  }
}

void GameStateManager::switchState(game::State newState) {
  if (currentState) {
    currentState->onExit();
  }

  currentState = states[newState];

  if (currentState) {
    currentState->onEnter();
  }
}
