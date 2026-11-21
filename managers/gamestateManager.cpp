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

GameState *GameStateManager::findState(game::State state) {
  const auto found = states.find(state);
  if (found == states.end() || !found->second) {
    throw std::invalid_argument("Game state is not registered");
  }
  return found->second;
}

void GameStateManager::transitionTo(GameState *next) {
  if (currentState) {
    currentState->onExit();
  }

  currentState = next;
}

void GameStateManager::switchState(game::State newState) {
  auto *next = findState(newState);
  if (next->requiresEntryData()) {
    throw std::invalid_argument("Game state requires entry data");
  }
  transitionTo(next);
  next->onEnter();
}
