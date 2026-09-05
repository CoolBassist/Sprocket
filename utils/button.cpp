#include "button.hpp"
#include "./managers/audioManager.hpp"
#include "./managers/windowManager.hpp"
#include <spdlog/spdlog.h>

using namespace Utils;

Button::Button(const sf::Texture &texture, sf::Vector2f &position,
               sf::Vector2i spritePos, sf::Vector2i spriteSize,
               bool changeWhenHovering, float scale)
    : texture(texture), position(position), spritePos(spritePos),
      spriteSize(spriteSize), changeWhenHovering(changeWhenHovering),
      scale(scale) {}

void Button::render(sf::RenderWindow &window) {
  sf::Sprite sprite(texture);
  sprite.setTextureRect({spritePos, spriteSize});
  if (changeWhenHovering && isHovering) {
    sprite.setTextureRect(
        {spritePos + sf::Vector2i(spriteSize.x, 0),
         {spriteSize.x, spriteSize.y}}); // Lighten the sprite when hovering
  }
  sprite.setPosition(position);
  sprite.setScale({scale, scale});
  window.draw(sprite);
}

void Button::update() {
  sf::Vector2i mousePos =
      sf::Mouse::getPosition(Utils::WindowManager::getWindow());
  const auto [mouseX, mouseY] =
      Utils::WindowManager::mapPixelToCoords(mousePos);

  sf::FloatRect buttonRect(position,
                           {spriteSize.x * scale, spriteSize.y * scale});
  isHovering = buttonRect.contains(static_cast<sf::Vector2f>(mousePos));

  if (isHovering && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
      onClick) {
    Utils::AudioManager::playSound(Utils::Sound::ButtonClick);
    Utils::AudioManager::stopMusic(Utils::Music::Background);
    onClick();
  }
}
