#pragma once

#include "../../utils/gameState.hpp"
#include "../utils/gamestate.hpp"
#include <unordered_map>
#include <stdexcept>
#include <type_traits>

namespace sprocket::managers {

class GameStateManager {
public:
  static void update();
  static void render();
  static void handleEvent(const sf::Event &event);
  static void switchState(game::State newState);
  template <typename Data>
  static void switchState(game::State newState, const Data &data) {
    auto *next = findState(newState);
    auto *receiver = dynamic_cast<
        sprocket::utils::GameStateWithData<std::decay_t<Data>> *>(next);
    if (!receiver) {
      throw std::invalid_argument("State does not accept this entry data type");
    }
    transitionTo(next);
    receiver->onEnter(data);
  }
  static void addState(game::State stateEnum,
                       sprocket::utils::GameState *state) {
    states[stateEnum] = state;
  }

  static int getFps() {
    return lastDt > 0 ? static_cast<int>(1000.0f / lastDt) : 0;
  }

private:
  static sprocket::utils::GameState *findState(game::State state);
  static void transitionTo(sprocket::utils::GameState *next);
  static sprocket::utils::GameState *currentState;
  static std::unordered_map<game::State, sprocket::utils::GameState *> states;
  static sf::Clock clock;
  static float lastDt;
};
} // namespace sprocket::managers
