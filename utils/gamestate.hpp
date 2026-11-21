#pragma once

#include <SFML/Graphics.hpp>
namespace sprocket::utils {
class GameState {
public:
  virtual ~GameState() = default;
  virtual void update(double dt) = 0;
  virtual void render(sf::RenderWindow &window) = 0;
  virtual void onEnter() = 0;
  virtual bool requiresEntryData() const { return false; }
  virtual void onExit() = 0;
  virtual void handleEvent(const sf::Event &event) = 0;
};

template <typename Data> class GameStateWithData : public GameState {
public:
  virtual void onEnter(const Data &data) = 0;
  bool requiresEntryData() const final { return true; }

private:
  void onEnter() final {}
};
} // namespace sprocket::utils
