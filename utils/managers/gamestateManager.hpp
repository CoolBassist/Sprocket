#include "../../gamestates/gamestate.hpp"
#include <unordered_map>

namespace sprocket::utils {

enum class State { MainMenu, Playing };
enum class Transition { None, FadeIn, FadeOut };

class GameStateManager {
public:
  static void update();
  static void render();
  static void handleEvent(const sf::Event &event);
  static void switchState(State newState, Transition transition);
  static void addState(State stateEnum, GameState *state) {
    states[stateEnum] = state;
  }
  static int getFps() {
    return lastDt > 0 ? static_cast<int>(1000.0f / lastDt) : 0;
  }

private:
  static GameState *currentState;
  static std::unordered_map<State, GameState *> states;
  static sf::Clock clock;
  static float lastDt;
};
} // namespace sprocket::utils
