#pragma once

#include <SFML/Graphics.hpp>
namespace Utils {
class GameState {
public:
  virtual ~GameState() = default;
  virtual void update(double dt) = 0;
  virtual void render(sf::RenderWindow &window) = 0;
  virtual void onEnter() = 0;
  virtual void onExit() = 0;
  virtual void handleEvent(const sf::Event &event) = 0;
};
} // namespace Utils
