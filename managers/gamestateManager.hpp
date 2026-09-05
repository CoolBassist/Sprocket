#include "../../utils/gameState.hpp"
#include "../utils/gamestate.hpp"
#include <unordered_map>

namespace sprocket::managers {

enum class Transition { None, FadeIn, FadeOut };

class GameStateManager {
public:
  static void update();
  static void render();
  static void handleEvent(const sf::Event &event);
  static void switchState(game::State newState, Transition transition);
  static void addState(game::State stateEnum,
                       sprocket::utils::GameState *state) {
    states[stateEnum] = state;
  }

  static int getFps() {
    return lastDt > 0 ? static_cast<int>(1000.0f / lastDt) : 0;
  }

private:
  static sprocket::utils::GameState *currentState;
  static std::unordered_map<game::State, sprocket::utils::GameState *> states;
  static sf::Clock clock;
  static float lastDt;
};
} // namespace sprocket::managers
