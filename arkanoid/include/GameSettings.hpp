#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

extern std::shared_ptr<sf::RenderWindow> window;

namespace GameParam
{

extern sf::Font font;

extern bool isMouseControl;

extern size_t points;

extern size_t lives;

} // namespace GameParam
