#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace sprocket::utils {
class Button {
public:
  Button(const sf::Texture &texture, sf::Vector2f &position,
         sf::Vector2i spritePos, sf::Vector2i spriteSize,
         bool changeWhenHovering = false, float scale = 1.0);
  void render(sf::RenderWindow &window);
  void update();
  std::function<void()> onClick;

private:
  const sf::Texture &texture;
  sf::Vector2i spritePos;
  sf::Vector2i spriteSize;
  sf::Vector2f position;
  float scale;

  bool changeWhenHovering = false;
  bool isHovering = false;
};
} // namespace sprocket::utils
